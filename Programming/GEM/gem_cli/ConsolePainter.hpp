#pragma once

#include "../gem_lib/Painter/Painter.hpp"

using namespace painter;

class ConsolePainter : public painter::Painter
{
public:

  void DrawPoint(PointF const & point) override;
  void DrawLine(LineF const & line) override;
  void DrawRect(RectF const & rect) override;
  void DrawEllipse(EllipseF const & ellipse) override;

  virtual float TargetWidth()  override  { return 0; }
  virtual float TargetHeight() override  { return 0; }
};
