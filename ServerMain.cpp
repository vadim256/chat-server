/***************************************************************
 * Name:      ServerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Vadim Kondratyuk (kvadiml256@gmail.com)
 * Created:   2019-03-08
 * Copyright: Vadim Kondratyuk (github.com/vadim256)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ServerMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ServerFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
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

//(*IdInit(ServerFrame)
const long ServerFrame::ID_TEXTCTRL1 = wxNewId();
const long ServerFrame::ID_BUTTON1 = wxNewId();
const long ServerFrame::ID_TEXTCTRL2 = wxNewId();
const long ServerFrame::ID_SIMPLEHTMLLISTBOX1 = wxNewId();
const long ServerFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long ServerFrame::ID_PANEL1 = wxNewId();
const long ServerFrame::idMenuQuit = wxNewId();
const long ServerFrame::idMenuAbout = wxNewId();
const long ServerFrame::ID_STATUSBAR1 = wxNewId();
//*)

const long ServerFrame::idSocketClient = wxNewId();
const long ServerFrame::idSocketServer = wxNewId();

BEGIN_EVENT_TABLE(ServerFrame,wxFrame)
    //(*EventTable(ServerFrame)
    //*)
END_EVENT_TABLE()

ServerFrame::ServerFrame(wxWindow* parent, wxWindowID id) {
    //(*Initialize(ServerFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("wxChatServer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(500,500));
    SetMinSize(wxSize(350,350));
    SetForegroundColour(wxColour(196,237,255));
    SetBackgroundColour(wxColour(200,219,228));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("/home/ameliepulen/project1/chat-server/server_icon.png"))));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RICH|wxTE_RICH2, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer3->Add(TextCtrl1, 5, wxALL, 2);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("send"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND, 2);
    SplitterWindow1 = new wxSplitterWindow(Panel1, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DBORDER|wxSP_LIVE_UPDATE, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinimumPaneSize(50);
    SplitterWindow1->SetSashGravity(1);
    TextCtrl2 = new wxTextCtrl(SplitterWindow1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    SimpleHtmlListBox1 = new wxSimpleHtmlListBox(SplitterWindow1, ID_SIMPLEHTMLLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxHLB_DEFAULT_STYLE|wxHLB_MULTIPLE, wxDefaultValidator, _T("ID_SIMPLEHTMLLISTBOX1"));
    SplitterWindow1->SplitHorizontally(TextCtrl2, SimpleHtmlListBox1);
    BoxSizer2->Add(SplitterWindow1, 1, wxALL|wxEXPAND, 2);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 2);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ServerFrame::OnTextEnterAllClients);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerFrame::OnTextEnterAllClients);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerFrame::OnAbout);
    //*)
    TextCtrl1->SetValidator(wxGenericValidator(&m_AdminMsg));

    if(!InitializeSocketServer()){
        TextCtrl2->AppendText(_("[error] сould not start server\n"));
    } else {
        TextCtrl2->AppendText(_("[success] go\n"));
    }
    this->Connect(idSocketServer, wxEVT_SOCKET, wxSocketEventHandler(ServerFrame::OnSocketEventServer));
    this->Connect(idSocketClient, wxEVT_SOCKET, wxSocketEventHandler(ServerFrame::OnSocketEventClient));
}

ServerFrame::~ServerFrame() {
    //(*Destroy(ServerFrame)
    //*)
     for(wxSocketHash::iterator it = m_HashClients.begin(); it != m_HashClients.end(); ++it)
                    it->second->Destroy();

    if(m_SocketServer) m_SocketServer->Destroy();
}

void ServerFrame::OnQuit(wxCommandEvent& event) {
    Close();
}

void ServerFrame::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

bool ServerFrame::InitializeSocketServer() {

    wxIPV4address address;
    address.Service(3000);

    m_SocketServer = new wxSocketServer(address);
    if(!m_SocketServer->IsOk()) return false;

    m_SocketServer->SetEventHandler(*this, idSocketServer);
    m_SocketServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
    m_SocketServer->Notify(TRUE);

    return true;
}

void ServerFrame::OnSocketEventServer(wxSocketEvent & event) {

    switch(event.GetSocketEvent()){
        case wxSOCKET_CONNECTION:
            auto socket_slave = m_SocketServer->Accept(FALSE);
            if(!socket_slave){
                TextCtrl2->AppendText(wxT("[error] failed to attach client\n"));
                return;
            }
            socket_slave->SetEventHandler(*this, idSocketClient);
            socket_slave->SetNotify(wxSOCKET_INPUT_FLAG|wxSOCKET_LOST_FLAG);
            socket_slave->Notify(TRUE);
            m_HashClients[socket_slave->GetSocket()] = socket_slave;
            wxIPV4address address;
            socket_slave->GetLocal(address);
            TextCtrl2->AppendText(wxString::Format(_("[%s] new customer added\n"), address.IPAddress()));
            SimpleHtmlListBox1->Clear();
            for(auto it(m_HashClients.begin()); it != m_HashClients.end();++it){
                if(it->second->IsConnected()){
                    wxIPV4address address;
                    it->second->GetLocal(address);
                    SimpleHtmlListBox1->Append(wxString::Format(wxT("[%s]"), address.IPAddress()));
                }
            }
            break;
    }
}

void ServerFrame::OnSocketEventClient(wxSocketEvent & event) {
    auto socket_slave = event.GetSocket();
    wxIPV4address address;
    socket_slave->GetLocal(address);
    char msg_data[SIZE_MSG];
    switch(event.GetSocketEvent()){
        case wxSOCKET_INPUT:
        socket_slave->Read(msg_data, sizeof(char)*SIZE_MSG);
        if(socket_slave->Error()){
            TextCtrl2->AppendText(wxString(wxT("[error] сould not read message\n")));
        } else{
            msg_data[(size_t)ceil((double)socket_slave->LastCount()/sizeof(char))] = wxT('\0');
            wxString msg = wxString::Format(_T("[%s] %s"),address.IPAddress(), msg_data);
            TextCtrl2->AppendText(msg+wxString(wxT("\n")));
	        for(wxSocketHash::iterator it = m_HashClients.begin(); it != m_HashClients.end(); ++it)
                    if(it->second->IsConnected())
                       it->second->Write(msg.GetData(), msg.Length()*sizeof(char));
        }
        break;

        case wxSOCKET_LOST:

            TextCtrl2->AppendText(wxString::Format(_("[%s] detached customer\n"), address.IPAddress()));
             wxSocketHash::iterator it;
            if((it = m_HashClients.find(socket_slave->GetSocket())) != m_HashClients.end())
                m_HashClients.erase(it);

            if(socket_slave->IsOk())
                socket_slave->Destroy();
        break;
    }
}

void ServerFrame::OnTextEnterAllClients(wxCommandEvent& event) {
    TransferDataFromWindow();
    if(m_AdminMsg.IsNull()) return;
    m_AdminMsg = wxString(wxT("[admin] ")) + m_AdminMsg;
    TextCtrl2->AppendText(m_AdminMsg+wxString(wxT("\n")));

    for(auto it(m_HashClients.begin()); it != m_HashClients.end(); ++it){
        auto client = it->second;
        if(client){
            client->Write(m_AdminMsg.GetData(), m_AdminMsg.Len()*sizeof(char));
        }
    }
    m_AdminMsg.Clear();
    TransferDataToWindow();
}
