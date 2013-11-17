#pragma once

#include "../Geometry/Geometry.hpp"
#include "Drawable.hpp"
#include "Painter.hpp"

namespace painter
{

class PointDrawable: public Drawable
{
public:
  PointF _point;

  PointDrawable(PointF const & point)
    : _point(point) {}

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawPoint(_point);
  }
};

class LineDrawable: public Drawable
{
public:
  LineF _line;

  LineDrawable()
  {}

  LineDrawable(LineF const & line)
    : _line(line) {}

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawLine(_line);
  }
};

class RectDrawable: public Drawable
{
public:
  RectF _rect;

  RectDrawable()
  {}

  RectDrawable(RectF const & rect)
    : _rect(rect) {}

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawRect(_rect);
  }
};

class EllipseDrawable: public Drawable
{
public:
  EllipseF _ellipse;

  EllipseDrawable ()
  {}

  EllipseDrawable(EllipseF const & ellipse)
    : _ellipse(ellipse) {}

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawEllipse(_ellipse);
  }
};

class PolylineDrawable: public Drawable
{
public:
  PolylineF _polyline;

  PolylineDrawable()
  {}

  PolylineDrawable(PolylineF const & polyline)
  {
    _polyline = polyline;
  }

  void Draw(Painter * painter)
  {
    if (_polyline._points.size() < 2)
      return;

    painter->UsePaint(&_paint);
    for (size_t i = 1; i < _polyline._points.size(); ++i)
    {
      PointF & p0 = _polyline._points[i - 1];
      PointF & p1 = _polyline._points[i];
      LineF l(p0, p1);
      painter->DrawLine(l);
    }
  }
};

}
