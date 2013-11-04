#pragma once

#include "Matrix.hpp"
#include "Geometry.hpp"

#include <cmath>


template <typename T>
class Transform
{
public:
  typedef Matrix<3,3,T> MatrixT;

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

    t._matrix(0,2) = dX;
    t._matrix(1,2) = dY;

    return t;
  }
  static Transform Rotate(T alphaRadians)
  {
    Transform t;

    T cosA = cosf(alphaRadians);
    T sinA = sinf(alphaRadians);

    t._matrix(0,0) = cosA;
    t._matrix(0,1) = sinA;
    t._matrix(1,0) = -sinA;
    t._matrix(1,1) = cosA;

    return t;
  }

  Transform operator*(Transform const & that) const
  {
    Transform t;
    t._matrix = _matrix*that._matrix;
    return t;
  }
  // }@



private:
  MatrixT _matrix;
};
