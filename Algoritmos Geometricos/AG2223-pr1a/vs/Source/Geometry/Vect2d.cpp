#include "stdafx.h"
#include "Vect2d.h"

// Public methods

Vect2d::Vect2d(const Point& point) : Point(point)
{
}

Vect2d::Vect2d(const Vect2d& v) : Point(v._x, v._y)
{
}

Vect2d::~Vect2d()
{
}

double Vect2d::dot(Vect2d& b)
{
	// Producto escalar
	return _x * b._x + _y * b._y;
}

Vect2d & Vect2d::operator=(const Vect2d & vector)
{
	Point::operator=(vector);

	return *this;
}

Vect2d Vect2d::operator+(const Vect2d& b)
{
	// Suma de vectores
	return Vect2d(_x + b._x, _y + b._y);
}

Vect2d Vect2d::operator-(const Vect2d& b)
{
	// Resta de vectores
	return Vect2d(_x - b._x, _y - b._y);
}

Vect2d Vect2d::scalarMult(double t)
{
	// Vector por un escalar
	return Vect2d(_x * t, _y * t);
}

float Vect2d::operator*(const Vect2d& b)
{
	// Producto escalar
	return _x * b._x + _y * b._y;
}

double Vect2d::module() {
	// Módulo de un vector
	return sqrt((_x * _x) + (_y * _y));
}