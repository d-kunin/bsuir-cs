#ifndef PAINTWIDGET_HPP
#define PAINTWIDGET_HPP

#include "Geometry.hpp"
#include "QxPainter.hpp"

#include "gem_lib/Painter/Scene.hpp"

#include <QWidget>
#include <QMouseEvent>

class PaintWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PaintWidget(QWidget *parent = 0);

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
     bool _isDrawing;
     QPoint _startPoint;
     QPoint _endPoint;
     QxPainter _xPainter;
     QPainter _painter;
     GeometryType _geometry;
     painter::Scene _scene;

     Drawable * _currentDrawable;
};

#endif // PAINTWIDGET_HPP
