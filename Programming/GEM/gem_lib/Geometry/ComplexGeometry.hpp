#pragma once

#include "PrimitiveGeometry.hpp"
#include "../Commons.hpp"

namespace geometry {

template <typename T>
class Polyline {
public:

  vector<Point2D<T> > & Points() {
    return _points;
  }

  Point2D<T> & PointAt(size_t index) {
    return _points[index];
  }

  size_t PointsCount() {
    return _points.size();
  }

private:
  vector<Point2D<T> > _points;
};

template <typename T>
class Rect {
public:
  Point2D<T> _topleft, _bottomright;

  Rect(Point2D<T> topleft, Point2D<T> bottomright)
    : _topleft(topleft), _bottomright(bottomright) {}

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
  T _rh;
  T _rv;

  Ellipse(Point2D<T> center, T rh, T rv)
    : _center(center), _rh(rh), _rv(rv) {}
};

}
