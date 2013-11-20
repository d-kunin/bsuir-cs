#pragma once

#include <QColor>

#include "../gem_lib/Painter/Color.hpp"

using painter::Color;

class Convert
{
public:
  static QColor FromXColor(Color const & color);
  static Color FromQColor(QColor const & color);

private:
  Convert();
};
