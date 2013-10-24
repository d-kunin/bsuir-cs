#include "ConsolePainter.hpp"

#include "../gem_lib/Geometry/Utils.hpp"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

void ConsolePainter::DrawPoint(PointF const & point) {
  cout << ToStr(point) << endl;
}

void ConsolePainter::DrawLine(LineF const & line) {
  cout << ToStr(line) << endl;
}

void ConsolePainter::DrawRect(RectF const & rect) {
  cout << ToStr(rect) << endl;
}

void ConsolePainter::DrawEllipse(EllipseF const & ellipse) {
  cout << ToStr(ellipse) << endl;
}
