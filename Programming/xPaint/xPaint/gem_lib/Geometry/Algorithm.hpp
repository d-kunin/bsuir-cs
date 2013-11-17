#pragma once

#include "Geometry.hpp"

using geometry::Point2D;
using geometry::Rect;
using geometry::Line2D;
using geometry::Ellipse;
using geometry::Polyline;

namespace algo
{

template <typename T>
bool Intersects(T x, T y, Rect<T> const & r)
{
  return r.Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Line2D<T> const & l)
{
  Rect<T> testRect(l._end, l._start);
  return testRect.Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Ellipse<T> const & e)
{
  Point2D<T> tl(e._center._x - e._rX, e._center._y - e._rY);
  Point2D<T> br(e._center._x + e._rX, e._center._y + e._rY);
  Rect<T> testRect(tl, br);
  return testRect.Contains(x, y);
}

template <typename T>
bool Intersects(T x, T y, Polyline<T> const & poly)
{
  if (poly._points.size() < 2)
    return false;

  Rect<T> testRect;
  for (Point2D<T> & p : poly._points)
    testRect.Inflate(p);

  return testRect.Contains(x, y);
}

}
