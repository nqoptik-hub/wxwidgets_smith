/***************************************************************
 * Name:      widgetsApp.h
 * Purpose:   Defines Application Class
 * Author:    Nguyen Quang (nqoptik@gmail.com)
 * Created:   2019-11-17
 * Copyright: Nguyen Quang (https://nqoptik.gitlab.io)
 * License:
 **************************************************************/

#ifndef WIDGETSAPP_H
#define WIDGETSAPP_H

#include <wx/app.h>

class widgetsApp : public wxApp
{
public:
    virtual bool OnInit();
};

#endif // WIDGETSAPP_H
