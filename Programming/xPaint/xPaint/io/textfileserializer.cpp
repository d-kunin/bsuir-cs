#include "textfileserializer.hpp"

using std::endl;
using std::ios;

static const string  SP = " ";
static const string  SCENE = "SCN";
static const string  PAINT = "PNT";
static const string  LINE = "LINE";
static const string  ELLI = "ELLI";
static const string  POLY = "POLY";
static const string  RECT = "RECT";

TextFileSerializer::TextFileSerializer(string const & filename)
  : _fileName(filename)
{
  _file.open(_fileName, ios::out | ios::trunc);
}

void TextFileSerializer::Write(painter::RectDrawable const * r)
{
  _file << RECT << SP
        << r->_geometry._topLeft._x << SP
        << r->_geometry._topLeft._y << SP
        << r->_geometry._bottomRight._x << SP
        << r->_geometry._bottomRight._y << SP;
  Write(&r->GetPaint());
  _file << endl;
}

void TextFileSerializer::Write(painter::EllipseDrawable const * e)
{
  _file << ELLI << SP
        << e->_geometry._center._x << SP
        << e->_geometry._center._y << SP
        << e->_geometry.radiusX() << SP
        << e->_geometry.radiusY() << SP;
  Write(&e->GetPaint());
  _file << endl;
}

void TextFileSerializer::Write(painter::LineDrawable const * l)
{
  _file << LINE << SP
        << l->_geometry._start._x << SP
        << l->_geometry._start._y << SP
        << l->_geometry._end._x << SP
        << l->_geometry._end._y << SP;
  Write(&l->GetPaint());
  _file << endl;
}

void TextFileSerializer::Write(painter::PolylineDrawable const * p)
{
  _file << POLY << SP
        << p->_geometry._points.size() << SP;

  for (painter::PointF const & point: p->_geometry._points)
  {
    _file << point._x << SP
          << point._y << SP;
  }
  Write(&p->GetPaint());
  _file << endl;
}

void TextFileSerializer::Write(painter::Scene const * scene)
{
  _file << SCENE << SP
        << scene->Drawables().size() << endl;

  for (painter::Drawable const * drawable : scene->Drawables())
  {
    Serializable const * serializable =
        dynamic_cast<Serializable const *>(drawable);

    if (serializable)
      serializable->WriteTo(this);
  }
}

void TextFileSerializer::Write(const painter::Paint * paint)
{
  _file << PAINT << SP;

  Write(&paint->GetFillColor());
  _file << SP << paint->GetStrokeWidth();
  Write(&paint->GetStrokeColor());
}

void TextFileSerializer::Write(const painter::Color * color)
{
  _file << SP << color->AsString();
}
