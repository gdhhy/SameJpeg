//
// Created by gzhhy on 2022/6/4.
//

#include "SearchPanel.h"
#include "sqlfunc.h"
#include <boost/thread.hpp>

SearchPanel::SearchPanel(wxFrame *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style,
                         const wxString &name) {
    wxPanel::Create(parent, winid, pos, size, style, name);
    this->p_frame = parent;
    auto *bSizer1 = new wxBoxSizer(wxVERTICAL);
    m_auiToolBar1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT);
    m_btn_loadRepeat = new wxButton(m_auiToolBar1, wxID_ANY, wxT("加载"), wxDefaultPosition, wxSize(120, -1), 0);
    m_btn_loadRepeat->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_auiToolBar1->AddControl(m_btn_loadRepeat);

    m_btn_deleteRepeat = new wxButton(m_auiToolBar1, wxID_ANY, wxT("删除重复"), wxDefaultPosition, wxSize(120, -1), 0);
    m_btn_deleteRepeat->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_auiToolBar1->AddControl(m_btn_deleteRepeat);

    m_auiToolBar1->Realize();
    m_listCtrl1 = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    m_listCtrl1->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    bSizer1->Add(m_auiToolBar1, 0, wxALL, 0);
    bSizer1->Add(m_listCtrl1, 1, wxEXPAND, 5);

    this->SetSizer(bSizer1);
    this->Layout();
    bSizer1->Fit(this);

    m_listCtrl1->AppendColumn(wxT("序号"), wxLIST_FORMAT_CENTER, 45);
    m_listCtrl1->AppendColumn(wxT("目录"), wxLIST_FORMAT_LEFT, 200);
    m_listCtrl1->AppendColumn(wxT("扫描时间"), wxLIST_FORMAT_LEFT, 180);
    m_listCtrl1->AppendColumn(wxT("文件数量"), wxLIST_FORMAT_LEFT, 80);
    m_listCtrl1->AppendColumn(wxT("优先级"), wxLIST_FORMAT_LEFT, 70);
    m_listCtrl1->AppendColumn(wxT("删除数"), wxLIST_FORMAT_LEFT, 70);

    m_btn_loadRepeat->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(SearchPanel::loadRepeat), NULL, this);
};

SearchPanel::~SearchPanel() {
    m_btn_loadRepeat->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(SearchPanel::loadRepeat), NULL, this);
}

void SearchPanel::loadRepeat(wxMouseEvent &event) {
    // getHistory()
    //updateBatch(batchList.at(item_selected).execID, value, this);
    //boost::thread readBatch{getRepeat(this->p_frame), this};
}