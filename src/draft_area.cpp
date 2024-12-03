#include "draft_area.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "string"

namespace draft {

    BEGIN_EVENT_TABLE(DraftArea, wxScrolledWindow)
    EVT_ERASE_BACKGROUND(DraftArea::onErase)
    EVT_PAINT(DraftArea::onPaint)
    EVT_MOTION(DraftArea::onMotion)
    EVT_MOUSEWHEEL(DraftArea::onMouseWheel)
    EVT_LEFT_DOWN(DraftArea::onMouseLeft)
    EVT_KEY_DOWN(DraftArea::onKeyDown)
    EVT_KEY_UP(DraftArea::onKeyUp)
    END_EVENT_TABLE();

    DraftArea::DraftArea(wxWindow *parent)
        : wxScrolledWindow(parent, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxVSCROLL | wxHSCROLL) {
        
        _draft._lines.push_back(Line(glm::vec2(100, 100), glm::vec2(200, 100)));
        _draft._circle_arcs.push_back(CircleArc(glm::vec2(100, 200), 50.0f, 20.0f, 150.0f));
    }

    void DraftArea::resetView() {

        glm::vec2 screen_size = glm::vec2(GetSize().x, GetSize().y);
        glm::vec2 draft_size = glm::vec2(_draft._width, _draft._height);

        glm::vec2 needed_zoom = screen_size / draft_size;

        _zoom_level = glm::min(needed_zoom.x, needed_zoom.y);
        _view_position = -0.5f * (screen_size / _zoom_level - draft_size);

        Refresh();
    }

    void DraftArea::onErase(wxEraseEvent &event) {

    }

    void DraftArea::onPaint(wxPaintEvent &event) {

        wxPaintDC dc(this);

        glm::mat3 view_matrix = calcViewMatrix(_view_position, _zoom_level);

        drawDraftGround(dc, view_matrix);
        // drawGrid(dc, view_matrix);

        _line_tool.onPaint(dc, view_matrix, _zoom_level);

        // drawing the draft
        dc.SetPen(wxPen(*wxBLACK, 1, wxPENSTYLE_SOLID));

        for(const Line& l: _draft._lines) {
            
            l.draw(dc, view_matrix, _zoom_level);
        }

        for(const CircleArc& c: _draft._circle_arcs) {
            
            c.draw(dc, view_matrix, _zoom_level);
        }

    }

    void DraftArea::onMotion(wxMouseEvent &event) {

        _space_reset_view = false;

        if (_cursor_is_dragging && event.Dragging()) {
            
            glm::mat3 inverse_view = calcInverseViewMatrix(_view_position, _zoom_level);

            if (wxGetKeyState(WXK_SPACE)) {
                // move the view

                glm::vec3 pos0 = inverse_view * glm::vec3(_cursor_position.x, _cursor_position.y, 1.0f);
                glm::vec3 pos1 = inverse_view * glm::vec3(event.GetPosition().x, event.GetPosition().y, 1.0f);

                glm::vec3 delta = pos1 - pos0;

                _view_position -= glm::vec2(delta.x, delta.y);

            } else {

                _line_tool.onMotion(event, inverse_view);
            }
        }

        Refresh();

        _cursor_is_dragging = event.Dragging();
        _cursor_position = event.GetPosition();
    }

    void DraftArea::onMouseWheel(wxMouseEvent &event) {

        // calculate the position of the cursor using the old zoom
        glm::vec2 cursor_pos(event.GetPosition().x, event.GetPosition().y);
        glm::mat3 inverse_view = calcInverseViewMatrix(_view_position, _zoom_level);

        // update the zoom
        if (event.GetWheelRotation() > 0)
            _zoom_level *= (1.0f + 0.0001f * float(event.GetWheelRotation())) / 1.0f;
        else
            _zoom_level *= 1.0f / (1.0f - 0.0001f * float(event.GetWheelRotation()));

        // _zoom_level = std::clamp(_zoom_level, 0.1f, 5.0f);

        // move the view to keep the same cursor position with the new zoom
        _view_position = glm::vec2(inverse_view * glm::vec3(cursor_pos, 1.0f)) - cursor_pos / _zoom_level;

        // redraw
        Refresh();
    }

    void DraftArea::onMouseLeft(wxMouseEvent &event) {

        glm::mat3 inverse_view = calcInverseViewMatrix(_view_position, _zoom_level);

        Line new_line;

        if(_line_tool.onMouseLeft(event, inverse_view, new_line)) 
            _draft._lines.push_back(new_line);

        Refresh();
    }

    void DraftArea::onKeyDown(wxKeyEvent& event) {

        if(!_space_held_down && event.GetKeyCode() == WXK_SPACE) {
            
            _space_reset_view = true;
            _space_held_down = true;
        }

    }

    void DraftArea::onKeyUp(wxKeyEvent& event) {

        if(event.GetKeyCode() == WXK_SPACE) {

            _space_held_down = false;

            if(_space_reset_view) {

                resetView();
            }

        }

    }

    void DraftArea::drawDraftGround(wxPaintDC& dc, const glm::mat3& view_matrix) {

        // drawing the draft area
        glm::vec3 p0 = view_matrix * glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 p1 = view_matrix * glm::vec3(_draft._width, _draft._height, 1.0f);

        wxRect draft_area(wxPoint(p0.x,p0.y), wxPoint(p1.x, p1.y));

        // drawing the background
        dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
        dc.SetBrush(wxBrush(wxColor(0xb5decf)));
        dc.DrawRectangle(draft_area);

    }

    void DraftArea::drawGrid(wxPaintDC& dc, const glm::mat3& view_matrix) {

        // calculating the visible area
        glm::mat3 inverse_view = calcInverseViewMatrix(_view_position, _zoom_level);
        glm::vec3 screen_p0 = inverse_view * glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 screen_p1 = inverse_view * glm::vec3(GetSize().x, GetSize().y, 1.0f);

        glm::vec3 draft_p0 = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 draft_p1 = glm::vec3(_draft._width, _draft._height, 0.0f);

        glm::vec3 grid_p0 = glm::max(screen_p0, draft_p0);
        glm::vec3 grid_p1 = glm::min(screen_p1, draft_p1);

        // cm lines
        if(_zoom_level > 1.0f) {
            dc.SetPen(wxPen(*wxColor(0, 0, 0, 100), 3, wxPENSTYLE_SOLID));

            for(int i = int(grid_p0.x / 10) * 10; i < grid_p1.x; i+=10) {
                glm::vec3 p0 = view_matrix * glm::vec3(i, grid_p0.y, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(i, grid_p1.y, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }

            for(int i = int(grid_p0.y / 10) * 10; i < grid_p1.y; i+=10) {
                glm::vec3 p0 = view_matrix * glm::vec3(grid_p0.x, i, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(grid_p1.x, i, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }
        }

        // 5 mm lines
        if(_zoom_level > 2.0f) {
            dc.SetPen(wxPen(wxColor(0, 0, 0, 100), 2, wxPENSTYLE_SOLID));

            for(int i = int(grid_p0.x / 10) * 10 + 5; i < grid_p1.x; i+=10) {
                glm::vec3 p0 = view_matrix * glm::vec3(i, grid_p0.y, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(i, grid_p1.y, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }

            for(int i = int(grid_p0.y / 10) * 10 + 5; i < grid_p1.y; i+=10) {
                glm::vec3 p0 = view_matrix * glm::vec3(grid_p0.x, i, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(grid_p1.x, i, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }
        }

        // mm lines
        if(_zoom_level > 10.0f) {
            dc.SetPen(wxPen(wxColor(0, 0, 0, 100), 1, wxPENSTYLE_SOLID));

            for(int i = grid_p0.x; i < grid_p1.x; i++) {
                glm::vec3 p0 = view_matrix * glm::vec3(i, grid_p0.y, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(i, grid_p1.y, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }

            for(int i = grid_p0.y; i < grid_p1.y; i++) {
                glm::vec3 p0 = view_matrix * glm::vec3(grid_p0.x, i, 1.0f);
                glm::vec3 p1 = view_matrix * glm::vec3(grid_p1.x, i, 1.0f);

                dc.DrawLine(p0.x, p0.y, p1.x, p1.y);
            }
        }
        
        // glm::vec3 p0 = view_matrix * glm::vec3(0.0f, 0.0f, 1.0f);
        //glm::vec3 p1 = view_matrix * glm::vec3(_draft._width, _draft._height, 1.0f);



    }

    glm::mat3 DraftArea::calcViewMatrix(const glm::vec2& view_position, float zoom_level) {

        glm::mat3 translation = glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-view_position, 1.0f));
        glm::mat3 scale = glm::mat3(glm::vec3(zoom_level, 0.0f, 0.0f), glm::vec3(0.0f, zoom_level, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        
        return scale * translation;
    }


    glm::mat3 DraftArea::calcInverseViewMatrix(const glm::vec2& view_position, float zoom_level) {

        glm::mat3 translation = glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(view_position, 1.0f));
        glm::mat3 scale = glm::mat3(glm::vec3(1.0f / zoom_level, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f / zoom_level, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        return translation * scale;
    }

} // namespace draft