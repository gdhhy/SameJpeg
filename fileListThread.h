//
// Created by gzhhy on 2022/5/17.
//

#ifndef JPEGFILE_FILELISTTHREAD_H
#define JPEGFILE_FILELISTTHREAD_H

#include <boost/filesystem.hpp>
#include <wx/thread.h>
#include <wx/frame.h>
#include "JpegFileMain.h"
#include <ctime>

#endif // JPEGFILE_FILELISTTHREAD_H
namespace fs = boost::filesystem;

class MyThread : public wxThread
{
public:
    MyThread(JpegFileFrame *frame, const fs::path &src_path )
    {
        m_pHandler = frame;
        this->src_path = src_path; 
    };

    virtual ExitCode Entry();

    virtual ~MyThread();

protected:
     fs::path src_path; 
    JpegFileFrame *m_pHandler;
};
