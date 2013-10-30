#include "ConsolePainter.hpp"

#include "../gem_lib/Geometry/Utils.hpp"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

void ConsolePainter::DrawPoint(PointF const & point)
{
  cout << point << endl;
}

void ConsolePainter::DrawLine(LineF const & line)
{
  cout << line << endl;
}

void ConsolePainter::DrawRect(RectF const & rect)
{
  cout << rect << endl;
}

void ConsolePainter::DrawEllipse(EllipseF const & ellipse)
{
  cout << ellipse << endl;
}

void ConsolePainter::UsePaint(Paint const * paint)
{
  cout << "Using new paint " << paint->GetStrokeWidth() << endl;
}
