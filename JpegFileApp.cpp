/***************************************************************
 * Name:      JpegFIleApp.cpp
 * Purpose:   Code for Application Class
 * Author:    gzhhy ()
 * Created:   2022-05-09
 * Copyright: gzhhy ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif


#include "JpegFileApp.h"
#include "JpegFileMain.h"

IMPLEMENT_APP(JpegFileApp);

bool JpegFileApp::OnInit()
{
    JpegFileFrame* frame = new JpegFileFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}