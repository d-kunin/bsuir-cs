#pragma once

#include "../../io/Serializable.hpp"

#include "../Commons.hpp"

namespace painter
{
struct Color: public Serializable
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

  Color(int color);

  void WriteTo(Serializer *) const override;

  string AsString() const;
  static Color FromString(string const &);
};
}
