#include "stdafx.h"
#include "Plane.h"
#include "BasicGeometry.h"
#include "../Constantes.h"


Plane::Plane(Vect3d & p, Vect3d & u, Vect3d & v, bool arePoints)
{
	if (!arePoints)			// Vectors: pi = p + u * lambda + v * mu 
	{			
		_a = p;
		_b = u.add(_a);
		_c = v.add(_a);
	}
	else 
	{						// 3 points in the plane
		_a = p;
		_b = u;
		_c = v;
	}
}

Plane::Plane(const Plane & plane): _a(plane._a), _b(plane._b), _c(plane._c)
{
}

Plane::~Plane()
{
}

bool Plane::coplanar(Vect3d & point)
{  
	Vect3d q = Vect3d();
	if (distance(point, q) < EPSILON)
	{
		return true;
	}
	return false;
}

double Plane::distance(Vect3d & point, Vect3d& q)
{
	Vect3d normal = getNormal();
	float alfa = -(normal.dot(point) + getD()) / normal.dot(normal);

	Vect3d normal_alfa = normal.scalarMul(alfa);
	q = point.add(normal_alfa);

	return normal_alfa.module();
}    

double Plane::getA()
{
	return (BasicGeometry::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
}

double Plane::getB()
{
	return (BasicGeometry::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));	
}

double Plane::getC()
{
	return (BasicGeometry::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
}

Vect3d Plane::getNormal()
{
	return Vect3d(getA(), getB(), getC());
}

bool Plane::intersect(Plane & plane, Line3d & line)
{
    //XXXX
    return true;
}

bool Plane::intersect(Line3d & line, Vect3d & point)
{   
	Vect3d normal = getNormal();
	Vect3d origin = line.getOrigin();
	Vect3d direction = line.getDestination();

	if (normal.dot(direction) < EPSILON) {
		return false;
	}

    float alfa = -(normal.dot(origin) + getD()) / (normal.dot(direction));

	point = line.getPoint(alfa);
	
	return true;
}

bool Plane::intersect(Plane& pa, Plane& pb, Vect3d& pinter)
{
	double DET = BasicGeometry::determinant3x3(getA(), getB(), getC(), pa.getA(), pa.getB(), pa.getC(), pb.getA(), pb.getB(), pb.getC());
	if (abs(DET) < EPSILON)
	{
		return false;
	}

	double DETx = BasicGeometry::determinant3x3(getD(), getB(), getC(), pa.getD(), pa.getB(), pa.getC(), pb.getD(), pb.getB(), pb.getC());
	double DETy = BasicGeometry::determinant3x3(getA(), getD(), getC(), pa.getA(), pa.getD(), pa.getC(), pb.getA(), pb.getD(), pb.getC());
	double DETz = BasicGeometry::determinant3x3(getA(), getB(), getD(), pa.getA(), pa.getB(), pa.getD(), pb.getA(), pb.getB(), pb.getD());

	pinter = Vect3d(-DETx / DET, -DETy / DET, -DETz / DET);

	return true;
}

Plane & Plane::operator=(const Plane & plane)
{
	if (this != &plane)
	{
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

Vect3d Plane::reflectedPoint(Vect3d& v)
{
	Vect3d normal = getNormal();
	float alfa = -2.0f * (normal.dot(v) + getD()) / normal.dot(normal);

	Vect3d normal_alfa = normal.scalarMul(alfa);

	return v.add(normal_alfa);
}

Vect3d Plane::reflectedDirection(Vect3d& d)
{
	Vect3d n_normal = getNormal().normalize();
	float d_dot_n = d.dot(n_normal);

	return d - n_normal.scalarMul(2.0f * d_dot_n);
}

std::ostream& operator<<(std::ostream& os, const Plane& plane)
{
	os << "Plane -> a: " << plane._a << ", b: " << plane._b << ", c: " << plane._c;
	return os;
}