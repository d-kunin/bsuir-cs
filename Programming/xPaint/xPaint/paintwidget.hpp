#pragma once

#include "Tool.hpp"
#include "QxPainter.hpp"

#include "gem_lib/Painter/Scene.hpp"

#include <QWidget>
#include <QMouseEvent>

class PaintWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PaintWidget(QWidget *parent = 0);
  ~PaintWidget();

  void SetTool(Tool * tool);
  painter::Scene * GetScene() { return _scene; }
  void             SetScene(Scene * scene);
  painter::Paint & GetPaint() { return _paint; }


  void SetFillColor(painter::Color const & color);
  void SetStrokeColor(painter::Color const & color);
  void SetStrokeWidth(float width);

signals:

public slots:
  void OnMousePress(QMouseEvent * event);
  void OnMouseRelease(QMouseEvent * event);
  void OnMouseMove(QMouseEvent * event);

protected:
  void paintEvent(QPaintEvent *event);

  void mouseMoveEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

private:
  void OnPaintUpdate();


  painter::QxPainter _xPainter;
  QPainter _painter;
  painter::Paint _paint;

  painter::Scene * _scene;
  Tool           * _tool;
};
