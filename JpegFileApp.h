/***************************************************************
 * Name:      JpegFIleApp.h
 * Purpose:   Defines Application Class
 * Author:    gzhhy ()
 * Created:   2022-05-09
 * Copyright: gzhhy ()
 * License:
 **************************************************************/


#ifndef JPEGFILEAPP_H
#define JPEGFILEAPP_H

#include <wx/app.h>

//bool thread_running = true;
class JpegFileApp : public wxApp {
public:

    virtual bool OnInit();

    wxCriticalSection m_critsect;
    wxThread *th = nullptr;
};

DECLARE_APP(JpegFileApp);//有了这一行就可以使用JpegFileApp & wxGetApp()了
#endif // JPEGFILEAPP_H
