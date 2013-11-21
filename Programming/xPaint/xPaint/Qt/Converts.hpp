#pragma once

#include <QColor>
#include <QRectF>
#include <QPointF>

#include "../gem_lib/Painter/Color.hpp"
#include "../gem_lib/Painter/Painter.hpp"

using painter::Color;
using painter::RectF;
using painter::PointF;

class Convert
{
public:
  static QColor FromXColor(Color const & color);
  static Color  FromQColor(QColor const & qcolor);

  static QPointF FromXPoint(PointF const & xpoint);
  static PointF  FromQPointF(QPointF const & qpoint);

  static QRectF FromRectF(RectF const & rectf);
  static RectF  FromQRectF(QRectF const & qrectf);

private:
  Convert();
};
