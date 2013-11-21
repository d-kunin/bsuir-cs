#pragma once

#include <QPainter>
#include <QMainWindow>

#include "paintwidget.hpp"
#include "Tool.hpp"

namespace Ui {
class xPaintWindow;
}

class xPaintWindow : public QMainWindow, public SelectionTool::SelectionListener
{
  Q_OBJECT

public:
  explicit xPaintWindow(QWidget *parent = 0);
  ~xPaintWindow();

  void OnDrawableSelected(Drawable *drawable) override;
  void OnNothingSelected() override;

private slots:
  void on_actionRect_triggered();

  void on_actionEllipse_triggered();

  void on_actionRemove_Last_triggered();

  void on_actionClear_All_triggered();

  void on_actionLine_triggered();

  void on_actionIncWidth_triggered();

  void on_actionDecWidth_triggered();

  void on_actionPolyline_triggered();

  void on_actionSelection_Tool_triggered();

  void on_actionStroke_Color_triggered();

  void on_actionFill_Color_triggered();

  void on_actionScale_Up_triggered();

  void on_actionScale_Down_triggered();

  void on_actionRotate_CW_triggered();

  void on_actionRotate_CCW_triggered();

private:
  Ui::xPaintWindow *ui;
  PaintWidget * _paintWidget;

  Drawable * _selectedDrawable;
};
