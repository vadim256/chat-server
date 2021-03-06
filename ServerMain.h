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
#include <stdexcept>
#include <wx/socket.h>
#include <wx/valgen.h>
#include <wx/string.h>
#include <cmath>
#include <wx/hashmap.h>
#include "SaveInDB.h"
#include <memory>

WX_DECLARE_HASH_MAP(wxSOCKET_T, wxSocketBase *, wxIntegerHash, wxIntegerEqual, wxSocketHash);

struct ServerFrame: wxFrame {

    explicit ServerFrame(wxWindow* parent, wxWindowID id = -1);
    virtual ~ServerFrame();


    static const int SIZE_MSG = 1024;

protected:

        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextEnterAllClients(wxCommandEvent& event);
        void OnSocketEventServer(wxSocketEvent &);
        void OnSocketEventClient(wxSocketEvent &);

private:
        bool CreateControls(wxWindow * parent, wxWindowID id);
        bool InitializeSocketServer();

        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_SIMPLEHTMLLISTBOX1;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long idSocketServer;
        static const long idSocketClient;


        wxButton* Button1;
        wxPanel* Panel1;
        wxSimpleHtmlListBox* SimpleHtmlListBox1;
        wxSplitterWindow* SplitterWindow1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl1;
        wxTextCtrl* TextCtrl2;

        wxBoxSizer* BoxSizer1;
        wxBoxSizer* BoxSizer2;
        wxBoxSizer* BoxSizer3;
        wxMenu* Menu1;
        wxMenu* Menu2;
        wxMenuBar* MenuBar1;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem2;

        wxSocketServer * m_SocketServer;
        wxSocketHash m_HashClients;
        wxString m_AdminMsg;
        std::unique_ptr<SaveInDB> m_PtrSave;
        DECLARE_EVENT_TABLE()
};
#endif // SERVERMAIN_H
