#include "Converts.hpp"

Convert::Convert()
{}

QColor Convert::FromXColor(Color const & color)
{
  return QColor(color.r,color.g,color.b, color.a);
}

Color Convert::FromQColor(QColor const & color)
{
  return Color(color.red(), color.green(), color.blue(), color.alpha());
}
