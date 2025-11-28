/***************************************************************
 * Name:      widgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Nguyen Quang (nqoptik@gmail.com)
 * Created:   2019-11-17
 * Copyright: Nguyen Quang (https://nqoptik.gitlab.io)
 * License:
 **************************************************************/

#include "widgetsApp.h"

//(*AppHeaders
#include "widgetsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(widgetsApp);

bool widgetsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if (wxsOK) {
        widgetsFrame* Frame = new widgetsFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;
}
