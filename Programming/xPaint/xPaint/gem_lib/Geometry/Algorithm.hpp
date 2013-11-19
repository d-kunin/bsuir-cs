#pragma once

#include <iostream>
#include "Utils.hpp"
using std::cout;
using std::endl;

#include "Geometry.hpp"

using geometry::Point2D;
using geometry::Rect;
using geometry::Line2D;
using geometry::Ellipse;
using geometry::Polyline;

namespace algo
{

template <typename T>
Rect<T> BoundingRect(Line2D<T> const & line)
{
  return Rect<T>(line._end, line._start);
}

template <typename T>
Rect<T> BoundingRect(Ellipse<T> const & e)
{
  Point2D<T> tl(e._center._x - e._rX, e._center._y - e._rY);
  Point2D<T> br(e._center._x + e._rX, e._center._y + e._rY);
  return Rect<T>(tl, br);
}

template <typename T>
Rect<T> BoundingRect(Polyline<T> const & poly)
{
  Rect<T> r;
  for (Point2D<T> const & point : poly._points)
    r.Inflate(point);
  return r;
}

template <typename T>
bool Intersects(T x, T y, Rect<T> const & r)
{
  return r.Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Line2D<T> const & l)
{
  return BoundingRect(l).Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Ellipse<T> const & ellipse)
{
  return BoundingRect(ellipse).Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Polyline<T> const & poly)
{
  return poly._points.size() < 2 ? false :BoundingRect(poly).Contains(x, y);
}

}
