#pragma once

#include "Painter.hpp"
#include "Paint.hpp"

namespace painter {

class Drawable {

public:
  virtual ~Drawable() {}
  virtual void Draw(Painter * painter) = 0;

  void    SetPaint(Paint const & paint) { _paint = paint; }
  Paint & GetPaint()                       { return _paint; }

protected:
  Paint _paint;
};

}
