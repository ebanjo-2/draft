#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <wx/wx.h>
#include "glm/glm.hpp"

namespace draft {

    class ControlPanel : public wxWindow {
      
      public:

        ControlPanel(wxWindow* parent);

        void onSize(wxSizeEvent &event);
        void onPaint(wxPaintEvent &event);
        
        wxDECLARE_EVENT_TABLE();

    };

} // draft

#endif // CONTROL_PANEL_H