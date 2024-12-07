#ifndef DRAFT_PAINTER_H
#define DRAFT_PAINTER_H

#include <wx/wx.h>
#include "glm/glm.hpp"
#include "string"

namespace draft {

    class DraftPainter {
      
      protected:

      public:
        // functions to draw elements of a draft

        void drawVertexMarker(wxPaintDC& dc, const glm::vec2& p0, float zoom_level, wxColor color = *wxBLACK);

        void drawPartLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level, wxColor color = *wxBLACK); // "Körperkante"
        void drawHelperLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level); // "Maßhilfslinie"
        void drawDimensionLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level); // "Maßlinie"

        void drawPartArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float zoom_level); // "Kreisbogen (Körperkante)"
        void drawDimensionArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float zoom_level); // "Kreisbogen (Maßlinie)"

      protected:
        // functions to draw primitive elements used in a draft

        void drawLine(wxPaintDC& dc, float width, const glm::vec2& p0, const glm::vec2& p1, const wxColor& color = *wxBLACK, const wxPenStyle& style = wxPENSTYLE_SOLID);
        void drawArrowHead(wxPaintDC& dc, const glm::vec2& tip, const glm::vec2& dir, float tip_angle, float length);
        void drawText(wxPaintDC& dc, const std::string& str, const glm::vec2& top_left, const glm::vec2& dir, float font_size);
        void drawArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float width);

    };

} // draft

#endif // DRAFT_PAINTER_H