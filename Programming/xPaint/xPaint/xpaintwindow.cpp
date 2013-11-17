#include "xpaintwindow.hpp"
#include "ui_xpaintwindow.h"

#include "QxPainter.hpp"

xPaintWindow::xPaintWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::xPaintWindow)
{
  ui->setupUi(this);
  _paintWidget = new PaintWidget();

  ui->_layout->addWidget(_paintWidget);
}

xPaintWindow::~xPaintWindow()
{
  delete ui;
  delete _paintWidget;
}
