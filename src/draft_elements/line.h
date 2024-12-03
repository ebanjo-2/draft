#ifndef LINE_H
#define LINE_H

#include <wx/wx.h>
#include "glm/glm.hpp"
#include "length_constraint.h"

namespace draft {

    class Line {

      protected:

        glm::vec2 _p0;
        glm::vec2 _p1;

      public:

        Line() = default;
        Line(const glm::vec2& p0, const glm::vec2& p1);

        const glm::vec2& getP0() const;
        const glm::vec2& getP1() const;

        virtual void draw(wxPaintDC& dc, const glm::mat3& view_matrix, float zoom_level) const;

    };

} // draft

#endif // LINE_H