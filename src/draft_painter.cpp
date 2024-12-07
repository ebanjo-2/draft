#include "draft_painter.h"

namespace draft {

    //////////////////////////// functions to draw elements of a draft ////////////////////////////

    void DraftPainter::drawVertexMarker(wxPaintDC& dc, const glm::vec2& p0, float zoom_level, wxColor color) {

        int pen_width = std::max(int(0.5f * zoom_level + 0.5f), 1);
        int radius = std::max(int(0.75f * zoom_level + 0.5), 1);

        dc.SetPen(wxPen(color, pen_width, wxPENSTYLE_SOLID));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawCircle(wxPoint(p0.x, p0.y), radius);
    }

    void DraftPainter::drawPartLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level, wxColor color) {
        // "Körperkante"

        drawLine(dc, 0.7f * zoom_level, p0, p1, color); // "breite Volllinie"
    }

    void DraftPainter::drawHelperLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level) {
        // "Maßhilfslinie"

        drawLine(dc, 0.2f * zoom_level, p0, p1); // "schmale Volllinie"
    } 
    void DraftPainter::drawDimensionLine(wxPaintDC& dc, const glm::vec2& p0, const glm::vec2& p1, float zoom_level) {
        // "Maßlinie"

        drawLine(dc, 0.2f * zoom_level, p0, p1); // "schmale Volllinie"
        drawArrowHead(dc, p0, glm::normalize(p0 - p1), 15.0f, 3.0f * zoom_level);
        drawArrowHead(dc, p1, glm::normalize(p1 - p0), 15.0f, 3.0f * zoom_level);

    }

    void DraftPainter::drawPartArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float zoom_level) {
        // "Kreisbogen (Körperkante)"

        drawArc(dc, centre, angle0, angle1, radius, 0.7f * zoom_level);
    }

    void DraftPainter::drawDimensionArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float zoom_level) {
        // "Kreisbogen (Maßlinie)"
        
        drawArc(dc, centre, angle0, angle1, radius, 0.2f * zoom_level);

        glm::vec2 p0 = centre + radius * glm::vec2(glm::cos(glm::radians(angle0)), -glm::sin(glm::radians(angle0)));
        glm::vec2 p1 = centre + radius * glm::vec2(glm::cos(glm::radians(angle1)), -glm::sin(glm::radians(angle1)));

        drawArrowHead(dc, p0, glm::vec2(glm::cos(glm::radians(angle0 - 90.0f)), -glm::sin(glm::radians(angle0 - 90.0f))), 15.0f, 3.0f * zoom_level);
        drawArrowHead(dc, p1, glm::vec2(glm::cos(glm::radians(angle1 + 90.0f)), -glm::sin(glm::radians(angle1 + 90.0f))), 15.0f, 3.0f * zoom_level);

    }


    ///////////////////// functions to draw primitive elements used in a draft ////////////////////

    void DraftPainter::drawLine(wxPaintDC& dc, float width, const glm::vec2& p0, const glm::vec2& p1, const wxColor& color, const wxPenStyle& style) {

        int pen_width = std::max(int(width + 0.5f), 1);

        dc.SetPen(wxPen(color, pen_width, style));
        dc.DrawLine(p0.x, p0.y, p1.x, p1.y);

    }

    void DraftPainter::drawArrowHead(wxPaintDC& dc, const glm::vec2& tip, const glm::vec2& dir, float tip_angle, float length) {
        
        // calculating the 3 points that form the arrow head
        // assuming dir is normalized
        glm::vec2 ortho(dir.y, -dir.x);
        glm::vec2 p0 = tip - dir * length + ortho * length * glm::sin(glm::radians(tip_angle / 2.0f));
        glm::vec2 p1 = tip - dir * length - ortho * length * glm::sin(glm::radians(tip_angle / 2.0f));

        wxPoint arrow[] = {wxPoint(p0.x, p0.y), wxPoint(p1.x, p1.y), wxPoint(tip.x, tip.y)};
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawPolygon(3, arrow);
        
    }

    void DraftPainter::drawText(wxPaintDC& dc, const std::string& str, const glm::vec2& top_left, const glm::vec2& dir, float font_size) {

        dc.SetTextForeground(*wxBLACK);
        dc.SetFont(wxFont(font_size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        dc.DrawRotatedText(str, wxPoint(top_left.x, top_left.y), glm::degrees(glm::atan(dir.y, dir.x)));
    }

    void DraftPainter::drawArc(wxPaintDC& dc, const glm::vec2& centre, float angle0, float angle1, float radius, float width) {

        int pen_width = std::max(int(width + 0.5f), 1);

        dc.SetPen(wxPen(*wxBLACK, pen_width, wxPENSTYLE_SOLID));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);

        glm::vec2 p0 = centre + radius * glm::vec2(glm::cos(glm::radians(angle0)), -glm::sin(glm::radians(angle0)));
        glm::vec2 p1 = centre + radius * glm::vec2(glm::cos(glm::radians(angle1)), -glm::sin(glm::radians(angle1)));

        dc.DrawArc(wxPoint(p0.x, p0.y), wxPoint(p1.x, p1.y), wxPoint(centre.x, centre.y));

    }

} // draft