#include "control_panel.h"

namespace draft {

    BEGIN_EVENT_TABLE(ControlPanel, wxWindow)
    EVT_PAINT(ControlPanel::onPaint)
    EVT_SIZE(ControlPanel::onSize)
    END_EVENT_TABLE();

    ControlPanel::ControlPanel(wxWindow* parent)
        : wxWindow(parent, wxID_ANY) {

    }

    void ControlPanel::onSize(wxSizeEvent &event) {

        SetPosition(wxPoint(GetParent()->GetSize().x - 200, 50));
        SetSize(wxSize(150, 300));
        SetWindowStyle(wxSIMPLE_BORDER);
        Refresh();

        std::cout << "onSize\n";
        event.Skip();
    }

    void ControlPanel::onPaint(wxPaintEvent &event) {

        wxPaintDC dc(this);
        event.Skip();
    }

} // draft