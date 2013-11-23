#pragma once

#include "Color.hpp"

#include "../../io/Serializable.hpp"

namespace painter
{
class Paint: public Serializable
{
public:

  void WriteTo(Serializer *) const;

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
    : _strokeWidth(5),
      _strokeColor(Color(0, 0, 0, 255)),
      _strokeStyle(SOLID),
      _fillColor(Color(255, 255, 255, 255)),
      _fillStyle(NORMAL)
  {}

  void SetStrokeWidth(float width)         { _strokeWidth = width; }
  void SetStrokeColor(Color const & color) { _strokeColor = color; }
  void SetStrokeStyle(StrokeStyle style)   { _strokeStyle = style; }

  float & GetStrokeWidth() { return _strokeWidth; }
  float   GetStrokeWidth() const { return _strokeWidth; }
  Color & GetStrokeColor() { return _strokeColor; }
  Color const & GetStrokeColor() const { return _strokeColor; }
  StrokeStyle GetStrokeStyle() const { return _strokeStyle; }


  Color & GetFillColor() { return _fillColor; }
  Color const & GetFillColor() const { return _fillColor; }
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
