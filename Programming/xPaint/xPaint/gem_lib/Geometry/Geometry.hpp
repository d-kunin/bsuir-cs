#pragma once

#include <vector>
#include <algorithm>

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

  T Width() const
  {
    return _bottomRight._x - _topLeft._x;
  }

  T Height() const
  {
    return _bottomRight._y - _topLeft._y;
  }

  bool Contains(Point2D<T> const & point) const
  {
    T minX = std::min(_bottomRight._x ,_topLeft._x);
    T maxX = std::max(_bottomRight._x, _topLeft._x);
    T minY = std::min(_bottomRight._y, _topLeft._y);
    T maxY = std::max(_bottomRight._y, _topLeft._y);

    return (point._x <= maxX) && (point._x >= minX)
        && (point._y <= maxY) && (point._y >= minY);
  }

  bool Contains(T x, T y) const
  {
    return Contains(Point2D<T>(x, y));
  }

  void Inflate(Point2D<T> const & point)
  {
    if (Contains(point))
      return;

    // change borders
    T minX = std::min(_bottomRight._x ,_topLeft._x);
    T maxX = std::max(_bottomRight._x, _topLeft._x);
    T minY = std::min(_bottomRight._y, _topLeft._y);
    T maxY = std::max(_bottomRight._y, _topLeft._y);

    if (point._x > maxX)
      maxX = point._x;
    else if (point._x < minX)
      minX = point._x;

    if (point._y > maxY)
      maxY = point._y;
    else if (point._y < minY)
      minY = point._y;

    _bottomRight = Point2D<T>(maxX, maxY);
    _topLeft = Point2D<T>(minX, minY);
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
