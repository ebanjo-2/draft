#ifndef CIRCLE_ARC_H
#define CIRCLE_ARC_H

#include <wx/wx.h>
#include "glm/glm.hpp"

namespace draft {

    class CircleArc {

      protected:

        glm::vec2 _p0;
        float _radius = 1.0f;
        float _angle_0 = 0.0f;
        float _angle_1 = 360.0f;

      public:

        CircleArc() = default;
        CircleArc(const glm::vec2& p0, float radius, float angle_0 = 0.0f, float angle_1 = 360.0f);

        virtual void draw(wxPaintDC& dc, const glm::mat3& view_matrix, float zoom_level) const;

    };

} // namespace draft

#endif // CIRCLE_ARC_H