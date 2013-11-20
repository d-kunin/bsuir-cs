#include "paintwidget.hpp"
#include "gem_lib/Painter/DrawableGeometry.hpp"
#include <QPainter>
#include <QRect>

#include <iostream>


PaintWidget::PaintWidget(QWidget *parent) :
  QWidget(parent)
{
  _tool = new RectTool();
  _tool->SetScene(&_scene);
}

void PaintWidget::SetTool(Tool * tool)
{
  delete _tool;

  _tool = tool;
  _tool->SetScene(&_scene);

  if (_tool->GetDrawable())
    _tool->GetDrawable()->SetPaint(_paint);

  update();
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

void PaintWidget::paintEvent(QPaintEvent * /*event*/)
{
  _painter.begin(this);
  {
    _painter.setRenderHint(QPainter::Antialiasing);
    _xPainter.setPainter(&_painter);
    _scene.Draw(&_xPainter);

    if (_tool->NeedDrawing())
      _tool->GetDrawable()->Draw(&_xPainter);
  }
  _painter.end();
}

void PaintWidget::OnMouseMove(QMouseEvent *event)
{
  if (_tool)
    _tool->OnRecieveIntermPoint(event->x(), event->y());

  update();
}

void PaintWidget::OnMousePress(QMouseEvent *event)
{
  if (_tool)
    _tool->OnRecieveStartPoint(event->x(), event->y());

  update();
}

void PaintWidget::OnMouseRelease(QMouseEvent *event)
{
  if (_tool)
    _tool->OnRecieveEndPoint(event->x(), event->y());

  update();
}

void PaintWidget::OnPaintUpdate()
{
  if (_tool->GetDrawable())
  {
    _tool->GetDrawable()->SetPaint(_paint);
    update();
  }
}

