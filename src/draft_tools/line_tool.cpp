#include "line_tool.h"

namespace draft {

    void LineTool::onPaint(wxPaintDC& dc, const glm::mat3& view_matrix, float _zoom_level) {

        glm::vec2 p0 = view_matrix * glm::vec3(_p0, 1.0f);        
        glm::vec2 p1 = view_matrix * glm::vec3(_p1, 1.0f);

        wxPoint p0_point = wxPoint(p0.x, p0.y);
        wxPoint p1_point = wxPoint(p1.x, p1.y);

        dc.SetTextForeground(*wxBLACK);
        dc.SetFont(wxFont(3 * _zoom_level, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        if(_p0_set) {
            dc.DrawCircle(p0_point, 1.5f * _zoom_level);
            dc.DrawText("P0", p0_point);
        }

        if(_p1_set) {
            dc.DrawCircle(p1_point, 1.5f * _zoom_level);
            dc.DrawText("P1", p1_point);
        }

    }

    void LineTool::onMotion(wxMouseEvent& event, const glm::mat3& inverse_view_matrix) {

    }

    bool LineTool::onMouseLeft(wxMouseEvent& event, const glm::mat3& inverse_view_matrix, Line& new_line) {
        // returns true, when a new line is created
    
        if (_p0_set) {
            // set p1
            
            _p1 = inverse_view_matrix * glm::vec3(event.GetPosition().x, event.GetPosition().y, 1.0f);

            new_line = Line(_p0, _p1);

            _p0_set = false;

            return true;
        } else {
            // set p0

            _p0_set = true;
            _p0 = inverse_view_matrix * glm::vec3(event.GetPosition().x, event.GetPosition().y, 1.0f);
        }

        return false;
    }

} // draft