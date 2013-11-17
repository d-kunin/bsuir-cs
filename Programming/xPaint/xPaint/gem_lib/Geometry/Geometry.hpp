#pragma once

#include <vector>

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

  T Width() const {
    return _bottomRight._x - _topLeft._x;
  }

  T Height() const {
    return _bottomRight._y - _topLeft._y;
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
class Polyline
{
public:
  std::vector<Point2D<T> > _points;

  Polyline()
  {}

  Polyline(std::vector<Point2D<T> > points)
  {
    _points = points;
  }

  void Add(T x, T y) { _points.push_back(Point2D<T>(x,y)); }
};

}
