#include "line.h"
#include "charconv"

namespace draft {

    Line::Line(const glm::vec2& p0, const glm::vec2& p1) : _p0(p0), _p1(p1) {

    }

    const glm::vec2& Line::getP0() const {

        return _p0;
    }

    const glm::vec2& Line::getP1() const {

        return _p1;
    }

    void Line::draw(wxPaintDC& dc, const glm::mat3& view_matrix, float zoom_level) const {

        glm::vec2 p0 = view_matrix * glm::vec3(_p0, 1.0f);
        glm::vec2 p1 = view_matrix * glm::vec3(_p1, 1.0f);
        
        dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
        dc.DrawLine(p0.x, p0.y, p1.x, p1.y);

        LengthConstraint length;
        length.onDraw(dc, view_matrix, zoom_level , *this);
        
    }

} // draft