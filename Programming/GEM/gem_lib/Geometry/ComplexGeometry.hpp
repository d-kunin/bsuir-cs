#pragma once

#include "PrimitiveGeometry.hpp"
#include "../Commons.hpp"

namespace geometry {

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
