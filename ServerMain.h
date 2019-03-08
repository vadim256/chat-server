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

class ServerFrame: public wxFrame
{
    public:

        ServerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ServerFrame();

    private:

        //(*Handlers(ServerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(ServerFrame)
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ServerFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SERVERMAIN_H
