#pragma once

#include "gem_lib/Painter/DrawableGeometry.hpp"
#include "gem_lib/Painter/Painter.hpp"
#include "gem_lib/Painter/Scene.hpp"

#include <iostream>
using std::cout;
using std::endl;

using painter::RectDrawable;
using painter::LineDrawable;
using painter::PolylineDrawable;
using painter::EllipseDrawable;
using painter::Drawable;
using painter::Scene;

class Tool
{
public:

  //{@ virtual
  virtual Drawable * GetDrawable() = 0;
  void virtual       OnRecieveStartPoint(int x, int y) = 0;
  void virtual       OnRecieveIntermPoint(int x, int y) = 0;
  void virtual       OnRecieveEndPoint(int x, int y) = 0;

  virtual ~Tool()
  {}
  //@} virtual


  void SetScene(painter::Scene * scene)
  {
    _scene = scene;
  }

  bool NeedDrawing()
  {
    return _needDrawing;
  }

  Tool()
    : _scene(NULL),
      _needDrawing(false)
  {}


protected:
  Scene    * _scene;
  bool _needDrawing;
};


template <typename D>
class DrawTool: public Drawable, public Tool
{
  Drawable * GetDrawable() override
  {
    return &_drawable;
  }

  void Draw(painter::Painter * painter) override
  {
    _drawable.Draw(painter);
  }

  painter::RectF BoundingRect() override
  {
    return _drawable.BoundingRect();
  }

protected:
  D _drawable;
};

class RectTool : public DrawTool<RectDrawable>
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _drawable._geometry._topLeft = painter::PointF(x,y);
    _drawable._geometry._bottomRight = painter::PointF(x,y);

    _needDrawing = true;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _drawable._geometry._bottomRight = painter::PointF(x,y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    RectDrawable * rd = new RectDrawable(_drawable._geometry);

    rd->SetPaint(_drawable.GetPaint());
    _scene->Drawables().push_back(rd);

    _needDrawing = false;
  }
};


class EllipseTool: public DrawTool<EllipseDrawable>
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _drawable._geometry._center = painter::PointF(x,y);
    _drawable._geometry._rX = 0;
    _drawable._geometry._rY = 0;

    _needDrawing = true;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _drawable._geometry._rX = _drawable._geometry._center._x - x;
    _drawable._geometry._rY = _drawable._geometry._center._y - y;
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    EllipseDrawable * ed = new EllipseDrawable(_drawable._geometry);

    ed->SetPaint(_drawable.GetPaint());
    _scene->Drawables().push_back(ed);

    _needDrawing = false;
  }
};


class LineTool: public DrawTool<LineDrawable>
{
public:

  void OnRecieveStartPoint(int x, int y)
  {
    _drawable._geometry._start = painter::PointF(x,y);
    _drawable._geometry._end   = painter::PointF(x,y);

    _needDrawing = true;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _drawable._geometry._end = painter::PointF(x,y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    LineDrawable * ld = new LineDrawable(_drawable._geometry);
    ld->SetPaint(_drawable.GetPaint());
    _scene->Drawables().push_back(ld);

    _needDrawing = false;
  }
};

class PolylineTool: public DrawTool<PolylineDrawable>
{
public:
  void OnRecieveStartPoint(int x, int y)
  {
    _drawable._geometry._points.clear();
    _drawable._geometry.Add(x, y);

    _needDrawing = true;
  }

  void OnRecieveIntermPoint(int x, int y)
  {
    _drawable._geometry.Add(x, y);
  }

  void OnRecieveEndPoint(int /*x*/, int /*y*/)
  {
    PolylineDrawable * pd = new PolylineDrawable(_drawable._geometry);

    pd->SetPaint(_drawable.GetPaint());
    _scene->Drawables().push_back(pd);

    _needDrawing = false;
  }

private:
  painter::PolylineDrawable _poly;
};

class SelectionTool: public Tool
{
public:
  SelectionTool()
  {
    _selectedDrawable = NULL;
    _selectionBorder = NULL;
    _selectionPaint.SetStrokeColor(painter::Color(0, 0 , 255, 64));
    _selectionPaint.SetFillColor(painter::Color(0, 0, 255, 32));
    _selectionPaint.SetStrokeWidth(3);
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

      _needDrawing = true;
    }
    else
    {
      delete _selectionBorder;
      _selectionBorder = NULL;

      _needDrawing = false;
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
