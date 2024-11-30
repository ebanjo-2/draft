#ifndef LINE_H
#define LINE_H

#include <wx/wx.h>
#include "glm/glm.hpp"

namespace draft {

    class Line {

      protected:

        glm::vec2 _p1;
        glm::vec2 _p2;

      public:

        Line() = default;
        Line(const glm::vec2& p1, const glm::vec2& p2);

        virtual void draw(wxPaintDC& dc, const glm::mat3& view_matrix) const;

    };

} // draft

#endif // LINE_H