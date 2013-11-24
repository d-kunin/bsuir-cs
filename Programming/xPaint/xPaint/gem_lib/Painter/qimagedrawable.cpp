#include "qimagedrawable.hpp"

#include "../../QxPainter.hpp"

namespace painter {


ImageDrawable::ImageDrawable()
{
  _bounds = RectF(0, 0, _image.width(), _image.height());
}

ImageDrawable::ImageDrawable(QString const & path)
  : _image(path)
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

void ImageDrawable::Transform(TransformF const & transform)
{
  _bounds = transform*_bounds;
}

}

