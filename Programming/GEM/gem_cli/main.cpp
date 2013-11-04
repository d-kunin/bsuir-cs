
#include "ConsolePainter.hpp"
#include "../gem_lib/Painter/DrawableGeometry.hpp"
#include "../gem_lib/Painter/Scene.hpp"
#include "../gem_lib/Geometry/Utils.hpp"
#include "../gem_lib/Geometry/Matrix.hpp"
#include "../gem_lib/Geometry/Transform.hpp"

#include <iostream>

using namespace std;
using namespace painter;


struct PrintFunctor : public Functor<float>
{
  void Apply(float & argument) override
  {
    cout << " " << argument;
  }
};

void matrixTest(void)
{
  PrintFunctor pf;

  auto m1 = Matrix<2,2,float>::Identity();
  m1(0,0) = 1; m1(0,1) = -1;
  m1(1,0) = 0; m1(1,1) = 1;

  auto m2 = Matrix<2,2,float>::Identity();
  m2(0,0) = 1; m2(0,1) = 1;
  m2(1,0) = 0; m2(1,1) = 1;

  auto c = m1*m2;
  c.ForEach(pf);
  cout << endl;

  auto m3 = Matrix<3,3,float>::Identity();
  m3(0,0) = 1; m3(0,1) = 2; m3(0,2) = 3;
  m3(1,0) = 4; m3(1,1) = 5; m3(1,2) = 6;
  m3(2,0) = 7; m3(2,1) = 8; m3(2,2) = 9;


  auto m4 = Matrix<3,3,float>::Identity();
  m4(0,0) = 1; m4(0,1) = 1; m4(0,2) = 1;
  m4(1,0) = 1; m4(1,1) = 1; m4(1,2) = 1;
  m4(2,0) = 1; m4(2,1) = 1; m4(2,2) = 1;

  auto c2 = m3*m4;
  c2.ForEach(pf);
  cout << endl;

  Matrix<3,2,float> m5;
  m5(0,0) = 1; m5(0,1) = 2;
  m5(1,0) = 3; m5(1,1) = 4;
  m5(2,0) = 5; m5(2,1) = 6;

   Matrix<2,3, float> m6;
  m6(0,0) = 1; m6(0,1) = 1; m6(0,2) = 1;
  m6(1,0) = 0; m6(1,1) = 1; m6(1,2) = -1;

  auto c3 = m5*m6;
  c3.ForEach(pf);
  cout << endl;
}

void painterTest(void)
{
  PointF p1(1,2);
  PointF p2(3,4);
  LineF l(p1, p2);
  RectF r(p1, p2);
  EllipseF e(p1, 2, 3);

  ConsolePainter * painter = new ConsolePainter();
  auto scale = Transform<float>::Scale(2, 1);

  Scene * innerScene = new Scene();
  innerScene->Drawables().push_back(new PointDrawable(p1));
  innerScene->Drawables().push_back(new LineDrawable(l));
  innerScene->Drawables().push_back(new RectDrawable(r));
  innerScene->Drawables().push_back(new EllipseDrawable(e));

  Scene * outterScene = new Scene();
  outterScene->Drawables().push_back(innerScene);
  outterScene->Drawables().push_back(new PointDrawable(p2));
  outterScene->Drawables().push_back(innerScene);

  outterScene->Draw(painter);
}

void transformTest()
{
  PointF px[] = {
    PointF(1,1),
    PointF(1,0),
    PointF(0,1),
    PointF(0,0),
  };

  Transform<float> tx[] = {
    Transform<float>::Scale(2,3),
    Transform<float>::RotateCW(acos(0)),
    Transform<float>::Translate(1,-1)
  };

  for (PointF & p : px)
  {
    cout << "initial: " << p << endl;
    for (auto & t : tx)
      cout << t*p << endl;
  }
}

int main()
{
  painterTest();
  matrixTest();
  transformTest();

  return 0;
}

