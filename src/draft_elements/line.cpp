#include "line.h"

namespace draft {

    Line::Line(const glm::vec2& p1, const glm::vec2& p2) : _p1(p1), _p2(p2) {

    }

    void Line::draw(wxPaintDC& dc, const glm::mat3& view_matrix) const {

        glm::vec2 p1 = view_matrix * glm::vec3(_p1, 1.0f);
        glm::vec2 p2 = view_matrix * glm::vec3(_p2, 1.0f);

        dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }

} // draft