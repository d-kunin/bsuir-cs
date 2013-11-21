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

  void  Draw(Painter * painter) ;
  RectF BoundingRect() const ;

  QImage const & Image() const { return _image; }

private:
  QImage _image;
  RectF  _bounds;
};

}


