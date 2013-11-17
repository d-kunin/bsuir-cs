#pragma once

#include "../Geometry/Geometry.hpp"
#include "Drawable.hpp"
#include "Painter.hpp"

namespace painter {

class PointDrawable: public Drawable {
public:
  PointF _point;

  PointDrawable(PointF const & point)
    : _point(point) {}

  void Draw(Painter * painter) {
    painter->DrawPoint(_point);
  }
};

class LineDrawable: public Drawable {
public:
  LineF _line;

  LineDrawable(LineF const & line)
    : _line(line) {}

  void Draw(Painter * painter) {
    painter->DrawLine(_line);
  }
};

class RectDrawable: public Drawable {
public:
  RectF _rect;

  RectDrawable(RectF const & rect)
    : _rect(rect) {}

  void Draw(Painter * painter) {
    painter->DrawRect(_rect);
  }
};

class EllipseDrawable: public Drawable {
public:
  EllipseF _ellipse;

  EllipseDrawable(EllipseF const & ellipse)
    : _ellipse(ellipse) {}

  void Draw(Painter * painter) {
    painter->DrawEllipse(_ellipse);
  }
};

}
