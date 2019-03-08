/***************************************************************
 * Name:      ServerApp.h
 * Purpose:   Defines Application Class
 * Author:    Vadim Kondratyuk (kvadiml256@gmail.com)
 * Created:   2019-03-08
 * Copyright: Vadim Kondratyuk (github.com/vadim256)
 * License:
 **************************************************************/

#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <wx/app.h>

class ServerApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // SERVERAPP_H
