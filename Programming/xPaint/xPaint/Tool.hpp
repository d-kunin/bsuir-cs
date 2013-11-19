#pragma once

#include "gem_lib/Painter/DrawableGeometry.hpp"
#include "gem_lib/Painter/Painter.hpp"
#include "gem_lib/Painter/Scene.hpp"

#include <iostream>
using std::cout;
using std::endl;

class Tool
{
public:

  void virtual OnRecieveStartPoint(int x, int y) = 0;
  void virtual OnRecieveIntermPoint(int x, int y) = 0;
  void virtual OnRecieveEndPoint(int x, int y) = 0;

  virtual painter::Drawable * GetDrawable()
  {
    return _drawable;
  }
  virtual ~Tool()
  {}

  Tool()
    : _scene(NULL),
      _drawable(NULL)
  {}

  void SetScene(painter::Scene * scene) { _scene = scene; }

protected:
  painter::Scene    * _scene;
  painter::Drawable * _drawable;
};


class RectTool : public Tool, public painter::RectDrawable
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _geometry._topLeft = painter::PointF(x,y);
    _geometry._bottomRight = painter::PointF(x,y);

    _drawable = this;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _geometry._bottomRight = painter::PointF(x,y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    RectDrawable * rd = new RectDrawable(_geometry);
    rd->SetPaint(_paint);
    _scene->Drawables().push_back(rd);

    _drawable = NULL;
  }
};


class EllipseTool: public Tool, public painter::EllipseDrawable
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _geometry._center = painter::PointF(x,y);
    _geometry._rX = 0;
    _geometry._rY = 0;

    _drawable = this;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _geometry._rX = _geometry._center._x - x;
    _geometry._rY = _geometry._center._y - y;
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    EllipseDrawable * ed = new EllipseDrawable(_geometry);
    ed->SetPaint(_paint);
    _scene->Drawables().push_back(ed);

    _drawable = NULL;
  }
};

class LineTool: public Tool, public painter::LineDrawable
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _geometry._start = painter::PointF(x,y);
    _geometry._end   = painter::PointF(x,y);

    _drawable = this;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _geometry._end = painter::PointF(x,y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    LineDrawable * ld = new LineDrawable(_geometry);
    ld->SetPaint(_paint);
    _scene->Drawables().push_back(ld);

    _drawable = NULL;
  }
};

class PolylineTool: public Tool, public painter::PolylineDrawable
{
public:
  void OnRecieveStartPoint(int x, int y)
  {
    _geometry._points.clear();
    _geometry.Add(x, y);

    _drawable = this;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _geometry.Add(x, y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    PolylineDrawable * pd = new PolylineDrawable(_geometry);
    pd->SetPaint(_paint);
    _scene->Drawables().push_back(pd);

    _drawable = NULL;
  }
};

class SelectionTool: public Tool
{
public:
  SelectionTool()
  {
    _selectedDrawable = NULL;
    _selectionBorder = NULL;
    _selectionPaint.SetStrokeColor(painter::Color(255, 255 ,0 ,128));
  }

  void OnRecieveStartPoint(int x, int y)
  {
    painter::Drawable * hit = _scene->FindDrawableForPoint(painter::PointF(x,y));
    _startX = x;
    _startY = y;

    if (hit)
    {
      _selectedDrawable = hit;
      _selectionBorder = new painter::RectDrawable(hit->BoundingRect());
      _selectionBorder->SetPaint(_selectionPaint);
    }
    else
    {
      delete _selectionBorder;
      _selectionBorder = NULL;
    }
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    if (_selectedDrawable)
    {
      TransformF transform = TransformF::Translate(x - _startX, y - _startY);
      _selectedDrawable->Transform(transform);
      _selectionBorder->Transform(transform);

      _startX = x;
      _startY = y;
    }
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    /// @todo
  }

  painter::Drawable * GetDrawable() { return _selectionBorder; }

private:
  painter::Drawable     * _selectedDrawable;
  painter::RectDrawable * _selectionBorder;
  painter::Paint _selectionPaint;


  int _startX;
  int _startY;
};
