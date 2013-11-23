#include "textfileserializer.hpp"

#include <sstream>
#include <iostream>

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
{}

painter::Scene * TextFileSerializer::ReadScene()
{
  if (!_file.is_open())
    _file.open(_fileName);

  painter::Scene * scene = new painter::Scene;
  string line;
  while (std::getline(_file, line))
  {
    painter::Drawable * drawable = NULL;
    string type;
    std::istringstream iss(line);
    iss >> type;

    if (RECT == type)
    {
      float x0, y0, x1, y1;
      iss >> x0 >> y0 >> x1 >> y1;
      painter::RectF r(x0, y0, x1, y1);
      drawable = new painter::RectDrawable(r);

      iss >> type;
      if (PAINT == type)
        drawable->SetPaint(ParsePaint(iss));
    }
    else if (LINE == type)
    {
      float x0, y0, x1, y1;
      iss >> x0 >> y0 >> x1 >> y1;
      painter::LineF l(x0, y0, x1, y1);
      drawable = new painter::LineDrawable(l);

      iss >> type;
      if (PAINT == type)
        drawable->SetPaint(ParsePaint(iss));
    }
    else if (ELLI == type)
    {
      float x0, y0, rx, ry;
      iss >> x0 >> y0 >> rx >> ry;
      painter::EllipseF e(x0, y0, rx, ry);
      drawable = new painter::EllipseDrawable(e);

      iss >> type;
      if (PAINT == type)
        drawable->SetPaint(ParsePaint(iss));
    }
    else if (POLY == type)
    {
      float x, y;
      size_t count = 0;
      iss >> count;
      painter::PolylineF poly;
      for (size_t index = 0; index < count; ++index)
      {
        iss >> x >> y;
        poly.Add(x, y);
      }
      drawable = new painter::PolylineDrawable(poly);

      iss >> type;
      if (PAINT == type)
        drawable->SetPaint(ParsePaint(iss));
    }

    if (drawable)
      scene->Add(drawable);
  }

  _file.close();

  return scene;
}

void TextFileSerializer::Write(painter::Scene const * scene)
{
  if (!_file.is_open())
    _file.open(_fileName, ios::trunc | ios::out);

  _file << SCENE << SP
        << scene->Drawables().size() << endl;

  for (painter::Drawable const * drawable : scene->Drawables())
  {
    Serializable const * serializable =
        dynamic_cast<Serializable const *>(drawable);

    if (serializable)
      serializable->WriteTo(this);
  }

  _file.close();
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

painter::Paint TextFileSerializer::ParsePaint(istream & in)
{
  painter::Paint p;
  string tmp;
  in >> tmp;
  p.SetFillColor(painter::Color::FromString(tmp));
  in >> p.GetStrokeWidth();
  in >> tmp;
  p.SetStrokeColor(painter::Color::FromString(tmp));
  return p;
}
