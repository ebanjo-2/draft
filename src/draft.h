#ifndef DRAFT_H
#define DRAFT_H

#include "vector"
#include "draft_elements/line.h"
#include "draft_elements/circle_arc.h"

namespace draft {

    class Draft {

      public:

        int _width = 300;
        int _height = 300;

        std::vector<Line> _lines;
        std::vector<CircleArc> _circle_arcs;

      public:

        Draft() = default;
        Draft(int width, int height) : _width(width), _height(height) {};

    };

} // namespace draft

#endif // DRAFT_H