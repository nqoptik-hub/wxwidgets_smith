/***************************************************************
 * Name:      widgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Nguyen Quang (nqoptik@gmail.com)
 * Created:   2019-11-17
 * Copyright: Nguyen Quang (https://nqoptik.gitlab.io)
 * License:
 **************************************************************/

#ifndef WIDGETSMAIN_H
#define WIDGETSMAIN_H

//(*Headers(widgetsFrame)
#include <wx/aui/aui.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class widgetsFrame : public wxFrame
{
public:
    widgetsFrame(wxWindow* parent, wxWindowID id = -1);
    virtual ~widgetsFrame();

private:
    //(*Handlers(widgetsFrame)
    void on_exit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
    void on_open_file(wxCommandEvent& event);
    //*)

    //(*Identifiers(widgetsFrame)
    static const long ID_AUI_TOOL_BAR;
    static const long ID_MENU_FILE_OPEN_FILE;
    static const long ID_MENU_FILE_EXIT;
    static const long ID_MENU_HELP_ABOUT;
    static const long ID_STATUS_BAR;
    //*)

    //(*Declarations(widgetsFrame)
    wxAuiManager* aui_manager;
    wxAuiToolBar* aui_tool_bar;
    wxFileDialog* open_file_dialog_ptr_;
    wxStatusBar* status_bar_ptr_;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // WIDGETSMAIN_H
