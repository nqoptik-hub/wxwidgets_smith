/***************************************************************
 * Name:      widgetsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Nguyen Quang (nqoptik@gmail.com)
 * Created:   2019-11-17
 * Copyright: Nguyen Quang (https://nqoptik.gitlab.io)
 * License:
 **************************************************************/

#include "widgetsMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(widgetsFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f,
    long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f)
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

//(*IdInit(widgetsFrame)
const long widgetsFrame::ID_MENU_FILE_OPEN_FILE = wxNewId();
const long widgetsFrame::ID_MENU_FILE_EXIT = wxNewId();
const long widgetsFrame::ID_MENU_HELP_ABOUT = wxNewId();
const long widgetsFrame::ID_STATUS_BAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(widgetsFrame, wxFrame)
//(*EventTable(widgetsFrame)
//*)
END_EVENT_TABLE()

widgetsFrame::widgetsFrame(wxWindow* parent, wxWindowID id)
{
    // Create icon
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    {
        std::string file_path = __FILE__;
        std::string dir_path = file_path.substr(0, file_path.rfind("/"));
        file_path = dir_path.append("/assets/icon/2019_05_nq.png");
        wxIcon FrameIcon;
        FrameIcon.CopyFromBitmap(wxBitmap(wxImage((wxString)(file_path))));
        SetIcon(FrameIcon);
    }

    //(*Initialize(widgetsFrame)
    wxMenu* menu_file_ptr;
    wxMenu* menu_help_ptr;
    wxMenuBar* menu_bar_ptr;
    wxMenuItem* menu_file_exit_ptr;
    wxMenuItem* menu_file_open_file_ptr;
    wxMenuItem* menu_help_about_ptr;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    menu_bar_ptr = new wxMenuBar();
    menu_file_ptr = new wxMenu();
    menu_file_open_file_ptr = new wxMenuItem(menu_file_ptr, ID_MENU_FILE_OPEN_FILE, _("Open File...\tCtrl-O"), _("Open a file"), wxITEM_NORMAL);
    menu_file_ptr->Append(menu_file_open_file_ptr);
    menu_file_ptr->AppendSeparator();
    menu_file_exit_ptr = new wxMenuItem(menu_file_ptr, ID_MENU_FILE_EXIT, _("Exit\tAlt-F4"), _("Exit the application"), wxITEM_NORMAL);
    menu_file_ptr->Append(menu_file_exit_ptr);
    menu_bar_ptr->Append(menu_file_ptr, _("&File"));
    menu_help_ptr = new wxMenu();
    menu_help_about_ptr = new wxMenuItem(menu_help_ptr, ID_MENU_HELP_ABOUT, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    menu_help_ptr->Append(menu_help_about_ptr);
    menu_bar_ptr->Append(menu_help_ptr, _("&Help"));
    SetMenuBar(menu_bar_ptr);
    status_bar_ptr_ = new wxStatusBar(this, ID_STATUS_BAR, 0, _T("ID_STATUS_BAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    status_bar_ptr_->SetFieldsCount(1,__wxStatusBarWidths_1);
    status_bar_ptr_->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(status_bar_ptr_);
    open_file_dialog_ptr_ = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    Center();

    Connect(ID_MENU_FILE_OPEN_FILE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&widgetsFrame::on_open_file);
    Connect(ID_MENU_FILE_EXIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&widgetsFrame::on_exit);
    Connect(ID_MENU_HELP_ABOUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&widgetsFrame::on_about);
    //*)
}

widgetsFrame::~widgetsFrame()
{
    //(*Destroy(widgetsFrame)
    //*)
}

void widgetsFrame::on_exit(wxCommandEvent& event)
{
    Close();
}

void widgetsFrame::on_about(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void widgetsFrame::on_open_file(wxCommandEvent& event)
{
    int result = open_file_dialog_ptr_->ShowModal();
    if (result == wxID_OK)
    {
        wxMessageBox(open_file_dialog_ptr_->GetPath());
    }
}
