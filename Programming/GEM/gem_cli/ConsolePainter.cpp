#include "ConsolePainter.hpp"

#include "../gem_lib/Geometry/Utils.hpp"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

void ConsolePainter::drawPoint(PointF const & point) {
  cout << ToStr(point) << endl;
}

void ConsolePainter::drawLine(LineF const & line) {
  cout << ToStr(line) << endl;
}

void ConsolePainter::drawRect(RectF const & rect) {
  cout << ToStr(rect) << endl;
}

void ConsolePainter::drawEllipse(EllipseF const & ellipse) {
  cout << ToStr(ellipse) << endl;
}
