#include "length_constraint.h"
#include "line.h"

namespace draft {

    void LengthConstraint::onDraw(wxPaintDC& dc, const glm::mat3& view_mat, float zoom_level, const Line& line) {

        glm::vec2 line0 = line.getP0();
        glm::vec2 line1 = line.getP1();

        glm::vec2 dir = glm::normalize(line1 - line0);
        glm::vec2 ortho = glm::normalize(glm::vec2(dir.y, -dir.x));
        float angle = glm::degrees(glm::atan(-dir.y, dir.x));

        if(ortho.y > 0.0f) {
            ortho *= -1.0f; // always point up
            angle += 180.0f;
        }

        glm::vec2 length0 = line0 + _distance_to_line * ortho;
        glm::vec2 length0_1 = line0 + (_distance_to_line + 2.0f) * ortho;
        glm::vec2 length1 = line1 + _distance_to_line * ortho;
        glm::vec2 length1_1 = line1 + (_distance_to_line + 2.0f) * ortho;

        glm::vec2 wx_line0 = view_mat * glm::vec3(line0, 1.0f);
        glm::vec2 wx_line1 = view_mat * glm::vec3(line1, 1.0f);
        glm::vec2 wx_length0 = view_mat * glm::vec3(length0, 1.0f);
        glm::vec2 wx_length0_1 = view_mat * glm::vec3(length0_1, 1.0f);
        glm::vec2 wx_length1 = view_mat * glm::vec3(length1, 1.0f);
        glm::vec2 wx_length1_1 = view_mat * glm::vec3(length1_1, 1.0f);

        // helper lines
        dc.SetPen(wxPen(*wxBLACK, 1, wxPENSTYLE_SOLID));
        dc.DrawLine(wx_line0.x, wx_line0.y, wx_length0_1.x, wx_length0_1.y);
        dc.DrawLine(wx_line1.x, wx_line1.y, wx_length1_1.x, wx_length1_1.y);

        // arrows
        glm::vec2 wx_arrow0_0 = view_mat * glm::vec3(length0 + 5.0f * dir - 0.65f * ortho, 1.0f);
        glm::vec2 wx_arrow0_1 = view_mat * glm::vec3(length0 + 5.0f * dir + 0.65f * ortho, 1.0f);
        glm::vec2 wx_arrow1_0 = view_mat * glm::vec3(length1 - 5.0f * dir - 0.65f * ortho, 1.0f);
        glm::vec2 wx_arrow1_1 = view_mat * glm::vec3(length1 - 5.0f * dir + 0.65f * ortho, 1.0f);
        wxPoint wx_arrow0[] = {wxPoint(wx_arrow0_0.x, wx_arrow0_0.y), wxPoint(wx_arrow0_1.x, wx_arrow0_1.y), wxPoint(wx_length0.x, wx_length0.y)};
        wxPoint wx_arrow1[] = {wxPoint(wx_arrow1_0.x, wx_arrow1_0.y), wxPoint(wx_arrow1_1.x, wx_arrow1_1.y), wxPoint(wx_length1.x, wx_length1.y)};
        dc.DrawLine(wx_length0.x, wx_length0.y, wx_length1.x, wx_length1.y);
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawPolygon(3, wx_arrow0, 0, 0);
        dc.DrawPolygon(3, wx_arrow1);

        // label
        glm::vec2 wx_text_pos = view_mat * glm::vec3(length0 + 0.4f * (length1 - length0) + 6.0f * ortho, 1.0f);

        dc.SetTextForeground(*wxBLACK);
        dc.SetFont(wxFont(3 * zoom_level, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        dc.DrawRotatedText(std::to_string(glm::length(line1 - line0)), wxPoint(wx_text_pos.x, wx_text_pos.y), angle);
    }


} // draft