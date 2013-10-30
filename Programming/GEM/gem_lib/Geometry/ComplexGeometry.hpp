#pragma once

#include "PrimitiveGeometry.hpp"
#include "../Commons.hpp"

namespace geometry {

//{@ Shapes
template <typename T>
class Rect {
public:
  Point2D<T> _topleft, _bottomright;

  Rect(Point2D<T> topleft, Point2D<T> bottomright)
    : _topleft(topleft), _bottomright(bottomright) {}

  Rect() {}

  T Width() {
    return _bottomright._x - _topleft._x;
  }

  T Height() {
    return _bottomright.y - _topleft._y;
  }
};


template <typename T>
class Ellipse {
public:
  Point2D<T> _center;
  T _rx;
  T _ry;

  Ellipse(Point2D<T> center, T rh, T rv)
    : _center(center), _rx(rh), _ry(rv) {}

  Ellipse()
    : _rx(0), _ry(0) {}
};

template <typename T>
class Polygon {
//NO-OP
};

//{@
}
