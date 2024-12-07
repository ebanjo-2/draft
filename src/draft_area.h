#ifndef DRAFT_AREA_H
#define DRAFT_AREA_H

#include <wx/wx.h>
#include "glm/glm.hpp"
#include "draft_painter.h"
#include "part.h"
#include "string"

namespace draft {

    class DraftArea : public wxWindow {

      protected:

        float _width = 400;
        float _height = 300;

        Part _part;
        DraftPainter _painter;

        // controlling the view
        float _zoom_level = 1.0f;
        glm::vec2 _view_position = glm::vec2(0.0f, 0.0f);
        bool _cursor_is_dragging = false;
        bool _space_reset_view = false; // if this is true, once the space key is released, resetView() will be called
        bool _space_held_down = false; // true, as long the space key is pressed
        wxPoint _cursor_position;

        // controlling which elements to show
        bool _show_vertices = true;

        // editing a part
        enum DraftAction {
            SELECT,
            ADD_VERTEX,
            SET_CONNECTOR_TARGET, // select the target next
            SET_CONNECTOR_REFERENCE, // select the reference next
            ADD_CONSTRAINT,
        };

        DraftAction _next_action = SELECT;
        std::string _selection = "";

      public:

        DraftArea(wxWindow* parent);

        void resetView();
        void loadDraft();

        void setShowVertices(bool show);
        bool getShowVertices() const;

      public:

        // event callbacks (get called by the main window)
        void onErase(wxEraseEvent& event);
        void onPaint(wxPaintEvent& event);
        void onMotion(wxMouseEvent& event);
        void onMouseWheel(wxMouseEvent& event);
        void onMouseLeft(wxMouseEvent& event);
        void onKeyDown(wxKeyEvent& event);
        void onKeyUp(wxKeyEvent& event);
        void onChar(wxKeyEvent& event);

        // drawing parts of the draft area
        void drawDraftGround(wxPaintDC& dc, const glm::mat3& view_matrix);

        wxDECLARE_EVENT_TABLE();

      private:

        glm::mat3 calcViewMatrix(const glm::vec2& view_position, float zoom_level);
        glm::mat3 calcInverseViewMatrix(const glm::vec2& view_position, float zoom_level);

    };

} // namespace draft

#endif // DRAFT_AREA_H