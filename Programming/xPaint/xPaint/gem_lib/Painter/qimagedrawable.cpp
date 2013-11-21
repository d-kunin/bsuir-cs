#include "qimagedrawable.hpp"

#include "../../QxPainter.hpp"

namespace painter {


ImageDrawable::ImageDrawable()
  : _image("/Users/markX/temp/lena_full_files/len_full.jpg")
{
  _bounds = RectF(0, 0, _image.width(), _image.height());
}


void ImageDrawable::Draw(Painter * painter)
{
  QxPainter * qpainter = dynamic_cast<QxPainter*>(painter);
  if (qpainter)
  {
    qpainter->DrawImageDrawable(*this);
  }
}


RectF ImageDrawable::BoundingRect() const
{
  return _bounds;
}


}

