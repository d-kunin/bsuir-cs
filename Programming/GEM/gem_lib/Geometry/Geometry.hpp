#pragma once

#include "Transform.hpp"

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

template <typename T>
class Rect
{
public:
  Point2D<T> _topLeft, _bottomRight;

  Rect(Point2D<T> topleft, Point2D<T> bottomright)
    : _topLeft(topleft), _bottomRight(bottomright) {}

  Rect() {}

  T Width() {
    return _bottomRight._x - _topLeft._x;
  }

  T Height() {
    return _bottomRight.y - _topLeft._y;
  }
};

template <typename T>
class Ellipse
{
public:
  Point2D<T> _center;
  T _rX;
  T _rY;

  Ellipse(Point2D<T> center, T rh, T rv)
    : _center(center), _rX(rh), _rY(rv) {}

  Ellipse()
    : _rX(0), _rY(0) {}
};

template <typename T>
class Polygon
{
//NO-OP
};

}
