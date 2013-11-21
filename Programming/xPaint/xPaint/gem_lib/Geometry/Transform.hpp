#pragma once

#include "Matrix.hpp"
#include "Geometry.hpp"

#include <math.h>

namespace geometry
{

template <typename T>
class Transform
{
public:
  typedef Matrix<3,3,T> MatrixT;
  typedef Matrix<1,3,T> HGPointT; // Homogeneous point

  Transform()
    : _matrix(MatrixT::Identity()) {}

  T & dX()
  {
    return _matrix(2,0);
  }

  T & dY()
  {
    return _matrix(2,1);
  }

  T & scaleX()
  {
    return _matrix(0,0);
  }

  T & scaleY()
  {
    return _matrix(1,1);
  }

  T dX() const
  {
    return _matrix(2,0);
  }

  T dY() const
  {
    return _matrix(2,1);
  }

  T scaleX() const
  {
    return _matrix(0,0);
  }

  T scaleY() const
  {
    return _matrix(1,1);
  }

  //{@ Basic transforms
  static Transform Scale(T sX, T sY)
  {
    Transform t;

    t._matrix(0,0) = sX;
    t._matrix(1,1) = sY;

    return t;
  }

  static Transform Translate(T dX, T dY)
  {
    Transform t;

    t._matrix(2,0) = dX;
    t._matrix(2,1) = dY;

    return t;
  }

  static Transform RotateCW(T alphaRadians)
  {
    Transform t;

    T cosA = cosf(alphaRadians);
    T sinA = sinf(alphaRadians);

    t._matrix(0,0) = cosA;
    t._matrix(0,1) = -sinA;
    t._matrix(1,0) = sinA;
    t._matrix(1,1) = cosA;
    t._matrix(2,2) = 1;

    return t;
  }

  Transform operator*(Transform const & that) const
  {
    Transform t;
    t._matrix = _matrix*that._matrix;
    return t;
  }

  static Transform WithFixedPoint(Transform const & t, Point2D<T> const & p)
  {
    return Transform::Translate(-p._x, -p._y)
        * t
        * Transform::Translate(p._x, p._y);
  }

  //}@

  //{@ Geometry-specific transforms
  // POINT
  Point2D<T> operator*(Point2D<T> const & point) const
  {
    HGPointT hgp = MakeHGPoint(point);
    hgp = hgp*_matrix;
    return FromHG(hgp);
  }

  // RECT
  Rect<T> operator *(Rect<T> const & rect) const
  {
    Transform t = WithFixedPoint(*this, rect._topLeft);
    return Rect<T>(t*rect._topLeft, t*rect._bottomRight);
  }

  // ELLIPSE
  Ellipse<T> operator *(Ellipse<T> const & ellipse) const
  {
    Transform t = WithFixedPoint(*this, ellipse._center);
    return Ellipse<T>(t*ellipse._center,
                      ellipse.radiusX()*t.scaleX(),
                      ellipse.radiusY()*t.scaleY());
  }

  // LINE
  Line2D<T> operator *(Line2D<T> const & line) const
  {
    return Line2D<T>((*this)*line._start, (*this)*line._end);
  }

  // POLYLINE
  Polyline<T> operator *(Polyline<T> const & poly) const
  {
    std::vector<Point2D<T>> points(poly._points.size());

    for (size_t i = 0; i < points.size(); ++i)
      points[i] = (*this)*poly._points[i];

    return Polyline<T>(points);
  }
  //}@

private:
  MatrixT _matrix;

  //{@ We work in homogenous system
  static HGPointT MakeHGPoint(Point2D<T> const & source)
  {
    HGPointT hgp;
    hgp(0,0) = source._x;
    hgp(0,1) = source._y;
    hgp(0,2) = 1;

    return hgp;
  }

  static Point2D<T> FromHG(HGPointT const & source)
  {
    Point2D<T> p(source(0,0)/source(0,2), source(0,1)/source(0,2));
    return p;
  }
  //}@
};

}
