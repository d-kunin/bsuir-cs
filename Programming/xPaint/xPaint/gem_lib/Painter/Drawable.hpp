#pragma once

#include "Painter.hpp"
#include "Paint.hpp"

namespace painter {

class Drawable {

public:
  virtual void Draw(Painter * painter) = 0;
  virtual bool Contains(PointF const & p) { return false; }
  virtual ~Drawable() {}

  void    SetPaint(Paint const & paint) { _paint = paint; }
  Paint & GetPaint()                       { return _paint; }

protected:
  Paint _paint;
};

}
