#include "xpaintwindow.hpp"
#include "ui_xpaintwindow.h"

#include "QxPainter.hpp"
#include "gem_lib/Painter/qimagedrawable.hpp"
#include "QT/Converts.hpp"

#include <QColorDialog>

xPaintWindow::xPaintWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::xPaintWindow)
{
  ui->setupUi(this);
  _paintWidget = new PaintWidget();
  ui->_layout->addWidget(_paintWidget);

  _serializer   = new TextFileSerializer("/Users/markX/temp/drawfile.txt");
  _deserializer = new TextFileSerializer("/Users/markX/temp/drawfile.txt");
}

xPaintWindow::~xPaintWindow()
{
  delete ui;
  delete _paintWidget;
  delete _serializer;
  delete _deserializer;
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
  if (!_paintWidget->GetScene()->Drawables().empty())
  {
    delete _paintWidget->GetScene()->Drawables().back();
    _paintWidget->GetScene()->Drawables().pop_back();

    _paintWidget->update();
  }
}

void xPaintWindow::on_actionClear_All_triggered()
{
  for (Drawable * d : _paintWidget->GetScene()->Drawables())
    delete d;
  _paintWidget->GetScene()->Drawables().clear();

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

void xPaintWindow::OnDrawableSelected(Drawable * drawable)
{
  cout << "Selected" << endl;
  _selectedDrawable = drawable;
}

void xPaintWindow::OnNothingSelected()
{
  cout << "Nothing selected" << endl;
  _selectedDrawable = NULL;
}

void xPaintWindow::on_actionScale_Up_triggered()
{
  if (_selectedDrawable)
  {
    float factor = 3.0/2.0;
    _selectedDrawable->Transform(TransformF::Scale(factor, factor));
    _paintWidget->update();
  }
}

void xPaintWindow::on_actionScale_Down_triggered()
{
  if (_selectedDrawable)
  {
    float factor = 2.0/3.0;
    _selectedDrawable->Transform(TransformF::Scale(factor, factor));
    _paintWidget->update();
  }
}

void xPaintWindow::on_actionRotate_CW_triggered()
{
  if(_selectedDrawable)
  {
    _selectedDrawable->Transform(TransformF::RotateCW(M_PI/8));
    _paintWidget->update();
  }
}

void xPaintWindow::on_actionRotate_CCW_triggered()
{
  if(_selectedDrawable)
  {
    _selectedDrawable->Transform(TransformF::RotateCW(-M_PI/8));
    _paintWidget->update();
  }
}

void xPaintWindow::on_actionLena_triggered()
{
  _paintWidget->GetScene()->Add(new painter::ImageDrawable);
  _paintWidget->update();
}

void xPaintWindow::on_actionSave_triggered()
{
  _serializer->Write(_paintWidget->GetScene());
}

void xPaintWindow::on_actionLoad_triggered()
{
  _paintWidget->SetScene(_deserializer->ReadScene());
}
