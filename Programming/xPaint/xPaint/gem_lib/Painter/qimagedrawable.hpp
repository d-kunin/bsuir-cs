#pragma once

#include "Painter.hpp"
#include "Drawable.hpp"

#include <QImage>

namespace painter
{

class ImageDrawable : public Drawable
{
public:
  ImageDrawable();
  ImageDrawable(QString const &);

  void  Draw(Painter * painter) override;
  RectF BoundingRect() const override;
  void Transform(TransformF const & transform) override;

  QImage const & Image() const { return _image; }

private:
  QImage _image;
  RectF  _bounds;
};

}


