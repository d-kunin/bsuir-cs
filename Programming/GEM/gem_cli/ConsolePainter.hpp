#pragma once

#include "../gem_lib/Painter/Painter.hpp"

using namespace painter;

class ConsolePainter : public painter::Painter
{
public:

  void drawPoint(PointF const & point) override;
  void drawLine(LineF const & line) override;
  void drawRect(RectF const & rect) override;
  void drawEllipse(EllipseF const & ellipse) override;

  virtual float TargetWidth()  override  { return 0; }
  virtual float TargetHeight() override  { return 0; }
};
