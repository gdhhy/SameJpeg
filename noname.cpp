///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////
enum {
    ID_BTN_PAUSE,
    ID_BTN_SAVEDB
};


MyFrame1::MyFrame1(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size,
                   long style) : wxFrame(parent, id, title, pos, size, style) {
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    this->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));

    wxBoxSizer *bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    m_auinotebook1 = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
    m_auinotebook1->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));

    m_panel1 = new wxPanel(m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_panel1->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));

    wxBoxSizer *bSizer3;
    bSizer3 = new wxBoxSizer(wxVERTICAL);

    m_auiToolBar1 = new wxAuiToolBar(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORIZONTAL | wxAUI_TB_VERTICAL);
    m_staticText1 = new wxStaticText(m_auiToolBar1, wxID_ANY, wxT("目录："), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText1->Wrap(-1);
    m_auiToolBar1->AddControl(m_staticText1);
    m_textCtrl2 = new wxTextCtrl(m_auiToolBar1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0);
    m_auiToolBar1->AddControl(m_textCtrl2);
    m_button2 = new wxButton(m_auiToolBar1, wxID_ANY, wxT("浏览"), wxDefaultPosition, wxDefaultSize, 0);
    m_button2->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_auiToolBar1->AddControl(m_button2);
    m_button3 = new wxButton(m_auiToolBar1, ID_BTN_PAUSE, wxT("暂停"), wxDefaultPosition, wxDefaultSize, 0);
    m_button3->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_button3->Disable();
    m_auiToolBar1->AddControl(m_button3);
    m_btnSave = new wxButton(m_auiToolBar1, ID_BTN_SAVEDB, wxT("存档"), wxDefaultPosition, wxDefaultSize, 0);
    m_btnSave->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_btnSave->Disable();
    m_auiToolBar1->AddControl(m_btnSave);
    m_auiToolBar1->Realize();

    m_statusBar1 = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
    int widths[] = {400, 300}; //状态条从左起，每隔的长度
    m_statusBar1->SetFieldsCount(WXSIZEOF(widths), widths);
    m_statusBar1->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_statusBar1->SetStatusText(wxT("状态条"), 0);

    wxRect rc;
    m_statusBar1->GetFieldRect(1, rc);
    m_gauge1 = new wxGauge(m_statusBar1, wxID_ANY, 1000, wxPoint(rc.x, rc.y), wxSize(rc.width, rc.height), wxGA_HORIZONTAL);
    // m_gauge1->SetValue(10);
    m_gauge1->Show(true);

    bSizer3->Add(m_auiToolBar1, 0, wxALL, 0);

    m_listCtrl1 = new wxListCtrl(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    m_listCtrl1->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    bSizer3->Add(m_listCtrl1, 1, wxEXPAND, 5);//在wxBoxSizer中用Add方法的第二个参数来控制控件是否可以自由伸展来填充面板其它未占用的地方，
    // 第三个参数控制控件向哪个方向伸展，有上下左右四个方向，wxALL表示四个方向都可以伸展。

    m_panel1->SetSizer(bSizer3);
    m_panel1->Layout();
    bSizer3->Fit(m_panel1);
    m_auinotebook1->AddPage(m_panel1, wxT("文件搜索"), false, wxNullBitmap);

    bSizer1->Add(m_auinotebook1, 1, wxEXPAND, 1);

    m_panel2 = new wxPanel(m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_panel2->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));

    auto *bSizer6 = new wxBoxSizer(wxVERTICAL);

    m_auiToolBar2 = new wxAuiToolBar(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT);
    m_button6 = new wxButton(m_auiToolBar2, wxID_ANY, wxT("设置优先级"), wxDefaultPosition, wxSize( 120,-1 ), 0);
    m_button6->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_button6->Enable(false);
    m_auiToolBar2->AddControl(m_button6);
    m_button7 = new wxButton(m_auiToolBar2, wxID_ANY, wxT("删除"), wxDefaultPosition, wxDefaultSize, 0);
    m_button7->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_button7->Enable(false);
    m_auiToolBar2->AddControl(m_button7);
    m_button8 = new wxButton(m_auiToolBar2, wxID_ANY, wxT("加载比较"), wxDefaultPosition, wxDefaultSize, 0);
    m_button8->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("宋体")));
    m_button8->Enable(false);
    m_auiToolBar2->AddControl(m_button8);
    m_auiToolBar2->Realize();

    bSizer6->Add(m_auiToolBar2, 0, wxALL, 0);

    m_listCtrl3 = new wxListCtrl(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    bSizer6->Add(m_listCtrl3, 1, wxEXPAND, 5);


    m_panel2->SetSizer(bSizer6);
    m_panel2->Layout();
    bSizer6->Fit(m_panel2);
    m_auinotebook1->AddPage(m_panel2, wxT("历史"), false, wxNullBitmap);

    //自定义的 SearchPanel
    m_panel3 = new SearchPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_auinotebook1->AddPage(m_panel3, wxT("重复文件"), false, wxNullBitmap);

    m_listCtrl1->AppendColumn(wxT("序号"), wxLIST_FORMAT_CENTER, 45);
    m_listCtrl1->AppendColumn(wxT("文件名"), wxLIST_FORMAT_LEFT, 300);
    m_listCtrl1->AppendColumn(wxT("SHA256"), wxLIST_FORMAT_LEFT, 400);
    //m_listCtrl1->wxWindow::Update();

    m_listCtrl3->AppendColumn(wxT("序号"), wxLIST_FORMAT_CENTER, 45);
    m_listCtrl3->AppendColumn(wxT("目录"), wxLIST_FORMAT_LEFT, 200);
    m_listCtrl3->AppendColumn(wxT("扫描时间"), wxLIST_FORMAT_LEFT, 180);
    m_listCtrl3->AppendColumn(wxT("文件数量"), wxLIST_FORMAT_LEFT, 80);
    m_listCtrl3->AppendColumn(wxT("优先级"), wxLIST_FORMAT_LEFT, 70);
    m_listCtrl3->AppendColumn(wxT("删除数"), wxLIST_FORMAT_LEFT, 70);

    //m_listCtrl3->wxWindow::Update();

    this->SetSizer(bSizer1);
    this->Layout();

    this->Centre(wxBOTH);

    // Connect Events
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::onClose));
    m_button2->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::clickChoosePath), NULL, this);
    m_button3->Connect(ID_BTN_PAUSE, wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::clickStopThread), NULL, this);
    Connect(ID_BTN_SAVEDB, wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::saveToDb));

    m_button6->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::modifyBatch), NULL, this);
    m_button7->Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::removeBatch), NULL, this);
    m_button8->Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::loadBatch), NULL, this);

    m_listCtrl3->Connect(wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler(MyFrame1::deselectedRow), NULL, this);
    m_listCtrl3->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(MyFrame1::selectedRow), NULL, this);
    m_listCtrl3->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::modifyBatch ), NULL, this );
}

MyFrame1::~MyFrame1() {
    // Disconnect Events
    this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::onClose));
    m_button2->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::clickChoosePath), NULL, this);
    m_button3->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::clickStopThread), NULL, this);
    m_btnSave->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::saveToDb), NULL, this);
    m_button6->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::modifyBatch), NULL, this);
    m_button7->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::removeBatch), NULL, this);
    m_button8->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxMouseEventHandler(MyFrame1::loadBatch), NULL, this);
}

 