#pragma once

#include "../Geometry/Geometry.hpp"
#include "Paint.hpp"

using geometry::Point2D;
using geometry::Line2D;
using geometry::Rect;
using geometry::Ellipse;
using geometry::Polyline;

namespace painter {

typedef Point2D<float> PointF;
typedef Line2D<float> LineF;
typedef Rect<float> RectF;
typedef Ellipse<float> EllipseF;
typedef Polyline<float> PolylineF;

class Painter {

public:
  virtual ~Painter() {}

  virtual void DrawPoint(PointF const & point) = 0;
  virtual void DrawLine(LineF const & line) = 0;
  virtual void DrawRect(RectF const & rect) = 0;
  virtual void DrawEllipse(EllipseF const & ellipse) = 0;

  virtual void UsePaint(Paint * paint) = 0;

  //{@ We need to know target bounds
  virtual float TargetWidth() = 0;
  virtual float TargetHeight() = 0;
  //@}
};

}
