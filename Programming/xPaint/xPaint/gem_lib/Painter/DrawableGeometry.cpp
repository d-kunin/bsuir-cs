#include "DrawableGeometry.hpp"
#include "../../io/Serializer.hpp"

namespace painter
{

void LineDrawable::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

void RectDrawable::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

void EllipseDrawable::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

void PolylineDrawable::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

}
