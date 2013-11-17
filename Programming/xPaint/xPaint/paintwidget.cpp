#include "paintwidget.hpp"
#include "gem_lib/Painter/DrawableGeometry.hpp"
#include <QPainter>
#include <QRect>

#include <iostream>


PaintWidget::PaintWidget(QWidget *parent) :
  QWidget(parent), _geometry(NONE), _currentDrawable(NULL)
{
}

void PaintWidget::mouseMoveEvent(QMouseEvent * event)
{
  QWidget::mouseMoveEvent(event);
  OnMouseMove(event);
}

void PaintWidget::mousePressEvent(QMouseEvent * event)
{
  QWidget::mousePressEvent(event);
  OnMousePress(event);
}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event)
{
  QWidget::mouseReleaseEvent(event);
  OnMouseRelease(event);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
  _painter.begin(this);
  _xPainter.setPainter(&_painter);

  if (_currentDrawable)
  {
    _currentDrawable->Draw(&_xPainter);
  }

  _scene.Draw(&_xPainter);
  _painter.end();
}

void PaintWidget::OnMouseMove(QMouseEvent *event)
{
  _endPoint = QPoint(event->x(), event->y());

  if (_currentDrawable)
  {
    RectDrawable * rd = dynamic_cast<RectDrawable*>(_currentDrawable);
    if (rd)
    {
      rd->_rect._bottomRight = PointF(_endPoint.x(), _endPoint.y());
    }
  }

  update();
}

void PaintWidget::OnMousePress(QMouseEvent *event)
{
  _startPoint = QPoint(event->x(), event->y());

  // for now let it be rect
  _currentDrawable = new RectDrawable(RectF(PointF(_startPoint.x(), _startPoint.y()),
                                      PointF(_startPoint.x(), _startPoint.y())));

  update();
}

void PaintWidget::OnMouseRelease(QMouseEvent *event)
{
  _endPoint = QPoint(event->x(), event->y());

  if (_currentDrawable)
  {
    _scene.Drawables().push_back(_currentDrawable);
    _currentDrawable = NULL;
  }

  update();
}

