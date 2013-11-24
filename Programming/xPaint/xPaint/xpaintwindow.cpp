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
  ui->_layout->addWidget(_paintWidget, 1);

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

void xPaintWindow::SetUpEditting(bool isEdditing)
{
  QWidget* edits[] = {
    ui->_btnRemove,
    ui->_btnRotateCW,
    ui->_btnRotateCCW,
    ui->_btnScale,
    ui->_btnTranslate,
    ui->_sbScaleX,
    ui->_sbScaleY,
    ui->_sbTransX,
    ui->_sbTransY,
  };

  for (QWidget * w : edits)
    w->setEnabled(isEdditing);
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
    _paintWidget->SetStrokeColor(Convert::FromQColor(color));
}

void xPaintWindow::on_actionFill_Color_triggered()
{
  QColorDialog colorDialog;
  QColor color = colorDialog.getColor
                 (Convert::FromXColor(_paintWidget->GetPaint().GetFillColor()),
                  this, tr("Select Fill Color"),
                  QColorDialog::ShowAlphaChannel);

  if (color.isValid())
    _paintWidget->SetFillColor(Convert::FromQColor(color));
}

void xPaintWindow::OnDrawableSelected(Drawable * drawable)
{
  _selectedDrawable = drawable;
  SetUpEditting(true);
}

void xPaintWindow::OnNothingSelected()
{
  _selectedDrawable = NULL;
  SetUpEditting(false);
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

void xPaintWindow::on__sldStrokeWidth_valueChanged(int value)
{
  _paintWidget->SetStrokeWidth(value);
}
