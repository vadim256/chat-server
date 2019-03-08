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



ServerFrame::ServerFrame(wxWindow* parent, wxWindowID id)
{
    //(*Initialize(ServerFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
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
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerFrame::OnAbout);
    //*)
    if(InitializeSocketServer() == false){
        //???
    }
    this->Connect(idSocketServer, wxEVT_SOCKET, wxSocketEventHandler(ServerFrame::OnSocketEventServer));
    this->Connect(idSocketClient, wxEVT_SOCKET, wxSocketEventHandler(ServerFrame::OnSocketEventClient));
}

ServerFrame::~ServerFrame()
{
    //(*Destroy(ServerFrame)
    //*)
    mySocketHashMap::iterator it = m_HashMapClients.begin();
    while(it != m_HashMapClients.end()){
        it->second->Destroy();
        ++it;
    }

    m_PtrServer->Destroy();
}

void ServerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ServerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

bool ServerFrame::InitializeSocketServer(){

    wxIPV4address address;
    address.Service(3000);
    m_PtrServer = std::make_unique<wxSocketServer>(address);
    if(m_PtrServer->IsOk() == FALSE) false;

    m_PtrServer->SetEventHandler(*this, idSocketServer);
    m_PtrServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
    m_PtrServer->Notify(TRUE);

    return true;
}

void ServerFrame::OnSocketEventServer(wxSocketEvent & event){

    switch(event.GetSocketEvent()){
        case wxSOCKET_CONNECTION:

            wxSocketBase * socket_slave = m_PtrServer->Accept(FALSE);
            if(!socket_slave->IsOk()) return;

            socket_slave->SetEventHandler(*this, idSocketClient);
            socket_slave->SetNotify(wxSOCKET_INPUT_FLAG|wxSOCKET_LOST_FLAG);
            socket_slave->Notify(TRUE);

            m_HashMapClients[socket_slave->GetSocket()] = socket_slave;
            break;
    /*    default:
            assert(FALSE);*/
    }
}

void ServerFrame::OnSocketEventClient(wxSocketEvent & event){
    wxSocketBase * socket_slave = event.GetSocket();
    wxIPV4address address;
    socket_slave->GetLocal(address);
    char msg_data[1024];
    switch(event.GetSocketEvent()){
        case wxSOCKET_INPUT:
        socket_slave->Read(msg_data, sizeof(char)*1024);
        if(socket_slave->Error()){

        } else{
            msg_data[static_cast<size_t>(ceil(static_cast<double>(socket_slave->LastCount()/sizeof(char))))] = wxT('\0');
            wxString msg = wxString::Format(wxT("%s>%s"), msg_data, address.IPAddress());
            for(mySocketHashMap::iterator it(m_HashMapClients.begin()); it != m_HashMapClients.end(); ++it)
                if(it->second->IsConnected())
                    it->second->Write(msg.GetData(), msg.Len()*sizeof(char));
        }
        break;

        case wxSOCKET_LOST:
            mySocketHashMap::iterator it;
            if((it = m_HashMapClients.find(socket_slave->GetSocket())) != m_HashMapClients.end())
                m_HashMapClients.erase(it);
            socket_slave->Destroy();
        break;
    }
}
