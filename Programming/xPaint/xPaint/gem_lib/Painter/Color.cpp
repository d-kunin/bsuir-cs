#include "Color.hpp"
#include "../../io/Serializer.hpp"

#include <sstream>
#include <iomanip>

namespace painter
{

Color::Color(int color)
{
  a = (0xFF000000 & color) >> 24;
  r = (0x00FF0000 & color) >> 16;
  g = (0x0000FF00 & color) >> 8;
  b = (0x000000FF & color);
}

void Color::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

string Color::AsString() const
{
  std::ostringstream ss;
  int argb[] = { a, r, g, b};
  for (int component : argb)
  {
    ss << std::setfill('0')
       << std::setw(2)
       << std::hex
       << component;
  }
  return ss.str();
}

Color Color::FromString(string const & str)
{
  int value = std::stoi(str, 0, 16);
  return Color(value);
}

}
