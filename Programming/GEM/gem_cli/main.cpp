
#include "ConsolePainter.hpp"
#include <iostream>

using namespace std;
using namespace painter;

int main()
{
  PointF p1(1,2);
  PointF p2(3,4);

  LineF l(p1, p2);
  RectF r(p1, p2);
  EllipseF e(p1, 2, 3);

  ConsolePainter painter;

  painter.drawPoint(p1);
  painter.drawLine(l);
  painter.drawRect(r);
  painter.drawEllipse(e);

  return 0;
}

