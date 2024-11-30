#ifndef DRAFT_H
#define DRAFT_H

#include "vector"
#include "draft_elements/line.h"

namespace draft {

    class Draft {

      public:

        int _width = 1000;
        int _height = 1000;

        std::vector<Line> _lines;

      public:

        Draft() = default;
        Draft(int width, int height) : _width(width), _height(height) {};

    };

} // namespace draft

#endif // DRAFT_H