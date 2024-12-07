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
    EVT_CHAR(DraftArea::onChar)
    END_EVENT_TABLE();

    DraftArea::DraftArea(wxWindow *parent)
        : wxWindow(parent, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxVSCROLL | wxHSCROLL) {
        
        //_draft._lines.push_back(Line(glm::vec2(100, 100), glm::vec2(200, 100)));
        //_draft._circle_arcs.push_back(CircleArc(glm::vec2(100, 200), 50.0f, 20.0f, 150.0f));
    }

    void DraftArea::resetView() {

        glm::vec2 screen_size = glm::vec2(GetSize().x, GetSize().y);
        glm::vec2 draft_size = glm::vec2(_width, _height);

        glm::vec2 needed_zoom = screen_size / draft_size;

        _zoom_level = glm::min(needed_zoom.x, needed_zoom.y);
        _view_position = -0.5f * (screen_size / _zoom_level - draft_size);

        Refresh();
    }

    void DraftArea::setShowVertices(bool show) {

        _show_vertices = show;
        Refresh();
    }

    bool DraftArea::getShowVertices() const {

        return _show_vertices;
    }

    void DraftArea::onErase(wxEraseEvent &event) {

    }

    void DraftArea::onPaint(wxPaintEvent &event) {

        wxPaintDC dc(this);

        glm::mat3 view_matrix = calcViewMatrix(_view_position, _zoom_level);
        drawDraftGround(dc, view_matrix);

        for(auto const& vertex : _part.getVertices()) {

            if(!_show_vertices) break;

            wxColor color = wxColor(0,100,0);
            if(_selection == vertex.first) color = wxColor(100, 0, 0);

            _painter.drawVertexMarker(dc, view_matrix * glm::vec3(vertex.second.x, vertex.second.y, 1.0f), _zoom_level, color);

        }

        for(auto const& connector : _part.getConnectors()) {

            std::string v0_identifier = connector.second.getVertex0();
            std::string v1_identifier = connector.second.getVertex1();

            glm::vec3 v0, v1;
            bool v0_exists = _part.getVertex(v0_identifier, v0);
            bool v1_exists = _part.getVertex(v1_identifier, v1);

            if(v0_exists && v1_exists) {

                wxColor color = *wxBLACK;
                if(_selection == connector.first) color = wxColor(100, 0, 0);

                _painter.drawPartLine(dc, view_matrix * glm::vec3(v0.x, v0.y, 1.0f), view_matrix * glm::vec3(v1.x, v1.y, 1.0f), _zoom_level, color);
            }
        }

        /*_painter.drawPartLine(dc, view_matrix * glm::vec3(100.0f, 100.0f, 1.0f), view_matrix * glm::vec3(200.0f, 100.0f, 1.0f), _zoom_level);
        _painter.drawHelperLine(dc, view_matrix * glm::vec3(100.0f, 100.0f, 1.0f), view_matrix * glm::vec3(100.0f, 88.0f, 1.0f), _zoom_level);
        _painter.drawHelperLine(dc, view_matrix * glm::vec3(200.0f, 100.0f, 1.0f), view_matrix * glm::vec3(200.0f, 88.0f, 1.0f), _zoom_level);
        _painter.drawDimensionLine(dc, view_matrix * glm::vec3(100.0f, 90.0f, 1.0f), view_matrix * glm::vec3(200.0f, 90.0f, 1.0f), _zoom_level);
        _painter.drawPartArc(dc, view_matrix * glm::vec3(150.0f, 200.0f, 1.0f), 14.0f, 60.0f, _zoom_level * 65.0f, _zoom_level);
        _painter.drawDimensionArc(dc, view_matrix * glm::vec3(150.0f, 200.0f, 1.0f), 60.0f, 14.0f, _zoom_level * 75.0f, _zoom_level);
        _painter.drawHelperLine(dc, view_matrix * glm::vec3(150.0f, 200.0f, 1.0f), view_matrix * glm::vec3(190.0f, 130.0f, 1.0f), _zoom_level);
        _painter.drawHelperLine(dc, view_matrix * glm::vec3(150.0f, 200.0f, 1.0f), view_matrix * glm::vec3(230.0f, 180.0f, 1.0f), _zoom_level);
        */

        // drawGrid(dc, view_matrix);

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
                // move a vertex

                glm::vec2 pos = inverse_view * glm::vec3(event.GetPosition().x, event.GetPosition().y, 1.0f);
                _part.moveVertex(_selection, glm::vec3(pos, 0.0f));  

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
            _zoom_level *= (1.0f + 0.0005f * float(event.GetWheelRotation())) / 1.0f;
        else
            _zoom_level *= 1.0f / (1.0f - 0.0005f * float(event.GetWheelRotation()));

        // _zoom_level = std::clamp(_zoom_level, 0.1f, 5.0f);

        // move the view to keep the same cursor position with the new zoom
        _view_position = glm::vec2(inverse_view * glm::vec3(cursor_pos, 1.0f)) - cursor_pos / _zoom_level;

        // redraw
        Refresh();
    }

    void DraftArea::onMouseLeft(wxMouseEvent &event) {

        glm::mat3 inverse_view = calcInverseViewMatrix(_view_position, _zoom_level);
        glm::vec2 position = inverse_view * glm::vec3(event.GetPosition().x,  event.GetPosition().y, 1.0f);

        if(_next_action == ADD_VERTEX) {
            _part.addVertex(glm::vec3(position, 0.0f));
            _selection = "";
            _next_action = SELECT;
        } else if (_next_action == SET_CONNECTOR_TARGET) {
            _selection = _part.getVertex(glm::vec3(position, 0.0f), 1.0f);
            _next_action = SET_CONNECTOR_REFERENCE;
        } else if (_next_action == SET_CONNECTOR_REFERENCE) {
            _part.addConnector(Connector(_selection, _part.getVertex(glm::vec3(position, 0.0f), 1.0f), Connector::ConnectorType::LINE));
            _selection = "";
            _next_action = SELECT;
        } else if(_next_action == SELECT) {
            _selection = _part.getVertex(glm::vec3(position, 0.0f), 1.0f);
            if(_selection == "")
                _selection = _part.getConnector(glm::vec3(position, 0.0f), 0.5f);
        }

        Refresh();
    }

    void DraftArea::onKeyDown(wxKeyEvent& event) {

        if(!_space_held_down && event.GetKeyCode() == WXK_SPACE) {
            
            _space_reset_view = true;
            _space_held_down = true;
        } else if(event.GetKeyCode() == WXK_DELETE) {
            
            if(!_part.eraseVertex(_selection))
                _part.eraseConnector(_selection);

            Refresh();
        } else {

            event.Skip();
        }

    }

    void DraftArea::onKeyUp(wxKeyEvent& event) {

        if(event.GetKeyCode() == WXK_SPACE) {

            _space_held_down = false;

            if(_space_reset_view) {

                resetView();
            }

        } else {
            event.Skip();
        }

    }

    void DraftArea::onChar(wxKeyEvent& event) {

        if(event.GetKeyCode() == 'v') {
            _next_action = ADD_VERTEX;
        } else if(event.GetKeyCode() == 'c') {
            glm::vec3 dummy;
            if(_part.getVertex(_selection, dummy)) {
                _next_action = SET_CONNECTOR_REFERENCE;
            } else {
                _next_action = SET_CONNECTOR_TARGET;
            }
        } else if(event.GetKeyCode() == 'x') {
            _next_action = ADD_CONSTRAINT;
        } else if(event.GetKeyCode() == 'd') {
            if(!_part.eraseVertex(_selection))
                _part.eraseConnector(_selection);
            Refresh();
            _next_action = SELECT;
        } else {
            event.Skip();
        }

    }

    void DraftArea::drawDraftGround(wxPaintDC& dc, const glm::mat3& view_matrix) {

        // drawing the draft area
        glm::vec3 p0 = view_matrix * glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 p1 = view_matrix * glm::vec3(_width, _height, 1.0f);

        wxRect draft_area(wxPoint(p0.x,p0.y), wxPoint(p1.x, p1.y));

        // drawing the background
        dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
        dc.SetBrush(wxBrush(wxColor(0xb5decf)));
        dc.DrawRectangle(draft_area);

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