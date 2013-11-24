#pragma once

#include "../gem_lib/Painter/Scene.hpp"
#include "../gem_lib/Painter/Paint.hpp"
#include "../gem_lib/Painter/DrawableGeometry.hpp"
#include "../gem_lib/Painter/qimagedrawable.hpp"

class Serializer
{
public:
  virtual void Write(painter::RectDrawable const *) = 0;
  virtual void Write(painter::EllipseDrawable const *) = 0;
  virtual void Write(painter::LineDrawable const *) = 0;
  virtual void Write(painter::PolylineDrawable const *) = 0;
  virtual void Write(painter::ImageDrawable const *) = 0;

  virtual void Write(painter::Scene const *) = 0;
  virtual void Write(painter::Paint const *) = 0;
  virtual void Write(painter::Color const *) = 0;

  virtual ~Serializer() {}
};
