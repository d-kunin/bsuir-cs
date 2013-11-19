#pragma once

#include "Matrix.hpp"
#include "Geometry.hpp"

#include <cmath>

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
  //}@

  //{@ Geometry-specific transforms
  Point2D<T> operator*(Point2D<T> const & point) const
  {
    HGPointT hgp = MakeHGPoint(point);
    hgp = hgp*_matrix;
    return FromHG(hgp);
  }

  Rect<T> operator *(Rect<T> const & rect) const
  {
    return Rect<T>((*this)*rect._topLeft, (*this)*rect._bottomRight);
  }

  Ellipse<T> operator *(Ellipse<T> const & ellipse) const
  {
    /// @todo Add axixes transform
    return Ellipse<T>((*this)*ellipse._center,
                      ellipse._rX, ellipse._rY);
  }

  Line2D<T> operator *(Line2D<T> const & line) const
  {
    return Line2D<T>((*this)*line._start, (*this)*line._end);
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
