#pragma once

#include "gem_lib/Painter/Painter.hpp"
#include "gem_lib/Geometry/Geometry.hpp"
#include "gem_lib/Geometry/Utils.hpp"

#include <QPainter>

using namespace painter;

class QxPainter : public painter::Painter
{
public:
  QxPainter()
  {
  }

  void setPainter(QPainter * painter) { _nativePainter = painter; }

  virtual void DrawPoint(PointF const & point)
  {
    _nativePainter->drawPoint(QPoint(point._x, point._y));
  }

  virtual void DrawLine(LineF const & line)
  {
    _nativePainter->drawLine(line._start._x, line._start._y, line._end._x, line._end._y);
  }

  virtual void DrawRect(RectF const & rect)
  {
    _nativePainter->drawRect(rect._topLeft._x, rect._topLeft._y, rect.Width(), rect.Height());
  }

  virtual void DrawEllipse(EllipseF const & ellipse)
  {
    _nativePainter->drawEllipse(QPoint(ellipse._center._x, ellipse._center._y),
                                static_cast<int>(ellipse._rX), static_cast<int>(ellipse._rY));
  }

  virtual void UsePaint(Paint * paint)
  {
    QPen pen;
    pen.setWidth(paint->GetStrokeWidth());
    Color c = paint->GetStrokeColor();
    pen.setColor(QColor(c.r,c.g,c.b, c.a));

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 255, 64));

    _nativePainter->setPen(pen);
    _nativePainter->setBrush(brush);
  }

  float TargetWidth() { return 0; }
  float TargetHeight() { return 0; }

  ~QxPainter()
  {
  }

private:
  QPainter * _nativePainter;
};
