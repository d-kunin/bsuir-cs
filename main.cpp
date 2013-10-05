#include <iostream>
#include <cassert>

#include "xmath/matrix.hpp"
#include "xmath/geometry.hpp"

using namespace std;
using dkmath::Matrix;
using dkmath::Point2d;
using dkmath::Rect;

int main()
{
  typedef Matrix<double>  MatrixD;
  typedef Point2d<double> PointD;
  typedef Rect<double>    RectD;

  {
    // test matrix creation and destroying
    const size_t n = 10;
    MatrixD * matrices[n];

    for (int i = 1; i < n; ++i)
      matrices[i - 1] = new MatrixD( i*i, (n-i)*(n-i));

    for (int i = 0; i < n; ++i)
      delete matrices[i];
  }


  {
    // test point
    PointD p(0,0);
    assert(p.x() == 0);
    assert(p.y() == 0);
    assert(p.boundingRect().isDegenerate());
    assert(p.boundingRect().isValid());

    cout << "Point checks successed." << endl;
  }

  {
    // test rect
    PointD pInside(1,1);
    PointD pOutside(-1,-1);

    RectD r(2, 2, 0, 0);

    assert(r.isValid());
    assert(!r.isDegenerate());

    assert(r.contains(pInside));
    assert(!r.contains(pOutside));

    assert(pInside == r.center());

    cout << "Rect checks successed." << endl;
  }

  return 0;
}

