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
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
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
const long widgetsFrame::ID_AUI_TOOL_BAR = wxNewId();
const long widgetsFrame::ID_AUI_NOTEBOOK_MANAGEMENT = wxNewId();
const long widgetsFrame::ID_MAIN_PANEL = wxNewId();
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
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("/"));
    file_path = dir_path.append("/assets/icon/2019_05_nq.png");
    wxString wx_file_path(file_path);

    //(*Initialize(widgetsFrame)
    wxMenu* menu_file_ptr;
    wxMenu* menu_help_ptr;
    wxMenuBar* menu_bar_ptr;
    wxMenuItem* menu_file_exit_ptr;
    wxMenuItem* menu_file_open_file_ptr;
    wxMenuItem* menu_help_about_ptr;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(960,720));
    SetMinSize(wxSize(480,240));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wx_file_path);
    	SetIcon(FrameIcon);
    }
    aui_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    aui_tool_bar = new wxAuiToolBar(this, ID_AUI_TOOL_BAR, wxDefaultPosition, wxSize(400,36), wxAUI_TB_DEFAULT_STYLE);
    aui_tool_bar->Realize();
    aui_manager->AddPane(aui_tool_bar, wxAuiPaneInfo().Name(_T("tool_bar")).ToolbarPane().Caption(_("Tool Bar")).Layer(10).Top().BestSize(wxSize(400,36)).Gripper());
    aui_notebook_management = new wxAuiNotebook(this, ID_AUI_NOTEBOOK_MANAGEMENT, wxDefaultPosition, wxSize(250,-1), wxAUI_NB_DEFAULT_STYLE);
    aui_notebook_management->SetMinSize(wxSize(120,60));
    aui_manager->AddPane(aui_notebook_management, wxAuiPaneInfo().Name(_T("notebook_management")).DefaultPane().Caption(_("Management")).CaptionVisible().Left().BestSize(wxSize(250,-1)).MinSize(wxSize(120,60)));
    main_panel = new wxPanel(this, ID_MAIN_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_PANEL"));
    aui_manager->AddPane(main_panel, wxAuiPaneInfo().Name(_T("main_panel")).DefaultPane().Caption(_("Main Panel")).CaptionVisible(false).Center());
    aui_manager->Update();
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
    aui_manager->UnInit();
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
