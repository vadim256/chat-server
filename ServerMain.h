/***************************************************************
 * Name:      ServerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Vadim Kondratyuk (kvadiml256@gmail.com)
 * Created:   2019-03-08
 * Copyright: Vadim Kondratyuk (github.com/vadim256)
 * License:
 **************************************************************/

#ifndef SERVERMAIN_H
#define SERVERMAIN_H

//(*Headers(ServerFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/htmllbox.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)


#include <wx/socket.h>
#include <wx/valgen.h>
#include <wx/string.h>
#include <cmath>
#include <wx/hashmap.h>
WX_DECLARE_HASH_MAP(wxSOCKET_T, wxSocketBase *, wxIntegerHash, wxIntegerEqual, wxSocketHash);


class ServerFrame: public wxFrame {
public:
    explicit ServerFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~ServerFrame();
    enum {
        SIZE_MSG = 1024
    };
private:
        void CreateControls();
        bool InitializeSocketServer();
        //(*Handlers(ServerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextEnterAllClients(wxCommandEvent& event);
        //*)
        void OnSocketEventServer(wxSocketEvent &);
        void OnSocketEventClient(wxSocketEvent &);

        //(*Identifiers(ServerFrame)
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_SIMPLEHTMLLISTBOX1;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long idSocketServer;
        static const long idSocketClient;
        //(*Declarations(ServerFrame)
        wxButton* Button1;
        wxPanel* Panel1;
        wxSimpleHtmlListBox* SimpleHtmlListBox1;
        wxSplitterWindow* SplitterWindow1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl1;
        wxTextCtrl* TextCtrl2;
        //*)
        
        wxSocketServer * m_SocketServer;
        wxSocketHash m_HashClients;
        wxString m_AdminMsg;
        DECLARE_EVENT_TABLE()
};
#endif // SERVERMAIN_H
