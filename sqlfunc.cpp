#include <sqlite3.h>
#include <string>
#include <wx/listctrl.h>
#include <list>
#include "fileListThread.h"
#include <wx/app.h>

extern std::vector<filesha256> file256List;
extern std::vector<photoBatch> batchList;
extern std::vector<std::string> sha256;
extern sqlite3 *db;
/*
Description:Convert between ANSI and UTF-8
Usage:
convert UTF-8 to ANSI:
    CodePageConvert(CP_ACP,ansi_str_out,CP_UTF8,utf8_str_in);
Conver ANSI to UTF-8:
    CodePageConvert(CP_UTF8,utf8_str_out,CP_ACP,ansi_str_in);
*/
//****大半天用wxString、std::wstring，想删除本函数，失败
int CodePageConvert(uint32_t uDestCodePage, void *pDestChar, uint32_t uSrcCodePage, void *pSrcChar) {
    if (uDestCodePage == uSrcCodePage) {
        return -1;
    }
    if ((pDestChar == nullptr) || (pSrcChar == nullptr)) {
        return -1;
    }
    // ANSI转UTF-8
    if ((uSrcCodePage == CP_ACP) && (uDestCodePage == CP_UTF8)) {
        //先将ASCII码转换为Unicode编码
        int wcharlen = MultiByteToWideChar(CP_ACP, 0, (PCSTR) pSrcChar, -1, nullptr, 0);
        uint32_t cbWideCharByte = wcharlen * sizeof(wchar_t);
        void *pWideCharBuf = malloc(cbWideCharByte);
        memset(pWideCharBuf, 0x00, cbWideCharByte);
        MultiByteToWideChar(CP_ACP, 0, (PCSTR) pSrcChar, -1, (PWSTR) pWideCharBuf, cbWideCharByte);
        //将Unicode编码转换为UTF-8编码
        int u8Len = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH) pWideCharBuf, -1, nullptr, 0, nullptr, FALSE);
        WideCharToMultiByte(CP_UTF8, 0, (LPCWCH) pWideCharBuf, cbWideCharByte, (LPSTR) pDestChar, u8Len, nullptr,
                            FALSE);
        free(pWideCharBuf);
    }
    // UTF-8转ANSI
    if ((uSrcCodePage == CP_UTF8) && (uDestCodePage == CP_ACP)) {
        // UTF-8转Unicode
        int wcharlen = MultiByteToWideChar(CP_UTF8, 0, (LPCCH) pSrcChar, -1, nullptr, 0);
        uint32_t wchar_byte = wcharlen * sizeof(wchar_t);
        void *pUnicodeBuf = malloc(wchar_byte);
        memset(pUnicodeBuf, 0x00, wchar_byte);
        MultiByteToWideChar(CP_UTF8, 0, (LPCCH) pSrcChar, -1, (LPWSTR) pUnicodeBuf, wcharlen);
        int aLen = WideCharToMultiByte(CP_ACP, 0, (PWSTR) pUnicodeBuf, -1, nullptr, 0, nullptr, FALSE);
        WideCharToMultiByte(CP_ACP, 0, (PWSTR) pUnicodeBuf, -1, (LPSTR) pDestChar, aLen, nullptr, FALSE);
        // Unicode转ANSI
        free(pUnicodeBuf);
    }
    return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char *) NotUsed);
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static int getAutoIncrementID(void *NotUsed, int argc, char **argv, char **azColName) {
    int *p = (int *) NotUsed;
    if (argc == 1) {
        *p = std::stoi(argv[0]);
    }
    return 0;
}

static int readHistoryRow(void *pData, int argc, char **argv, char **azColName) {
    auto *batchList = (std::vector<photoBatch> *) pData;
    if (argc == 7) {//todo read into a map vector
        photoBatch batch;
        batch.execID = atoi(argv[0]);
        //batch.rootDir = argv[1];
        batch.scanDir = wxString::FromUTF8(argv[1]);
        batch.scanTime = (time_t) atol(argv[2]);
        batch.fileCount = atoi(argv[3]);
        batch.keepPriority = atoi(argv[5]);
        batch.removeCount = atoi(argv[6]);
        batchList->emplace_back(batch);
    }

    return 0;
}

int getRepeat(wxFrame *frame) {
    std::string select = "select * from photofile where sha256 in("
                         "select sha256 from photofile group by sha256 having count(sha256)>1) order by  sha256";

    char *zErrMsg;
    int rc = sqlite3_exec(db, select.c_str(), readHistoryRow, &batchList, &zErrMsg);
    if (rc != SQLITE_OK) {
        wxLogStatus(frame, wxString::Format("SQL error: %s", sqlite3_errmsg(db)), 2);
        sqlite3_free(zErrMsg);
    } else {
        wxQueueEvent(frame, new wxThreadEvent(wxEVT_COMMAND_READBATCH));
    }

    return batchList.size();
}

int getHistory(wxFrame *frame) {
    batchList.clear();
    std::string selectBatch = "select execID,scanDir,scanTime,fileCount,totalSize,keepPriority,removeCount from photoBatch where filecount>0 order by keepPriority desc,execID asc";

    char *zErrMsg;
    int rc;
    /* Open database */
    /* rc = sqlite3_open("photofile.db", &db);//_v2,SQLITE_OPEN_READONLY, nullptr
     if (rc) {
         wxLogStatus(frame, wxString::Format("Can't open database: %s", sqlite3_errmsg(db)), 1);
         // exit(0);
     } else {*/
    rc = sqlite3_exec(db, selectBatch.c_str(), readHistoryRow, &batchList, &zErrMsg);
    if (rc != SQLITE_OK) {
        wxLogStatus(frame, wxString::Format("SQL error: %s", sqlite3_errmsg(db)), 2);
        sqlite3_free(zErrMsg);
    } else {
        wxQueueEvent(frame, new wxThreadEvent(wxEVT_COMMAND_READBATCH));
    }
    //}

    //sqlite3_close(db);

    return batchList.size();
}

int saveDb(const wxString rootDir, wxFrame *frame) {
    //sqlite3 *db;
    char *zErrMsg;
    int rc;
    int insertRecordCount = 0;
    std::string batchTemplate = "INSERT INTO photobatch (scanDir,scanTime,fileCount) values('%s',%d,%d);";
    std::string queryExecID = "SELECT seq FROM sqlite_sequence WHERE name='photobatch'";
    std::string sqlTemplate = "INSERT INTO photofile (filename,execID,createTime,modifyTime,fileSize,sha256) VALUES('%s',%d,%d,%d,%d,'%s');";

    /* Open database */
    /*rc = sqlite3_open("photofile.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        wxLogStatus(frame, "Opened database successfully", 2);
    }*/
    char sql[8192];
    //memset(sql8, 0x00, 8192);
    // char *strc=new char(strlen(rootDir.c_str())+1);
    // strcpy(strc,rootDir.c_str());
    /** photobatch **/
    sprintf(sql, batchTemplate.c_str(), rootDir.ToUTF8().data(), time(nullptr),
            file256List.size());//error rootDir.To8BitData().data()

    //CodePageConvert(CP_UTF8, (void *) sql8, CP_ACP, sql);
    rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        return 0;
    }
    // todo query auto increment id
    /** query photobatch autoincrement id **/
    int autoIncrementID;
    rc = sqlite3_exec(db, queryExecID.c_str(), getAutoIncrementID, &autoIncrementID, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    /* Create SQL statement */
    int k = 1;
    char *sql8 = new char[8192];
    for (int i = 0; i < file256List.size(); i++) {
        filesha256 file = file256List.at(i);
        sprintf(sql, sqlTemplate.c_str(), file.filename.c_str(), autoIncrementID,
                file.createTime, file.modifyTime, file.fileSize, sha256.at(i).c_str());

        memset(sql8, 0x00, 8192);
        CodePageConvert(CP_UTF8, (void *) sql8, CP_ACP, sql);
        /* sqlTemplate=wxString::Format("INSERT INTO photofile (filename,execID,createTime,modifyTime,fileSize,sha256) VALUES('%s',%i,%i,%i,%i,'%s')",
                 file.filename,file.createTime, file.modifyTime, file.fileSize, file.sha256.c_str());*/
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql8, callback, nullptr, &zErrMsg);// error sql9(3)\To8BitData(3)\ToStdString (3)
        if (rc != SQLITE_OK) {
            wxLogStatus(frame, zErrMsg, 1);
            sqlite3_free(zErrMsg);
        } else {
            insertRecordCount++;
        }
        if (i > file256List.size() / 99.0 * k) {
            wxThreadEvent evt(wxEVT_COMMAND_SAVEDB_UPDATE);
            evt.SetInt(k++);
            wxQueueEvent(frame, evt.Clone());
        }
    }
    delete[] sql8;
    //sqlite3_close(db);
    wxThreadEvent evt(wxEVT_COMMAND_SAVEDB_UPDATE);
    evt.SetInt(100);
    wxQueueEvent(frame, evt.Clone());
    return insertRecordCount;
}

int deletePhotoBatch(const int execID, wxFrame *frame) {
    wxString deleteFile = wxString::Format("DELETE FROM photoFile  WHERE execID=%i", execID);
    wxString deleteBatch = wxString::Format("DELETE FROM photoBatch  WHERE execID=%i", execID);

    //sqlite3 *db;
    char *zErrMsg;
    int rc;
    /* Open database */
    /* rc = sqlite3_open("photofile.db", &db);//_v2,SQLITE_OPEN_READONLY, nullptr
     if (rc) {
         wxLogStatus(frame, wxString::Format("Can't open database: %s", sqlite3_errmsg(db)), 1);
     } else {*/
    rc = sqlite3_exec(db, deleteFile.data(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        wxLogStatus(frame, wxString::Format("SQL error: %s", sqlite3_errmsg(db)), 1);
        sqlite3_free(zErrMsg);
    } else {
        rc = sqlite3_exec(db, deleteBatch.data(), nullptr, nullptr, &zErrMsg);
        if (rc != SQLITE_OK) {
            wxLogStatus(frame, wxString::Format("SQL error: %s", sqlite3_errmsg(db)), 1);
            sqlite3_free(zErrMsg);
        } else
            wxLogStatus(frame, wxT("删除成功"), 1);
    }
    //  }

    //sqlite3_close(db);

    getHistory(frame);

    return 0;
}


int updateBatch(const int execID, const int keepPriority, wxFrame *frame) {
    wxString updatePriority = wxString::Format("UPDATE PhotoBatch SET keepPriority=%i WHERE execID=%i", keepPriority,
                                               execID);

    //sqlite3 *db;
    char *zErrMsg;
    int rc;
    /* Open database */
    /* rc = sqlite3_open("photofile.db", &db);//_v2,SQLITE_OPEN_READONLY, nullptr
     if (rc) {
         wxLogStatus(frame, wxString::Format("Can't open database: %s", sqlite3_errmsg(db)), 3);
     } else {*/
    rc = sqlite3_exec(db, updatePriority.data(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        wxLogStatus(frame, wxString::Format("SQL error: %s", sqlite3_errmsg(db)), 3);
        sqlite3_free(zErrMsg);
    } else
        wxLogStatus(frame, wxT("修改优先级成功"), 1);
    /* }

     sqlite3_close(db);*/
    getHistory(frame);
    return 0;
}
