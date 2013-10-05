#pragma once

namespace dkmath
{

// forward declarations to use in parent class;
template <typename T> class Point2d;
template <typename T> class Rect;

template <typename T>
class Geometry
{
public:
  virtual Point2d<T> const center() const = 0;
  virtual bool             contains(Point2d<T> const & point) const = 0;
  virtual Rect<T>    const boundingRect() const = 0;


  virtual ~Geometry() {}
};

// Point
template <typename T>
class Point2d : public Geometry<T>
{
private:
  T _x;
  T _y;

public:
  Point2d(T x, T y)
    : _x(x), _y(y)
  {}

  Point2d()
  {
    this(0,0);
  }

  T x() const { return _x; }
  T y() const { return _y; }

  virtual Point2d<T> const center() const override
  {
    return *this;
  }

  virtual bool contains(Point2d<T> const & point) const override
  {
    return point.x() == _x && point.y() == _y;
  }

  virtual Rect<T> const boundingRect() const override
  {
    return Rect<T>(_y, _x, _y, _x);
  }

  bool operator ==(Point2d<T> const & other)
  {
    return _x == other.x() && _y == other.y();
  }

  bool operator !=(Point2d<T> const & other)
  {
    return !(this == other);
  }
};
// point

// Rect
template <typename T>
class Rect : public Geometry<T>
{
public:
  virtual Point2d<T> const center() const override
  {
    const T centerX = (_right - _left)/2;
    const T centerY = (_top - _bottom)/2;

    return Point2d<T>(centerX, centerY);
  }

  virtual bool contains(Point2d<T> const & point) const override
  {
    if (isDegenerate() || !isValid())
      return false;


    return (point.x() <= _right) && (point.x() >= _left)
        && (point.y() <= _top)   && (point.y() >= _bottom);
  }

  virtual Rect<T> const boundingRect() const override
  {
    return *this;
  }

private:
  T _top;
  T _right;
  T _bottom;
  T _left;

public:

  Rect()
  {
    this(0,0,0,0);
  }

  Rect(T top, T right, T bottom, T left)
   : _top(top), _right(right), _bottom(bottom), _left(left)
  {}

  T width()  const { return _right - _left; }
  T height() const { return _top - _bottom; }

  bool isDegenerate() const { return width() == 0 || height() == 0; }
  bool isValid()      const { return width() >= 0 && height() >= 0; }
};
// rect
}
