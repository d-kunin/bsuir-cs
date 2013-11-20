#include "xpaintwindow.hpp"
#include "ui_xpaintwindow.h"

#include "QxPainter.hpp"
#include "QT/Converts.hpp"

#include <QColorDialog>

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
  _paintWidget->SetTool(new RectTool);
}

void xPaintWindow::on_actionEllipse_triggered()
{
  _paintWidget->SetTool(new EllipseTool);
}

void xPaintWindow::on_actionLine_triggered()
{
  _paintWidget->SetTool(new LineTool);
}

void xPaintWindow::on_actionRemove_Last_triggered()
{
  if (!_paintWidget->GetScene().Drawables().empty())
  {
    delete _paintWidget->GetScene().Drawables().back();
    _paintWidget->GetScene().Drawables().pop_back();

    _paintWidget->update();
  }
}

void xPaintWindow::on_actionClear_All_triggered()
{
  for (Drawable * d : _paintWidget->GetScene().Drawables())
    delete d;
  _paintWidget->GetScene().Drawables().clear();

  _paintWidget->update();
}

void xPaintWindow::on_actionIncWidth_triggered()
{
  _paintWidget->GetPaint().GetStrokeWidth()+=5;
  _paintWidget->OnPaintUpdate();
}

void xPaintWindow::on_actionDecWidth_triggered()
{
  _paintWidget->GetPaint().GetStrokeWidth()-=5;
  _paintWidget->OnPaintUpdate();
}

void xPaintWindow::on_actionPolyline_triggered()
{
  _paintWidget->SetTool(new PolylineTool);
}

void xPaintWindow::on_actionSelection_Tool_triggered()
{
  _paintWidget->SetTool(new SelectionTool(this));
}

void xPaintWindow::on_actionStroke_Color_triggered()
{
  QColorDialog colorDialog;
  QColor color = colorDialog.getColor
                 (Convert::FromXColor(_paintWidget->GetPaint().GetStrokeColor()),
                  this, tr("Select Stroke Color"),
                  QColorDialog::ShowAlphaChannel);

  if (color.isValid())
  {
    _paintWidget->GetPaint().SetStrokeColor(Convert::FromQColor(color));
    _paintWidget->OnPaintUpdate();
  }
}

void xPaintWindow::on_actionFill_Color_triggered()
{
  QColorDialog colorDialog;
  QColor color = colorDialog.getColor
                 (Convert::FromXColor(_paintWidget->GetPaint().GetFillColor()),
                  this, tr("Select Fill Color"),
                  QColorDialog::ShowAlphaChannel);

  if (color.isValid())
  {
    _paintWidget->GetPaint().SetFillColor(Convert::FromQColor(color));
    _paintWidget->OnPaintUpdate();
  }
}

void xPaintWindow::OnDrawableSelected(Drawable * /*drawable*/)
{
  cout << "Selected" << endl;
}

void xPaintWindow::OnNothingSelected()
{
  cout << "Nothing selected" << endl;
}
