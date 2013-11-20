#pragma once

namespace painter
{
struct Color
{
  unsigned char a;
  unsigned char r;
  unsigned char g;
  unsigned char b;

  Color()
    : a(255), r(0), g(0), b(0)
  {}

  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
  {
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
  }

};
}
