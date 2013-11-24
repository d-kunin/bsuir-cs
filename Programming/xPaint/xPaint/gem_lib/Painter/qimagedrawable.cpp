#include "qimagedrawable.hpp"

#include "../../QxPainter.hpp"
#include "../../io/Serializer.hpp"

namespace painter {

ImageDrawable::ImageDrawable()
{
  _bounds = RectF(0, 0, _image.width(), _image.height());
}

ImageDrawable::ImageDrawable(string const & path)
  : _image(path.c_str()), _fileName(path)
{
  _bounds = RectF(0, 0, _image.width(), _image.height());
}

ImageDrawable::ImageDrawable(string const & path, RectF const & rect)
  : _image(path.c_str()), _fileName(path), _bounds(rect)
{}

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

void ImageDrawable::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

}

