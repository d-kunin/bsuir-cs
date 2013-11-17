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
    : a(0), r(0), g(0), b(0)
  {}
};
}
