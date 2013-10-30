#pragma once

namespace geometry {

template <typename T>
class Point2D
{
public:
  T _x;
  T _y;

  Point2D()
    : _x(0), _y(0) {}

  Point2D(T x, T y)
    : _x(x), _y(y) {}
};


template <typename T>
class Line2D
{
public:
  Point2D<T> _start;
  Point2D<T> _end;

  Line2D() {}

  Line2D(Point2D<T> const & start, Point2D<T> const & end)
    : _start(start), _end(end) {}
};

}
