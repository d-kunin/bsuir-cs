#pragma once

#include <QPainter>
#include <QMainWindow>

#include "paintwidget.hpp"
#include "Tool.hpp"
#include "io/textfileserializer.hpp"

namespace Ui {
class xPaintWindow;
}

class xPaintWindow : public QMainWindow,
                     public SelectionTool::SelectionListener
{
  Q_OBJECT

public:
  explicit xPaintWindow(QWidget *parent = 0);
  ~xPaintWindow();

  void OnDrawableSelected(Drawable *drawable) override;
  void OnNothingSelected() override;

private slots:
  void on_actionRemove_Last_triggered();

  void on_actionClear_All_triggered();

  void on_stroke_color_clicked();

  void on_fill_color_clicked();

  void on_scale();

  void on_translate();

  void on_rotate_cw();

  void on_rotate_ccw();

  void on_add_image();

  void on_save_action();

  void on_load_action();

  void on_stroke_width_changed(int value);

  void on_rect_tool(bool checked);

  void on_line_tool(bool checked);

  void on_ellipse_tool(bool checked);

  void on_polyline_tool(bool checked);

  void on_selection_tool(bool checked);

private:
  Ui::xPaintWindow *ui;
  PaintWidget * _paintWidget;

  Serializer   * _serializer;
  Deserializer * _deserializer;
  Drawable   * _selectedDrawable;

  void SetUpEditting(bool isEdditing);
  void OnColorUpdate();
};
