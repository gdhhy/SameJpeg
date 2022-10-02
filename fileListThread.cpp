//
// Created by gzhhy on 2022/5/17.
//
#include <boost/filesystem/path.hpp>

#include <deque>
#include "fileListThread.h"
#include <wx/app.h>

extern "C"
{
#include "sha256md5.h"
}
extern std::vector<filesha256> file256List;
extern std::vector<std::string> sha256;

void postThreadEvent(JpegFileFrame *m_pHandler, const int eventID, const wxString message, int messageInt) {
    wxThreadEvent evt(wxEVT_THREAD, eventID);
    evt.SetString(message);
    evt.SetInt(messageInt); // 10%是搜索文件，90%是计算sha256
    wxQueueEvent(m_pHandler, evt.Clone());
}
static int gauge = 1;
double complexity = 0, complexity2 = 0; //按文件大小计算sha256的复杂度
wxThread::ExitCode MyThread::Entry() {

    float targetFileCount = 100.0;//预计100个文件，按2指数增加
//    const int findFileRatio = 100;
    wxThreadEvent e(wxEVT_THREAD); // declared and implemented somewhere

    //遍历文件夹，列出所有文件
    std::deque<fs::path> deque;

    deque.push_front(src_path);
    while (!deque.empty()) {
        fs::path src = (fs::path) deque.back();

        fs::directory_iterator end; //迭代器的终点
        for (fs::directory_iterator dir(src); dir != end; dir++) {

            if (TestDestroy())
                break;

            if (fs::is_regular_file(*dir)) { //非目录，即是普通文件
                wxCriticalSectionLocker enter(wxGetApp().m_critsect);//与刷新listctrl互斥
                filesha256 file;
                //file.filename = wxString::FromAscii(dir->path().string().data());
                file.filename = dir->path().string();
                file.fileSize = fs::file_size(dir->path());
                file.modifyTime = fs::last_write_time(dir->path());
                file.createTime = fs::creation_time(dir->path());
                file256List.emplace_back(file);

                if (file.fileSize)
                    complexity += log(file.fileSize) / log(1024 * 1024  );
                if (floor(targetFileCount) < file256List.size() && gauge < 100) {
                    targetFileCount = targetFileCount * 1.05;//100次方1.3万
                    postThreadEvent(m_pHandler, ID_THREAD_UPDATE, wxT("搜索文件"), gauge++);
                    //wxLogDebug(wxT("targetFileCount:%f,gauge:%d,complexity:%f,log:%f,fileSize:%lu"), targetFileCount, gauge, complexity, log(file.fileSize) / log(1024 * 1024 * 10), file.fileSize);
                }
            } else if (fs::is_directory(*dir))
                deque.push_front(dir->path());
        }

        deque.pop_back();
    }
    postThreadEvent(m_pHandler, ID_THREAD_UPDATE, wxT("搜索文件"), 100);
    //wxLogDebug(wxT("***************************文件总数：%d"), file256List.size());//

    //*********************计算sha256****************************
    //todo multi thread calc sha256
    char SHA256result[65];
    gauge = 0;
    for (int i = 0; i < file256List.size(); i++) {
        if (TestDestroy())
            break;

        //sha256_file((char *) file256List[i].filename.To8BitData().data(), SHA256result);//error toUtf8,ToStdString,-------OK:To8BitData
        sha256_file((char *) file256List[i].filename.c_str(), SHA256result);
        sha256.emplace_back(SHA256result);
        if (file256List[i].fileSize > 0)//不能少这个比较
            complexity2 += log(file256List[i].fileSize) / log(1024 * 1024 );
        if (gauge < ceil(100 * complexity2 / complexity)) {
            gauge = ceil(100 * complexity2 / complexity);
            postThreadEvent(m_pHandler, ID_SHA256_UPDATE, wxT("计算SHA256"), gauge);
        }
    }
    postThreadEvent(m_pHandler, ID_SHA256_UPDATE, wxT("计算SHA256"), 100);//怕%10有余数

    return (wxThread::ExitCode) 0;
}
void threadSha256(JpegFileFrame *m_pHandler,int begin,int end){
    char SHA256result[65];
    gauge = 0;
    for (int i = begin; i < end; i++) {

        //sha256_file((char *) file256List[i].filename.To8BitData().data(), SHA256result);//error toUtf8,ToStdString,-------OK:To8BitData
        sha256_file((char *) file256List[i].filename.c_str(), SHA256result);
        sha256.emplace_back(SHA256result);

        if (file256List[i].fileSize > 0)//不能少这个比较
            complexity2 += log(file256List[i].fileSize) / log(1024 * 1024 );
        if (gauge < ceil(100 * complexity2 / complexity)) {
            gauge = ceil(100 * complexity2 / complexity);
            postThreadEvent(m_pHandler, ID_SHA256_UPDATE, wxT("计算SHA256"), gauge);
        }
    }
    postThreadEvent(m_pHandler, ID_SHA256_UPDATE, wxT("计算SHA256"), 100);//怕%10有余数
}

MyThread::~MyThread() {
    wxCriticalSectionLocker enter(wxGetApp().m_critsect);
    wxGetApp().th = nullptr;
    wxLogDebug("MyThread::~MyThread");
}
