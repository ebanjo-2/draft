#ifndef LINE_TOOL_H
#define LINE_TOOL_H

#include <wx/wx.h>
#include "glm/glm.hpp"
#include "draft_elements/line.h"

namespace draft {

    class LineTool {

      protected:

        bool _p0_set = false;
        bool _p1_set = false;

        glm::vec2 _p0;
        glm::vec2 _p1;

      public:

        void onPaint(wxPaintDC& dc, const glm::mat3& view_matrix, float _zoom_level);
        void onMotion(wxMouseEvent& event, const glm::mat3& inverse_view_matrix);
        bool onMouseLeft(wxMouseEvent& event, const glm::mat3& inverse_view_matrix, Line& new_line);

    };

} // draft

#endif // LINE_TOOL_H