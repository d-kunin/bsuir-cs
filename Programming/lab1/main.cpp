#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

/* Объявим следующие классы: 
	Matrix <- Vector <- Point
*/

// Объявления
template <size_t N, size_t M, typename T>
class Matrix
{
public:

	Matrix();
	virtual ~Matrix();

	size_t Rows() const;
	size_t Columns() const;
	// Доступ к элементам
	T & operator()(size_t i, size_t j);
	T const & operator()(size_t i, size_t j) const;
	// Базовые операции
	Matrix<N, M, T> operator +(Matrix<N, M, T> const & other) const;
	Matrix<N, M, T> operator -(Matrix<N, M, T> const & other) const;
	Matrix<N, M, T> operator -() const;

	// Необходимо реализовать глубокое копирование
	Matrix(Matrix<N, M, T> const & source);
	Matrix<N, M, T> const & operator =(Matrix<N, M, T> const & source);


protected: 
	T ** _data;
};

template <size_t M, typename T>
class Vector : public Matrix<1, M, T>
{
public:
	// Скалярное произведение
	T operator * (Vector<M, T> const & v) const;
	T & operator [](size_t index); 
};


template <typename T>
class Point2D : public Vector<2, T>
{
public:
	Point2D(T x, T y);

	T & x();
	T & y();
};

// Реализация методов классов
template <size_t N, size_t M, typename T> Matrix<N, M, T>::Matrix()
{
	_data = new T*[N];

	for (size_t i = 0; i < N; ++i)
		_data[i] = new T[M];

	cout << "Created matrix" << N << "x" << M << endl;

	// Заполним нулями
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < M; ++j)
			_data[i][j] = 0;
}

template <size_t N, size_t M, typename T> Matrix<N, M, T>::Matrix(Matrix<N, M, T> const & source)
{
	_data = new T*[N];

	for (size_t i = 0; i < N; ++i)
		_data[i] = new T[M];

	// Заполним из источника
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < M; ++j)
			_data[i][j] = source._data[i][j];
}

template <size_t N, size_t M, typename T> Matrix<N, M, T> const & Matrix<N, M, T>::operator=(Matrix<N, M, T> const & source)
{
	// Заполним из источника
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < M; ++j)
			_data[i][j] = source._data[i][j];

	return *this;
}

template <size_t N, size_t M, typename T> Matrix<N, M, T>::~Matrix()
{
	for (size_t i = 0; i < N; ++i)
		delete[] _data[i];

	delete[] _data;

	cout << "Deleted matrix" << N << "x" << M << endl;
}

template <size_t N, size_t M, typename T> T& Matrix<N, M, T>::operator()(size_t i, size_t j)
{
	// todo: add range check
	return _data[i][j];
}

template <size_t N, size_t M, typename T> T const & Matrix<N, M, T>::operator()(size_t i, size_t j) const
{
	// todo: add range check
	return _data[i][j];
}


template <size_t N, size_t M, typename T> Matrix<N, M, T> Matrix<N, M, T>::operator-() const
{
	Matrix<N,M,T> res(*this);

	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < M; ++j)
			res._data[i][j] *= -1;

	return res;
 }

template <size_t N, size_t M, typename T> Matrix<N, M, T> Matrix<N, M, T>::operator+(Matrix<N, M, T> const & other) const
{
	Matrix<N,M,T> res(*this);

	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < M; ++j)
			res._data[i][j] += other._data[i][j];

	return res;
}

template <size_t N, size_t M, typename T> Matrix<N, M, T> Matrix<N, M, T>::operator-(Matrix<N, M, T> const & other) const
{
	return *this + (-other);
}

template <size_t N, size_t M, typename T> size_t Matrix<N, M, T>::Rows() const { return N; }
template <size_t N, size_t M, typename T> size_t Matrix<N, M, T>::Columns() const { return M; }


// Vector
template <size_t M, typename T> T & Vector<M, T>::operator[](size_t index)
{
	return this->_data[0][index];
}

template <size_t M, typename T> T Vector<M, T>::operator*(Vector<M, T> const & other) const
{
	T prod = 0;

	for (size_t i = 0; i < M; ++i)
		prod += this->_data[0][i] * other._data[0][i];

	return prod;
}


// Point
template <typename T> Point2D<T>::Point2D(T x, T y) 
{
	this->_data[0][0] = x;
	this->_data[0][1] = y;
}
template <typename T> T & Point2D<T>::x() { return this->_data[0][0]; }
template <typename T> T & Point2D<T>::y() { return this->_data[0][1]; }



// Вспомогательные функции
template <size_t N, size_t M, typename T> void matrix_print(Matrix<N, M, T> const & m)
{
	cout << ">>>===" << endl;
	for (size_t i = 0; i < m.Rows(); ++i)
	{

		for (size_t j = 0; j < m.Columns(); ++j)
			cout << std::setw(4) << m(i,j);

		cout << endl;
	}
	cout << "<<<===" << endl;
}

int main()
{
	// Матрицы

	Matrix<4,3, int> m;
	Matrix<4,3, int> m2;

	m2 = m;

	// Выведем содержимое на консоль
	matrix_print(m);

	m(3,2) = 32;
	m(3,1) = 31;
	m(2,1) = 21;

	// Проверка операторов
	matrix_print(m + m);
	matrix_print(m - m);
	matrix_print(-m);

	//  Код ниже не скомпилируется, так как _data - protected-член класса
	//m._data[1][1];

    // Проверка опертора копирования: m2 должна быть нулевой
	matrix_print(m2);

	// Вектора
	Vector<3, double> v1;
	Vector<3, double> v2;

	for (size_t i = 0; i < 3; ++i)
	{
		v1[i] = i;
		v2[2 - i] = i;
	}
	matrix_print(v1);
	matrix_print(v2);
	matrix_print(v1 + v2);
	matrix_print(v1 - v2);
	matrix_print(v1 - v1);
	cout << v1*v2 << endl;

	// Точки
	Point2D<double> p1(0,1);
	Point2D<double> p2(0,1);

	matrix_print(p1 + p2);
	matrix_print(p1 - p2);
	p1.x() = 111;
	p1.y() = 222;
	cout << p1.x() << p1.y() << endl;
}