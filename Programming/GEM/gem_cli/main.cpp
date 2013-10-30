
#include "ConsolePainter.hpp"
#include "../gem_lib/Painter/DrawableGeometry.hpp"
#include "../gem_lib/Painter/Scene.hpp"
#include "../gem_lib/Geometry/Utils.hpp"
#include "../gem_lib/Geometry/Matrix.hpp"

#include <iostream>

using namespace std;
using namespace painter;


class PrintFunctor : public Functor<float>
{
public:
  void Apply(float & argument) override
  {
    cout << " " << argument;
  }
};

int main()
{
  Matrix<2,2, float> mat = Matrix<2,2, float>::Identity();
  PrintFunctor pf;


  PointF p1(1,2);
  PointF p2(3,4);

  LineF l(p1, p2);
  RectF r(p1, p2);
  EllipseF e(p1, 2, 3);

  ConsolePainter * painter = new ConsolePainter();

//  Scene * innerScene = new Scene();
//  innerScene->Drawables().push_back(new PointDrawable(p1));
//  innerScene->Drawables().push_back(new LineDrawable(l));
//  innerScene->Drawables().push_back(new RectDrawable(r));
//  innerScene->Drawables().push_back(new EllipseDrawable(e));

//  Scene * outterScene = new Scene();
//  outterScene->Drawables().push_back(innerScene);
//  outterScene->Drawables().push_back(new PointDrawable(p2));
//  outterScene->Drawables().push_back(innerScene);

//  outterScene->Draw(painter);

//  cout << p1;

  mat.ForEach(pf);

  mat(1,1) = 4;
  mat = mat*4;

  mat.ForEach(pf);

  return 0;
}

