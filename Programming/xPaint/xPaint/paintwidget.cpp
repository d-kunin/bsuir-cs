#include "paintwidget.hpp"
#include "gem_lib/Painter/DrawableGeometry.hpp"
#include <QPainter>
#include <QRect>

#include <iostream>


PaintWidget::PaintWidget(QWidget *parent) :
  QWidget(parent), _isToolActive(false)
{
  _tool = new RectTool(&_scene);
}

void PaintWidget::SetTool(Tool * tool)
{
  delete _tool;
  _tool = tool;
  _tool->SetScene(&_scene);
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

  if (_isToolActive)
    _tool->GetDrawable()->Draw(&_xPainter);

  _scene.Draw(&_xPainter);

  _painter.end();
}

void PaintWidget::OnMouseMove(QMouseEvent *event)
{
  _endPoint = QPoint(event->x(), event->y());

  if (_tool)
    _tool->OnRecieveIntermPoint(event->x(), event->y());

  update();
}

void PaintWidget::OnMousePress(QMouseEvent *event)
{
  _isToolActive = true;


  _startPoint = QPoint(event->x(), event->y());

  if (_tool)
    _tool->OnRecieveStartPoint(event->x(), event->y());

  update();
}

void PaintWidget::OnMouseRelease(QMouseEvent *event)
{
  _isToolActive = false;

  _endPoint = QPoint(event->x(), event->y());

  if (_tool)
    _tool->OnRecieveEndPoint(event->x(), event->y());

  update();
}

