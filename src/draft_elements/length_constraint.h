#ifndef LENGTH_CONSTRAINT_H
#define LENGTH_CONSTRAINT_H

#include <wx/wx.h>
#include "glm/glm.hpp"

namespace draft {

    class Line;

    class LengthConstraint {
      
      protected:

        float _length = 0.0f;
        float _distance_to_line = 10.0f;

      public:

        LengthConstraint() = default;
        LengthConstraint(float length) : _length(length) {};

        void onDraw(wxPaintDC& dc, const glm::mat3& view_mat, float zoom_level, const Line& line);

    };

} // draft

#endif // LENGTH_CONSTRAINT_H