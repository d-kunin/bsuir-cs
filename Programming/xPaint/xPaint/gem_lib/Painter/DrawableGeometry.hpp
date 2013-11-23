#pragma once

#include "../Geometry/Geometry.hpp"
#include "../Geometry/Algorithm.hpp"
#include "Drawable.hpp"
#include "Painter.hpp"

#include "../../io/Serializable.hpp"

class Serializer;

namespace painter
{

template<typename T>
class GeometryDrawable: public Drawable
{
public:
  T _geometry;

  void Transform(TransformF const & transform) override
  {
    _geometry = transform*_geometry;
  }

  RectF BoundingRect() const override
  {
    return algo::BoundingRect(_geometry);
  }
};

class PointDrawable: public GeometryDrawable<PointF>
{
public:

  PointDrawable()
  {}

  PointDrawable(PointF const & point)
  {
    _geometry = point;
  }

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawPoint(_geometry);
  }
};

class LineDrawable: public GeometryDrawable<LineF>,
                    public Serializable
{
public:

  LineDrawable()
  {}

  LineDrawable(LineF const & line)
  {
    _geometry = line;
  }

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawLine(_geometry);
  }

  bool Contains(PointF const & p ) override
  {
    return algo::Intersects(p._x, p._y, _geometry);
  }

  void WriteTo(Serializer * ) const override;
};

class RectDrawable: public GeometryDrawable<RectF>,
                    public Serializable
{
public:

  RectDrawable()
  {}

  RectDrawable(RectF const & rect)
  {
    _geometry = rect;
  }

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawRect(_geometry);
  }

  bool Contains(PointF const & p ) override
  {
    return algo::Intersects(p._x, p._y, _geometry);
  }

  void WriteTo(Serializer * ) const override;
};

class EllipseDrawable: public GeometryDrawable<EllipseF>,
                       public Serializable
{
public:

  EllipseDrawable ()
  {}

  EllipseDrawable(EllipseF const & ellipse)
  {
    _geometry = ellipse;
  }

  void Draw(Painter * painter)
  {
    painter->UsePaint(&_paint);
    painter->DrawEllipse(_geometry);
  }

  bool Contains(PointF const & p ) override
  {
    return algo::Intersects(p._x, p._y, _geometry);
  }

  void WriteTo(Serializer * ) const override;
};

class PolylineDrawable: public GeometryDrawable<PolylineF>,
                        public Serializable
{
public:

  PolylineDrawable()
  {}

  PolylineDrawable(PolylineF const & polyline)
  {
    _geometry = polyline;
  }

  void Draw(Painter * painter)
  {
    if (_geometry._points.size() < 2)
      return;

    painter->UsePaint(&_paint);
    for (size_t i = 1; i < _geometry._points.size(); ++i)
    {
      PointF & p0 = _geometry._points[i - 1];
      PointF & p1 = _geometry._points[i];
      LineF l(p0, p1);
      painter->DrawLine(l);
    }
  }

  bool Contains(PointF const & p ) override
  {
    return algo::Intersects(p._x, p._y, _geometry);
  }

  void WriteTo(Serializer * ) const override;
};

}
