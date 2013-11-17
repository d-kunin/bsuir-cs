#pragma once

#include "Color.hpp"

namespace painter
{
class Paint
{
public:

  enum FillStyle
  {
    NO_FILL,
    NORMAL
  };

  enum StrokeStyle
  {
    NO_STROKE,
    SOLID,
    DASH
  };

public:
  Paint()
    : _strokeWidth(5), _strokeStyle(SOLID), _fillStyle(NORMAL)
  {}

  void SetStrokeWidth(float width)         { _strokeWidth = width; }
  void SetStrokeColor(Color const & color) { _strokeColor = color; }
  void SetStrokeStyle(StrokeStyle style)   { _strokeStyle = style; }

  float & GetStrokeWidth() { return _strokeWidth; }
  Color & GetStrokeColor() { return _strokeColor; }
  StrokeStyle GetStrokeStyle() const { return _strokeStyle; }


  Color     GetFillColor() const { return _fillColor; }
  FillStyle GetFillStyle() const { return _fillStyle; }

  void SetFillColor(Color const & color) { _fillColor = color; }
  void SetFillStyle(FillStyle style)     { _fillStyle = style; }

private:
  float _strokeWidth;
  Color _strokeColor;
  StrokeStyle _strokeStyle;

  Color _fillColor;
  FillStyle _fillStyle;
};
}
