#pragma once

#include "Painter.hpp"
#include "Drawable.hpp"
#include "../../io/Serializable.hpp"

#include <QImage>

namespace painter
{

class ImageDrawable : public Drawable,
                      public Serializable
{
public:
  ImageDrawable();
  ImageDrawable(string const &);
  ImageDrawable(string const &, RectF const &);

  void  Draw(Painter * painter) override;
  RectF BoundingRect() const override;
  void Transform(TransformF const & transform) override;

  QImage const & Image() const { return _image; }
  string FileName() const { return _fileName; }

  void WriteTo(Serializer *) const;

private:
  QImage _image;
  string _fileName;
  RectF  _bounds;
};

}


