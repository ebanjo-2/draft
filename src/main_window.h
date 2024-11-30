#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include "draft_area.h"

namespace draft {

    class MainWindow : public wxFrame {

      protected:

        DraftArea* _draft_area;

      public:

        MainWindow();
        
      private:

        wxMenu* createFileMenu();
        wxMenu* createHelpMenu();
        void createMenuBar(wxMenu* menu_file, wxMenu* menu_help);

        // menu callbacks
        void onHello(wxCommandEvent &event);
        void onExit(wxCommandEvent &event);
        void onAbout(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
    };

} // namespace draft

#endif // MAIN_WINDOW_H