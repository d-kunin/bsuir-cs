#ifndef XPAINTWINDOW_HPP
#define XPAINTWINDOW_HPP

#include <QPainter>
#include <QMainWindow>

#include "paintwidget.hpp"

namespace Ui {
class xPaintWindow;
}

class xPaintWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit xPaintWindow(QWidget *parent = 0);
  ~xPaintWindow();

private:
  Ui::xPaintWindow *ui;
  PaintWidget * _paintWidget;
};

#endif // XPAINTWINDOW_HPP
