// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>
#include "main_window.h"

namespace draft {

    class App : public wxApp {

      public:
        bool OnInit() override {

            MainWindow *main_window = new MainWindow();
            main_window->Show(true);
            return true;
        }
    };

} // namespace draft

// program entry point (main)
DECLARE_APP(draft::App)
IMPLEMENT_APP(draft::App)