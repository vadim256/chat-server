/***************************************************************
 * Name:      ServerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Vadim Kondratyuk (kvadiml256@gmail.com)
 * Created:   2019-03-08
 * Copyright: Vadim Kondratyuk (github.com/vadim256)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ServerApp.h"

//(*AppHeaders
#include "ServerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ServerApp);

ServerApp::ServerApp()
{
    m_locale.Init(wxLANGUAGE_UKRAINIAN);
}

bool ServerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ServerFrame* Frame = new ServerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    return wxsOK;
}
