#include "circle_arc.h"

namespace draft {

    CircleArc::CircleArc(const glm::vec2& p0, float radius, float angle_0, float angle_1) 
            : _p0(p0), _radius(radius), _angle_0(angle_0), _angle_1(angle_1) {

    }

    void CircleArc::draw(wxPaintDC& dc, const glm::mat3& view_matrix, float zoom_level) const {

        glm::vec2 wx_center = view_matrix * glm::vec3(_p0, 1.0f);
        glm::vec2 wx_p0 = view_matrix * glm::vec3(_p0 + _radius * glm::vec2(glm::cos(glm::radians(_angle_0)), -glm::sin(glm::radians(_angle_0))), 1.0f);
        glm::vec2 wx_p1 = view_matrix * glm::vec3(_p0 + _radius * glm::vec2(glm::cos(glm::radians(_angle_1)), -glm::sin(glm::radians(_angle_1))), 1.0f);


        dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawArc(wxPoint(wx_p0.x, wx_p0.y), wxPoint(wx_p1.x, wx_p1.y), wxPoint(wx_center.x, wx_center.y));
        // dc.DrawCircle(wxPoint(wx_center.x, wx_center.y), _radius * zoom_level);
    }

} // draft