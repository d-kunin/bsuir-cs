#pragma once

#include <iostream>

template<typename T>
class Functor
{
public:
  virtual ~Functor() {}
  virtual void Apply(T & argument) = 0;
};

template <size_t N, size_t M, typename T>
class Matrix
{
public:
  virtual ~Matrix();

  static Matrix<N,N,T> Identity();
  static Matrix<N,N,T> Diagonal(T value);

  size_t Rows() const { return N; }
  size_t Columns() const { return M; }

  T & operator()(size_t i, size_t j);
  T const & operator()(size_t i, size_t j) const;

  Matrix<N, M, T> operator +(Matrix<N, M, T> const & other) const;
  Matrix<N, M, T> operator -(Matrix<N, M, T> const & other) const;
  Matrix<N, M, T> operator -() const;

  Matrix(Matrix<N, M, T> const & source);
  Matrix<N, M, T> const & operator =(Matrix<N, M, T> const & source);

  Matrix<N, M, T> operator * (T scalar) const;

  void ForEach(Functor<T> & f);

protected:
  T ** _data;
  Matrix();
};

template <size_t N, size_t M, typename T>
Matrix<N, N, T> Matrix<N, M, T>::Diagonal(T value)
{
  Matrix<N,N,T> mat;
  for (size_t i = 0; i < N; ++i)
    mat(i,i) = value;

  return mat;
}

template <size_t N, size_t M, typename T>
Matrix<N, N, T> Matrix<N, M, T>::Identity()
{
  return Diagonal(1);
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix()
{
  _data = new T*[N];

  for (size_t i = 0; i < N; ++i)
    _data[i] = new T[M];

  cout << "Created matrix" << N << "x" << M << endl;

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      _data[i][j] = 0;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(Matrix<N, M, T> const & source)
{
  _data = new T*[N];

  for (size_t i = 0; i < N; ++i)
    _data[i] = new T[M];

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      _data[i][j] = source._data[i][j];
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> const & Matrix<N, M, T>::operator=(Matrix<N, M, T> const & source)
{
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      _data[i][j] = source._data[i][j];

  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::~Matrix()
{
  for (size_t i = 0; i < N; ++i)
    delete[] _data[i];

  delete[] _data;

  cout << "Deleted matrix" << N << "x" << M << endl;
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t i, size_t j)
{
  // todo: add range check
  return _data[i][j];
}

template <size_t N, size_t M, typename T>
T const & Matrix<N, M, T>::operator()(size_t i, size_t j) const
{
  // todo: add range check
  return _data[i][j];
}


template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-() const
{
  Matrix<N,M,T> res(*this);

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      res._data[i][j] *= -1;

  return res;
 }

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(Matrix<N, M, T> const & other) const
{
  Matrix<N,M,T> res(*this);

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      res._data[i][j] += other._data[i][j];

  return res;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(T scalar) const
{
  Matrix<N,M,T> res(*this);

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      res._data[i][j] *= scalar;

  return res;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(Matrix<N, M, T> const & other) const
{
  return *this + (-other);
}

template <size_t N, size_t M, typename T>
void Matrix<N, M, T>::ForEach(Functor<T> & f)
{
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      f.Apply(operator()(i,j));
}
