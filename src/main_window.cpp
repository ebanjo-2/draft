#include "main_window.h"

namespace draft {

    enum MenuEventIDs {
        ID_Hello = 1
    };

    BEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_ABOUT, MainWindow::onAbout)
    EVT_MENU(wxID_EXIT, MainWindow::onExit)
    EVT_MENU(ID_Hello, MainWindow::onHello)
    END_EVENT_TABLE();

    MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Draft") {

        _draft_area = new DraftArea(this);

        wxMenu *menu_file = createFileMenu();
        wxMenu *menu_help = createHelpMenu();

        createMenuBar(menu_file, menu_help);

        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");

    }

    wxMenu *MainWindow::createFileMenu() {

        wxMenu *menuFile = new wxMenu;
        menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        return menuFile;
    }

    wxMenu *MainWindow::createHelpMenu() {

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        return menuHelp;
    }

    void MainWindow::createMenuBar(wxMenu *menu_file, wxMenu *menu_help) {

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menu_file, "&File");
        menuBar->Append(menu_help, "&Help");

        SetMenuBar(menuBar);
    }

    void MainWindow::onExit(wxCommandEvent &event) {

        Close(true);

        std::cout << "Trying to close the window!\n";
    }

    void MainWindow::onAbout(wxCommandEvent &event) {

        wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
    }

    void MainWindow::onHello(wxCommandEvent &event) {

        wxLogMessage("Hello world from wxWidgets!");
    }

} // namespace draft