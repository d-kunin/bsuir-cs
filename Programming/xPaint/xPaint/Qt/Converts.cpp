#include "Converts.hpp"

Convert::Convert()
{}

QColor Convert::FromXColor(Color const & color)
{
  return QColor(color.r,color.g,color.b, color.a);
}

Color Convert::FromQColor(QColor const & color)
{
  return Color(color.red(), color.green(), color.blue(), color.alpha());
}

painter::PointF Convert::FromQPointF(QPointF const & qpoint)
{
  return painter::PointF(qpoint.x(), qpoint.y());
}

QPointF Convert::FromXPoint(PointF const & xpoint)
{
  return QPointF(xpoint._x, xpoint._y);
}

painter::RectF Convert::FromQRectF(QRectF const & qrectf)
{
  return painter::RectF(qrectf.left(), qrectf.top(),
                        qrectf.right(), qrectf.bottom());
}

QRectF Convert::FromRectF(RectF const & rectf)
{
  return QRectF(FromXPoint(rectf._topLeft), FromXPoint(rectf._bottomRight));
}
