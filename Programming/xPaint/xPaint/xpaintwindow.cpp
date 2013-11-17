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

void xPaintWindow::on_actionRect_triggered()
{
  _paintWidget->SetTool(new RectTool());
}

void xPaintWindow::on_actionEllipse_triggered()
{
  _paintWidget->SetTool(new EllipseTool());
}

void xPaintWindow::on_actionRemove_Last_triggered()
{
  if (!_paintWidget->GetScene().Drawables().empty())
  {
    _paintWidget->GetScene().Drawables().pop_back();
    _paintWidget->update();
  }
}

void xPaintWindow::on_actionClear_All_triggered()
{
    _paintWidget->GetScene().Drawables().clear();
    _paintWidget->update();
}
