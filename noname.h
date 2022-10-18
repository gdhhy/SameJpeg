///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/event.h>
#include <wx/gauge.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/aui/auibar.h>
#include "SearchPanel.h"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:
protected:
    wxAuiNotebook* m_auinotebook1;
    wxPanel* m_panel1;
    wxAuiToolBar* m_auiToolBar1;
    wxStaticText *m_staticText1;
    wxTextCtrl *m_textCtrl2;
    wxButton *m_button2;
    wxButton *m_button3;
    wxButton *m_btnSave;
    wxListCtrl *m_listCtrl1;
    wxGauge *m_gauge1;
    wxPanel* m_panel2;
    SearchPanel* m_panel3;
    wxAuiToolBar* m_auiToolBar2;
    wxButton* m_button6;
    wxButton* m_button7;
    wxButton* m_button8;
    wxListCtrl* m_listCtrl3;
    wxStatusBar *m_statusBar1;

    // Virtual event handlers, override them in your derived class
    virtual void onClose(wxCloseEvent &event) { event.Skip(); }
    virtual void clickChoosePath(wxMouseEvent &event) { event.Skip(); }
    virtual void clickStopThread(wxMouseEvent &event) { event.Skip(); }
    virtual void saveToDb(wxMouseEvent &event) { event.Skip(); }
    //Batch

    virtual void deselectedRow( wxListEvent& event ) { event.Skip(); }
    virtual void selectedRow( wxListEvent& event ) { event.Skip(); }

    virtual void modifyBatch(wxMouseEvent &event) { event.Skip(); }
    virtual void removeBatch(wxMouseEvent &event) { event.Skip(); }
    virtual void loadBatch(wxMouseEvent &event) { event.Skip(); }
   // virtual void dblClick( wxMouseEvent& event ) { event.Skip(); }
    //virtual void showHistory(wxMouseEvent &event) { event.Skip(); } //move to JpegFileMain.h

public:
    MyFrame1(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("照片重复管理"),
             const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(800, 600),
             long style = wxDEFAULT_FRAME_STYLE | wxBORDER_SUNKEN | wxTAB_TRAVERSAL);

    ~MyFrame1();
};
