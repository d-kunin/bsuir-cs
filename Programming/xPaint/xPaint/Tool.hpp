#pragma once

#include "gem_lib/Painter/DrawableGeometry.hpp"
#include "gem_lib/Painter/Painter.hpp"
#include "gem_lib/Painter/Scene.hpp"

class Tool
{
public:

  void virtual OnRecieveStartPoint(int x, int y) = 0;
  void virtual OnRecieveIntermPoint(int x, int y) = 0;
  void virtual OnRecieveEndPoint(int x, int y) = 0;
  virtual painter::Drawable * GetDrawable() = 0;

  void SetScene(painter::Scene * scene) { _scene = scene; }

  ~Tool() {}

protected:
  painter::Scene * _scene;
};


class RectTool : public Tool, public painter::RectDrawable
{
public:
  RectTool()
  {}

  RectTool(painter::Scene * scene)
  {
    _scene = scene;
  }

  void OnRecieveStartPoint(int x, int y)
  {
    _rect._topLeft = painter::PointF(x,y);
    _rect._bottomRight = painter::PointF(x,y);
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _rect._bottomRight = painter::PointF(x,y);
  }

  void OnRecieveEndPoint(int x, int y)
  {
    _scene->Drawables().push_back(new RectDrawable(_rect));
  }

  painter::Drawable * GetDrawable() { return this; }
};


class EllipseTool: public Tool, public painter::EllipseDrawable
{
public:
  EllipseTool()
  {
    _scene = NULL;
  }

  EllipseTool(painter::Scene * scene)
  {
    _scene = scene;
  }

  void OnRecieveStartPoint(int x, int y)
  {
    _ellipse._center = painter::PointF(x,y);
    _ellipse._rX = 0;
    _ellipse._rY = 0;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _ellipse._rX = _ellipse._center._x - x;
    _ellipse._rY = _ellipse._center._y - y;
  }

  void OnRecieveEndPoint(int x, int y)
  {
    _scene->Drawables().push_back(new EllipseDrawable(_ellipse));
  }

  painter::Drawable * GetDrawable() { return this; }
};


