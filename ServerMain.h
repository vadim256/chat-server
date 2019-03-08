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
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)
#include <memory>

#include <wx/socket.h>
#include <wx/hashmap.h>
#include <wx/valgen.h>
#include <wx/string.h>
#include <cassert>
#include <cmath>

WX_DECLARE_HASH_MAP(wxSOCKET_T, wxSocketBase*, wxIntegerHash, wxIntegerEqual, mySocketHashMap);

class ServerFrame: public wxFrame
{
    public:

        ServerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ServerFrame();

    private:
        void CreateControls();
        bool InitializeSocketServer();
        //(*Handlers(ServerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)
        void OnSocketEventServer(wxSocketEvent &);
        void OnSocketEventClient(wxSocketEvent &);

        //(*Identifiers(ServerFrame)
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long idSocketServer;
        static const long idSocketClient;

        //(*Declarations(ServerFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        //*)
        std::unique_ptr<wxSocketServer> m_PtrServer;
        mySocketHashMap m_HashMapClients;
        DECLARE_EVENT_TABLE()
};

#endif // SERVERMAIN_H
