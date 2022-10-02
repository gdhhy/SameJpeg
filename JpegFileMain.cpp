/***************************************************************
 * Name:      JpegFIleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    gzhhy ()
 * Created:   2022-05-09
 * Copyright: gzhhy ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "JpegFileMain.h"

#include "wx/dirdlg.h"
#include <boost/filesystem.hpp>
#include "fileListThread.h"
#include "wx/wxprec.h"
#include "wx/app.h"
#include "sqlfunc.h"
#include <boost/thread.hpp>
#include <wx/msgdlg.h>
#include "wx/numdlg.h"

namespace fs = boost::filesystem;


std::vector<filesha256> file256List;
std::vector<std::string> sha256;
std::vector<photoBatch> batchList;

// helper functions
enum wxbuildinfoformat {
    short_f,
    long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f) {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

// EVT_COMMAND、EVNT_THREAD，两种事件定义都使用！
wxBEGIN_EVENT_TABLE(JpegFileFrame, wxFrame)
// EVT_CLOSE(JpegFileFrame::OnClose)
// EVT_MENU(Minimal_Start, JpegFileFrame::DoStartThread)
                EVT_THREAD(ID_THREAD_UPDATE, JpegFileFrame::OnFindFileUpdate)
                EVT_THREAD(ID_SHA256_UPDATE, JpegFileFrame::OnSha256Update)
                //EVT_THREAD(ID_THREAD_COMPLETE, JpegFileFrame::OnThreadCompletion)
                EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_SAVEDB_UPDATE, JpegFileFrame::saveDbUpdate)
                //EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_SAVEDB_COMPLETED, JpegFileFrame::saveDbCompletion)
                EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_READBATCH, JpegFileFrame::showHistory)
wxEND_EVENT_TABLE();


// wxDEFINE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxCommandEvent);
// wxDEFINE_EVENT(wxEVT_COMMAND_MYTHREAD_COMPLETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SAVEDB_UPDATE, wxCommandEvent);
//wxDEFINE_EVENT(wxEVT_COMMAND_SAVEDB_COMPLETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_READBATCH, wxCommandEvent);

JpegFileFrame::JpegFileFrame(wxFrame *frame) : MyFrame1(frame) {
    /*#if wxUSE_STATUSBAR
        statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
        statusBar->SetStatusText(wxbuildinfo(short_f), 1);
    #endif*/
    //   getHistory(this);
    m_gauge1->SetRange(100);

    int rc;
    /* Open database */
    rc = sqlite3_open("photofile.db", &db);//_v2,SQLITE_OPEN_READONLY, nullptr
    if (rc) {
        wxLogStatus(frame, wxString::Format("Can't open database: %s", sqlite3_errmsg(db)), 1);
        // exit(0);
    } else
        boost::thread readBatch{getHistory, this};
}

JpegFileFrame::~JpegFileFrame() {
    sqlite3_close(db);
}

void JpegFileFrame::onClose(wxCloseEvent &event) {
    Destroy();
}

void JpegFileFrame::OnQuit(wxCommandEvent &event) {
    Destroy();
}

void JpegFileFrame::OnAbout(wxCommandEvent &event) {
    wxString msg = wxbuildinfo(long_f);
}

static int k = 0;

void JpegFileFrame::clickChoosePath(wxMouseEvent &event) {
    MyFrame1::clickChoosePath(event);
    // wxMessageBox("asfasdf\n");
    wxString defaultPath = wxT("/");
    wxDirDialog dialog(this->m_parent,
                       wxT("选择一个包含相片目录"),
                       defaultPath, wxDD_NEW_DIR_BUTTON);

    if (dialog.ShowModal() == wxID_OK) {
        wxString pathStr = dialog.GetPath();
        m_textCtrl2->ChangeValue(pathStr);
        m_textCtrl2->wxWindow::Update();
        /* if (wxGetApp().th)
             wxGetApp().th->Kill();*///放在线程德析构函数
        file256List.clear();
        sha256.clear();
        k = 0;
        m_gauge1->SetValue(0);
        wxLogStatus(this, pathStr, 1);

        if (m_listCtrl1->DeleteAllItems())
            m_listCtrl1->wxWindow::Update();
        fs::path pt(pathStr.ToStdString());

        wxGetApp().th = new MyThread(this, pt);
        wxGetApp().th->Create();
        wxGetApp().th->Run();
        m_button3->Enable(true);
        m_button3->wxWindow::Update();
    }
}

void JpegFileFrame::clickStopThread(wxMouseEvent &WXUNUSED(event)) {
    //    MyFrame1::clickStopThread(event);
    wxLogStatus(this, wxT("点击暂停"), 1);
    // wxGetApp().thread_running=!wxGetApp().thread_running;
    if (wxGetApp().th) {
        wxCriticalSectionLocker enter(wxGetApp().m_critsect);
        if (wxGetApp().th->IsAlive()) {
            if (wxGetApp().th->IsPaused()) {
                wxGetApp().th->Resume();
                wxLogStatus(this, wxT("Thread Resume!"));
                m_button3->SetLabelText(wxT("暂停"));
            } else if (wxGetApp().th->IsRunning()) {
                wxGetApp().th->Pause();
                m_button3->SetLabelText(wxT("恢复"));
                wxLogStatus(this, wxT("Thread paused."), 1);
            }
        }
    }
}


void JpegFileFrame::OnFindFileUpdate(wxThreadEvent &e) {
    wxLogStatus(this, e.GetString(), 1);
    m_gauge1->SetValue(e.GetInt());

    unsigned long strLen = m_textCtrl2->GetValue().Length();
    int vector_size = file256List.size();//warnning:不能放在循环里面比较！！（没有wxCriticalSectionLocker，一定要独立这一行）
    //wxLogDebug(wxString::Format(wxT("i1=%i"), i));
    //wxLogDebug(wxString::Format(wxT("---------k=%i"), i));

    wxCriticalSectionLocker enter(wxGetApp().m_critsect);//与搜索文件线程互斥，否则没有逐渐刷新的动态效果
    for (int i = m_listCtrl1->GetItemCount(); i < vector_size; i++) {
        wxString fn(file256List.at(i).filename);
        fn.replace(0, strLen + 1, "");
        /*wxString fn(file256List.at(i).filename.To8BitData());//error no To
        fn.Replace(m_textCtrl2->GetValue(), wxEmptyString, true);//error no To
        fn.replace(0,  1, wxEmptyString);*/

        m_listCtrl1->InsertItem(i, wxString::Format("%i", i + 1));
        m_listCtrl1->SetItem(i, 1, fn);
        m_listCtrl1->SetItem(i, 2, "");
    }
    //wxLogDebug(wxString::Format(wxT("i2=%i"), i));
    m_listCtrl1->EnsureVisible(m_listCtrl1->GetItemCount() - 1);

    m_gauge1->Update();
    m_listCtrl1->wxWindow::Update();
}

void JpegFileFrame::OnSha256Update(wxThreadEvent &e) {
    wxLogStatus(this, e.GetString(), 1);
    m_gauge1->SetValue(e.GetInt());

    for (; k < sha256.size() && k < m_listCtrl1->GetItemCount(); k++) {
        m_listCtrl1->SetItem(k, 2, sha256.at(k));
    }

    m_listCtrl1->EnsureVisible(k);
    m_gauge1->Update();
    m_listCtrl1->wxWindow::Update();
    if (e.GetInt() >= 100) {
        m_button4->Enable();
    }
}

void JpegFileFrame::saveToDb(wxMouseEvent &) {
    // saveDb(m_textCtrl2->GetValue().ToStdString(),this);
    wxLogStatus(this, wxT("点击存档"), 1);
    boost::thread second{saveDb, m_textCtrl2->GetValue(), this}; // std::thread can't run,exit code is 3
    // very ok!!!
}


void JpegFileFrame::saveDbUpdate(wxCommandEvent &e) {
    if (e.GetInt() < 100)
        wxLogStatus(this, wxT("存档中"), 1);
    else {
        wxLogStatus(this, wxT("存档完成"), 1);
        boost::thread readBatch{getHistory, this};
        m_button4->Disable();//存档按钮
        m_button4->Update();
    }
    m_gauge1->SetValue(e.GetInt());
}

void JpegFileFrame::showHistory(wxCommandEvent &e) {
    //wxLogStatus(this, wxT("读入历史成功"), 1);
    m_listCtrl3->DeleteAllItems();
    for (int i = 0; i < batchList.size(); i++) {
        struct tm *p = localtime(&batchList.at(i).scanTime);
        m_listCtrl3->InsertItem(i, wxString::Format("%i", i + 1));
        m_listCtrl3->SetItem(i, 1, batchList.at(i).scanDir);
        m_listCtrl3->SetItem(i, 2, wxString::Format("%i-%02i-%02i %02i:%02i:%02i", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec));
        m_listCtrl3->SetItem(i, 3, wxString::Format("%i", batchList.at(i).fileCount));
        m_listCtrl3->SetItem(i, 4, wxString::Format("%i", batchList.at(i).keepPriority));
        m_listCtrl3->SetItem(i, 5, wxString::Format("%i", batchList.at(i).removeCount));
    }
    m_listCtrl3->wxWindow::Update();

    m_button6->Disable();
    m_button7->Disable();
}

long item_selected;

void JpegFileFrame::modifyBatch(wxMouseEvent &event) {
    wxNumberEntryDialog dialog(this, wxT("优先级数字越大，该目录下的文件优先保留。\n最大1000，最小0，谨慎设置。"),
                               wxT("优先级:"), wxT("设置优先级"), batchList.at(item_selected).keepPriority, 0, 1000);
    if (dialog.ShowModal() == wxID_OK) {
        long value = dialog.GetValue();
        updateBatch(batchList.at(item_selected).execID, value, this);
    }
}

void JpegFileFrame::removeBatch(wxMouseEvent &event) {
    if (wxMessageBox(wxString::Format(wxT("确定要删除目录：%s下文件数据吗？"), batchList.at(item_selected).scanDir), wxT("请确认"),
                     wxICON_QUESTION | wxYES_NO, this) == wxYES)
        deletePhotoBatch(batchList.at(item_selected).execID, this);
}

void JpegFileFrame::deselectedRow(wxListEvent &event) {
    m_button6->Disable();
    m_button7->Disable();
}

void JpegFileFrame::selectedRow(wxListEvent &event) {
    item_selected = event.GetItem();
    m_button6->Enable();
    m_button7->Enable();
}