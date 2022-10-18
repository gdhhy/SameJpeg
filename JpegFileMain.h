/***************************************************************
 * Name:      JpegFIleMain.h
 * Purpose:   Defines Application Frame
 * Author:    gzhhy ()
 * Created:   2022-05-09
 * Copyright: gzhhy ()
 * License:
 **************************************************************/

#ifndef JPEGFILEMAIN_H
#define JPEGFILEMAIN_H

#include <wx/thread.h>


#include "JpegFileApp.h"
#include "noname.h"

struct filesha256 {
    std::string filename;
    time_t createTime;
    time_t modifyTime;
    int fileSize;
    std::string sha256;
};
struct photoBatch {
    int execID;
    //std::string rootDir;
    wxString scanDir;
    time_t scanTime;
    int fileCount;
    int keepPriority;
    int removeCount;
};
const int ID_THREAD_UPDATE = 100010;
const int ID_SHA256_UPDATE = 100310;
//const int ID_THREAD_COMPLETE = 101000;

// wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_COMPLETED, wxCommandEvent);
// wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_SAVEDB_UPDATE, wxCommandEvent);
//wxDECLARE_EVENT(wxEVT_COMMAND_SAVEDB_COMPLETED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_READBATCH, wxCommandEvent);

class JpegFileFrame : public MyFrame1 {
public:
    JpegFileFrame(wxFrame *frame);

    ~JpegFileFrame();

    //virtual void OnThreadCompletion(wxThreadEvent &);

    virtual void OnFindFileUpdate(wxThreadEvent &);

    virtual void OnSha256Update(wxThreadEvent &);

    virtual void saveToDb(wxMouseEvent &);

    virtual void saveDbUpdate(wxCommandEvent &);

    //virtual void saveDbCompletion(wxCommandEvent &);

    virtual void showHistory(wxCommandEvent &);
    //wxCriticalSection m_pThreadCS; // protects the m_pThread pointer
private:
    virtual void onClose(wxCloseEvent &event);

    virtual void OnQuit(wxCommandEvent &event);

    virtual void OnAbout(wxCommandEvent &event);

protected:
    void clickChoosePath(wxMouseEvent &event) override;

    void clickStopThread(wxMouseEvent &WXUNUSED(event)) override;

    void modifyBatch(wxMouseEvent &event) override;

    void removeBatch(wxMouseEvent &event) override;

    void loadBatch(wxMouseEvent &event) override;

    void deselectedRow(wxListEvent &event) override;

    void selectedRow(wxListEvent &event) override;

    //void dblClick(wxMouseEvent &event) override;
wxDECLARE_EVENT_TABLE();//不能放在函数声明中间
};

#endif // JPEGFILEMAIN_H
