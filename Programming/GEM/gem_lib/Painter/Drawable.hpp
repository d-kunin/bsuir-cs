#pragma once

#include "Painter.hpp"

namespace painter {

class Drawable {

public:
  virtual ~Drawable() {}
  virtual void Draw(Painter * painter) = 0;
};

}
