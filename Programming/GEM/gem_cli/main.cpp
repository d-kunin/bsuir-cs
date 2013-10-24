
#include "ConsolePainter.hpp"
#include "../gem_lib/Painter/DrawableGeometry.hpp"
#include "../gem_lib/Painter/Scene.hpp"

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

  Scene * innerScene = new Scene();
  innerScene->Drawables().push_back(new PointDrawable(p1));
  innerScene->Drawables().push_back(new LineDrawable(l));
  innerScene->Drawables().push_back(new RectDrawable(r));
  innerScene->Drawables().push_back(new EllipseDrawable(e));

  Scene * outterScene = new Scene();
  outterScene->Drawables().push_back(innerScene);
  outterScene->Drawables().push_back(new PointDrawable(p2));
  outterScene->Drawables().push_back(innerScene);

  outterScene->Draw(&painter);

  return 0;
}

