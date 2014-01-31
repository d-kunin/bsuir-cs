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

  bool operator==(Point2D<T> const & other) const
  {
    return (_x == other._x) && (_y == other._y);
  }

  bool operator !=(Point2D<T> const & other) const
  {
    return !(*this == other);
  }
};

template <typename T>
class Line2D
{
public:
  Point2D<T> _start;
  Point2D<T> _end;

  Line2D()
  {}

  Line2D(Point2D<T> const & start, Point2D<T> const & end)
    : _start(start), _end(end)
  {}

  Line2D(T x0, T y0, T x1, T y1)
    : _start(x0, y0), _end(x1, y1)
  {}
};

template <typename T>
class Rect
{
public:
  Point2D<T> _topLeft, _bottomRight;

  Rect(Point2D<T> topleft, Point2D<T> bottomright)
    : _topLeft(topleft), _bottomRight(bottomright) {}

  Rect(T x0, T y0, T x1, T y1)
    : _topLeft(x0,y0), _bottomRight(x1, y1)
  {}

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

  void Inflate(Rect<T> const & rect)
  {
    Inflate(rect._bottomRight);
    Inflate(rect._topLeft);
  }

  void Inflate(T dx, T dy)
  {
    Inflate(Point2D<T>(_bottomRight._x + dx, _bottomRight._y + dy));
    Inflate(Point2D<T>(_topLeft._x - dx, _topLeft._y - dy));
  }
};

template <typename T>
class Ellipse
{
public:
  Point2D<T> _center;
  Point2D<T> _radius;

  Ellipse(Point2D<T> center, T rX, T rY)
    : _center(center), _radius(rX, rY) {}

  Ellipse(Point2D<T> center, Point2D<T> radius)
    : _center(center), _radius(radius)
  {}

  Ellipse(T x0, T y0, T rx, T ry)
    : _center(x0, y0), _radius(rx, ry)
  {}

  Ellipse()
  {}

  T & radiusX()
  {
    return _radius._x;
  }

  T & radiusY()
  {
    return _radius._y;
  }

  T radiusX() const
  {
    return _radius._x;
  }

  T radiusY() const
  {
    return _radius._y;
  }
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

  void Add(T x, T y)
  {
    Point2D<T> _newP(x, y);
    if (_points.empty() || (_newP != _points.back()))
      _points.push_back(Point2D<T>(x,y));
  }
};

}
