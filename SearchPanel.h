//
// Created by gzhhy on 2022-06-03.
//

#ifndef JPEGFILE_SEARCHPANEL_H
#define JPEGFILE_SEARCHPANEL_H

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
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/aui/auibar.h>
#endif //JPEGFILE_SEARCHPANEL_H


class SearchPanel : public wxPanel {
protected:
   // JpegFileFrame *p_frame;
    wxAuiToolBar *m_auiToolBar1;
    wxButton *m_btn_loadRepeat;
    wxButton *m_btn_deleteRepeat;
    wxListCtrl *m_listCtrl1;

    virtual void loadRepeat(wxMouseEvent &event);

public:
    SearchPanel(wxAuiNotebook *parent,
                wxWindowID winid = wxID_ANY,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString &name = wxASCII_STR(wxPanelNameStr));

    ~SearchPanel();
};