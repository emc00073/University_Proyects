#include "stdafx.h"
#include "BasicGeometry.h"
#include "Line3d.h"
#include "../Constantes.h"

Line3d::Line3d()
{
}

Line3d::Line3d(Vect3d & orig, Vect3d & dest)
	: Edge3d(orig, dest)
{
}

Line3d::Line3d(const Line3d & line)
	: Edge3d(line)
{
}

Line3d::~Line3d()
{
}


double Line3d::distance(Line3d & line)
{
	// Distancia entre dos rectas en 3D

	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d orig1 = line._orig;
	Vect3d dest1 = line._dest;

	Vect3d u = dest - orig;
	Vect3d v = dest1 - orig1;
	Vect3d w = orig1 - orig;

	// Calcula el volumen del paralelepípedo formado por los vectores u, v y w
	Vect3d xProduct = v.xProduct(w);
	double vol = u.dot(xProduct);

	// Calcula el area del paralelogramo formado por los vectores u y v
	double area = u.xProduct(v).module();

	return abs(vol / area);
}

Line3d Line3d::normalLine(Vect3d & point)
{
    // Calcula y devuelve la Línea 3D normal a this que pase por el punto point
	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d point1 = point;

	Vect3d d = dest - orig;
	Vect3d p_Orig = point1 - orig;

	double t = d.dot(p_Orig) / d.dot(d);
	Vect3d q = getPoint(t);

	return Line3d(point1, q);
}

Line3d::classifyLines Line3d::classify(Line3d& line)
{
	// Clasifica la relación entre dos líneas en 3D
	// enum classifyLines { NON_INTERSECT, PARALLEL, INTERSECT, THESAME };
	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d orig1 = line._orig;
	Vect3d dest1 = line._dest;

	Vect3d u = dest - orig;
	Vect3d v = dest1 - orig1;

	// Comprobar manualmente si son paralelas
	if (u.xProduct(v).module() < EPSILON)
	{
		// Comprobar si son la misma línea
		if (orig == orig1 && dest == dest1)
		{
			return THESAME;
		}
		else
		{
			return PARALLEL;
		}
	}
	else
	{
		// Comprobar si se intersectan
		if (distance(line) < EPSILON)
		{
			return INTERSECT;
		}
		else
		{
			return NON_INTERSECT;
		}
	}
}

bool Line3d::isParallel(Line3d& line)
{
	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d orig1 = line._orig;
	Vect3d dest1 = line._dest;

	Vect3d u = dest - orig;
	Vect3d v = dest1 - orig1;

	// Comprobar manualmente si son paralelas
	if (u.xProduct(v).module() < EPSILON && !(orig == orig1 && dest == dest1))
	{
		return true;
	}
	return false;
}

bool Line3d::isPerpendicular(Line3d& line)
{
	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d orig1 = line._orig;
	Vect3d dest1 = line._dest;

	Vect3d u = dest - orig;
	Vect3d v = dest1 - orig1;

	// Comprobar manualmente si son perpendiculares
	if (u.dot(v) < EPSILON)
	{
		return true;
	}
	return false;
}

double Line3d::distance(Vect3d& p){
    
	// Calcula y devuelve la distancia entre el punto p y la línea this
	Vect3d orig = _orig;
	Vect3d dest = _dest;
	Vect3d point1 = p;

	Vect3d d = dest - orig;
	Vect3d p_Orig = point1 - orig;

	double t = d.dot(p_Orig) / d.dot(d);
	Vect3d q = getPoint(t);

	return p.distance(q);
}

Line3d & Line3d::operator=(const Line3d & line)
{
	if (this != &line)
	{
		Edge3d::operator=(line);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Line3d& line)
{
	std::cout << "Line -> Origin: " << line._orig << ", Destination: " << line._dest;
	return os;
}

