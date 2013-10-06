#pragma once

// for debug prints
#include <iostream>
using std::cout;
using std::endl;

namespace dkmath {

template <typename T>
class Matrix
{
private:
  T ** _data;

  size_t _rows_n;
  size_t _columns_m;

public:
  Matrix(size_t rows_n, size_t columns_m)
    : _rows_n(rows_n), _columns_m(columns_m)
  {
    _data = new T*[_rows_n];

    for (size_t i = 0; i < _rows_n; ++i)
      _data[i] = new T[_columns_m];

    for (size_t i = 0; i < _rows_n; ++i)
      for (size_t j = 0; j < _columns_m; ++j)
        _data[i][j] = 0;

    cout << "Created " << rowsCount() << "x" << columnsCount() << " matrix" << endl;
  }


  ~Matrix()
  {
    for (size_t i = 0; i < _rows_n; ++i)
      delete[] _data[i];
    delete[] _data;

    cout << "Destroyed " << rowsCount() << "x" << columnsCount() << " matrix" << endl;
  }

  int rowsCount()    { return _rows_n; }
  int columnsCount() { return _columns_m; }

  T & operator()(int i, int j)
  {
    return _data[i][j];
  }
};

}
