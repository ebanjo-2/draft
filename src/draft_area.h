#ifndef DRAFT_AREA_H
#define DRAFT_AREA_H

#include <wx/wx.h>
#include "draft.h"
#include "glm/glm.hpp"

namespace draft {

    class DraftArea : public wxScrolledWindow {

      protected:

        // the current draft
        Draft _draft;

        // controlling the view
        float _zoom_level = 1.0f;
        glm::vec2 _view_position = glm::vec2(0.0f, 0.0f);
        bool _cursor_is_dragging = false;
        bool _space_reset_view = false; // if this is true, once the space key is released, resetView() will be called
        bool _space_held_down = false; // true, as long the space key is pressed
        wxPoint _cursor_position;

      public:

        DraftArea(wxWindow* parent);

        void resetView();
        void loadDraft();

      public:

        // event callbacks (get called by the main window)
        void onErase(wxEraseEvent& event);
        void onPaint(wxPaintEvent& event);
        void onMotion(wxMouseEvent& event);
        void onMouseWheel(wxMouseEvent& event);
        void onMouseLeft(wxMouseEvent& event);
        void onKeyDown(wxKeyEvent& event);
        void onKeyUp(wxKeyEvent& event);


        wxDECLARE_EVENT_TABLE();

      private:

        glm::mat3 calcViewMatrix(const glm::vec2& view_position, float zoom_level);
        glm::mat3 calcInverseViewMatrix(const glm::vec2& view_position, float zoom_level);

    };

} // namespace draft

#endif // DRAFT_AREA_H