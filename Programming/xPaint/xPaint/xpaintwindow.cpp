#include "xpaintwindow.hpp"
#include "ui_xpaintwindow.h"

#include "QxPainter.hpp"
#include "gem_lib/Painter/qimagedrawable.hpp"
#include "QT/Converts.hpp"

#include <QColorDialog>
#include <QFileDialog>

#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#include <math.h>

xPaintWindow::xPaintWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::xPaintWindow)
{
  ui->setupUi(this);
  _paintWidget = new PaintWidget();
  ui->_layout->addWidget(_paintWidget, 1);

  // tools
  connect(ui->_rbRect,      SIGNAL(toggled(bool)), SLOT(on_rect_tool(bool)));
  connect(ui->_rbLine,      SIGNAL(toggled(bool)), SLOT(on_line_tool(bool)));
  connect(ui->_rbEllipse,   SIGNAL(toggled(bool)), SLOT(on_ellipse_tool(bool)));
  connect(ui->_rbPoly,      SIGNAL(toggled(bool)), SLOT(on_polyline_tool(bool)));
  connect(ui->_rbSelection, SIGNAL(toggled(bool)), SLOT(on_selection_tool(bool)));
  // paint
  connect(ui->_sldStrokeWidth, SIGNAL(valueChanged(int)), SLOT(on_stroke_width_changed(int)));
  connect(ui->_btnStrokeColor, SIGNAL(clicked()),         SLOT(on_stroke_color_clicked()));
  connect(ui->_btnFillColor,   SIGNAL(clicked()),         SLOT(on_fill_color_clicked()));
  // transform
  connect(ui->_btnScale,     SIGNAL(clicked()), SLOT(on_scale()));
  connect(ui->_btnTranslate, SIGNAL(clicked()), SLOT(on_translate()));
  connect(ui->_btnRotateCCW, SIGNAL(clicked()), SLOT(on_rotate_ccw()));
  connect(ui->_btnRotateCW,  SIGNAL(clicked()), SLOT(on_rotate_cw()));
  connect(ui->_btnRemove,    SIGNAL(clicked()), SLOT(on_remove_item()));
  // file
  connect(ui->actionSave, SIGNAL(triggered()), SLOT(on_save_action()));
  connect(ui->actionLoad, SIGNAL(triggered()), SLOT(on_load_action()));
  connect(ui->actionLena, SIGNAL(triggered()), SLOT(on_add_image()));
  // z-order
  connect(ui->_btnToBack,  SIGNAL(clicked()),   SLOT(on_to_back()));
  connect(ui->_btnToFront, SIGNAL(clicked()),   SLOT(on_to_front()));

  OnColorUpdate();
  SetUpEditting(false);
}

xPaintWindow::~xPaintWindow()
{
  delete ui;
  delete _paintWidget;
}

void xPaintWindow::SetUpEditting(bool isEdditing)
{
  QWidget * edits[] = {
    ui->_btnRemove,
    ui->_btnRotateCW,
    ui->_btnRotateCCW,
    ui->_btnScale,
    ui->_btnTranslate,
    ui->_sbScaleX,
    ui->_sbScaleY,
    ui->_sbTransX,
    ui->_sbTransY,
    ui->_btnToBack,
    ui->_btnToFront,
  };

  QWidget * edits2[] = {
    ui->_sldStrokeWidth,
    ui->_colorFill,
    ui->_colorStroke,
  };

  for (QWidget * w : edits)
    w->setEnabled(isEdditing);

  for (QWidget * w : edits2)
    w->setEnabled(!isEdditing);
}

void xPaintWindow::OnColorUpdate()
{
  QPalette paletteFill = ui->_colorFill->palette();
  paletteFill.setColor(QPalette::Background, Convert::FromXColor(_paintWidget->GetPaint().GetFillColor()));
  ui->_colorFill->setAutoFillBackground(true);
  ui->_colorFill->setPalette(paletteFill);

  QPalette paletteStroke = ui->_colorStroke->palette();
  paletteStroke.setColor(QPalette::Background, Convert::FromXColor(_paintWidget->GetPaint().GetStrokeColor()));
  ui->_colorStroke->setAutoFillBackground(true);
  ui->_colorStroke->setPalette(paletteStroke);
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

void xPaintWindow::on_remove_item()
{
  if (_selectedDrawable)
  {
    _paintWidget->GetScene()->Remove(_selectedDrawable);
    _selectedDrawable = NULL;
    _paintWidget->update();
    SetUpEditting(false);
  }
}

void xPaintWindow::on_actionClear_All_triggered()
{
  for (Drawable * d : _paintWidget->GetScene()->Drawables())
    delete d;
  _paintWidget->GetScene()->Drawables().clear();

  _paintWidget->update();
}

void xPaintWindow::on_stroke_color_clicked()
{
  QColorDialog colorDialog;
  QColor color = colorDialog.getColor
                 (Convert::FromXColor(_paintWidget->GetPaint().GetStrokeColor()),
                  this, tr("Select Stroke Color"),
                  QColorDialog::ShowAlphaChannel);

  if (color.isValid())
  {
    _paintWidget->SetStrokeColor(Convert::FromQColor(color));
    OnColorUpdate();
  }
}

void xPaintWindow::on_fill_color_clicked()
{
  QColorDialog colorDialog;
  QColor color = colorDialog.getColor
                 (Convert::FromXColor(_paintWidget->GetPaint().GetFillColor()),
                  this, tr("Select Fill Color"),
                  QColorDialog::ShowAlphaChannel);

  if (color.isValid())
  {
    _paintWidget->SetFillColor(Convert::FromQColor(color));
    OnColorUpdate();
  }
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

void xPaintWindow::on_scale()
{
  if (_selectedDrawable)
  {
    float factorX = ui->_sbScaleX->value();
    float factorY = ui->_sbScaleY->value();
    _selectedDrawable->Transform(TransformF::Scale(factorX, factorY));
    _paintWidget->update();
  }
}

void xPaintWindow::on_translate()
{
  if (_selectedDrawable)
  {
    int transX = ui->_sbTransX->value();
    int transY = ui->_sbTransY->value();
    _selectedDrawable->Transform(TransformF::Translate(transX, transY));
    _paintWidget->update();
  }
}

void xPaintWindow::on_rotate_cw()
{
  if(_selectedDrawable)
  {
    _selectedDrawable->Transform(TransformF::RotateCW(M_PI/2));
    _paintWidget->update();
  }
}

void xPaintWindow::on_rotate_ccw()
{
  if(_selectedDrawable)
  {
    _selectedDrawable->Transform(TransformF::RotateCW(-M_PI/2));
    _paintWidget->update();
  }
}

void xPaintWindow::on_add_image()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Add Image"), QString(),
                                                  tr("Images (*.png *.jpg *.jpeg)"));

  if (!fileName.isEmpty())
  {
    _paintWidget->GetScene()->Add(new painter::ImageDrawable(fileName.toStdString()));
    _paintWidget->update();
  }
}

void xPaintWindow::on_save_action()
{

  QString fileName = QFileDialog::getSaveFileName(this, tr("Save To File"), QString(),
                                                  tr("(*.txt *.jcvd)"));

  if (!fileName.isEmpty())
  {
    TextFileSerializer tfs(fileName.toStdString());
    tfs.Write(_paintWidget->GetScene());
  }
}

void xPaintWindow::on_load_action()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                  tr("(*.jcvd *.txt)"));

  if (!fileName.isEmpty())
  {
    TextFileSerializer tfs(fileName.toStdString());
    _paintWidget->SetScene(tfs.ReadScene());

    if (_selectedDrawable)
    {
      _selectedDrawable = NULL;
      SetUpEditting(false);
    }
  }
}

void xPaintWindow::on_stroke_width_changed(int value)
{
  _paintWidget->SetStrokeWidth(value);
}

void xPaintWindow::on_rect_tool(bool checked)
{
  if (checked && !dynamic_cast<RectTool*>(_paintWidget->GetTool()))
      _paintWidget->SetTool(new RectTool);
}

void xPaintWindow::on_line_tool(bool checked)
{
  if (checked && !dynamic_cast<LineTool*>(_paintWidget->GetTool()))
      _paintWidget->SetTool(new LineTool);
}

void xPaintWindow::on_ellipse_tool(bool checked)
{
  if (checked && !dynamic_cast<EllipseTool*>(_paintWidget->GetTool()))
      _paintWidget->SetTool(new EllipseTool);
}

void xPaintWindow::on_polyline_tool(bool checked)
{
  if (checked && !dynamic_cast<PolylineTool*>(_paintWidget->GetTool()))
      _paintWidget->SetTool(new PolylineTool);
}

void xPaintWindow::on_selection_tool(bool checked)
{
  SetUpEditting(checked);
   if (!dynamic_cast<SelectionTool*>(_paintWidget->GetTool()))
     _paintWidget->SetTool(new SelectionTool(this));
}

void xPaintWindow::on_to_back()
{
  if (_selectedDrawable)
  {
    _paintWidget->GetScene()->MoveToBack(_selectedDrawable);
    _paintWidget->update();
  }
}

void xPaintWindow::on_to_front()
{
  if (_selectedDrawable)
  {
    _paintWidget->GetScene()->MoveToFront(_selectedDrawable);
    _paintWidget->update();
  }
}
