#pragma once

#include "Geometry.hpp"

#include <string>
#include <sstream>

using namespace std;
using namespace geometry;

template <typename T>
string ToStr(Point2D<T> const & point)
{
  ostringstream ss;
  ss << "p:(" << point._x << "," << point._y << ")";
  return ss.str();
}

template <typename T>
string ToStr(Line2D<T> const & line)
{
  ostringstream ss;
  ss << "l:[" << ToStr(line._start) << " -> " << ToStr(line._end) << "]";
  return ss.str();
}

template <typename T>
string ToStr(Rect<T> const & rect)
{
  ostringstream ss;
  ss << "r:[ tl=" << ToStr(rect._topLeft) << ", br=" << ToStr(rect._bottomRight) << "]";
  return ss.str();
}

template <typename T>
string ToStr(Ellipse<T> const & elli)
{
  ostringstream ss;
  ss << "e:[ c=" << ToStr(elli._center) << ", rh=" << elli._rX << " rv=" << elli._rY << "]";
  return ss.str();
}

template<template<typename> class G, typename T>
ostream & operator<<(ostream & out, G<T> const & geometry)
{
  return out << ToStr(geometry);
}
