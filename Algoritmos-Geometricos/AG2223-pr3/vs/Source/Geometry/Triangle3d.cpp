#include "stdafx.h"
#include "BasicGeometry.h"
#include "Triangle3d.h"
#include "Edge3d.h"
#include "../Constantes.h"


Triangle3d::Triangle3d()
{
}

Triangle3d::Triangle3d(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz)
{
}

Triangle3d::Triangle3d(const Triangle3d & triangle)
	: _a(triangle._a), _b(triangle._b), _c(triangle._c)
{
}

Triangle3d::Triangle3d(Vect3d & va, Vect3d & vb, Vect3d & vc)
	: _a(va), _b(vb), _c(vc)
{
}

Triangle3d::~Triangle3d()
{
}

double Triangle3d::area()
{
    Vect3d AB = _b - _a;
	Vect3d AC = _c - _a;
	Vect3d cross = AB.xProduct(AC);

	return cross.module() / 2;
}

Triangle3d::PointPosition Triangle3d::classify(Vect3d & point)
{
	Vect3d v = point - _a;
	Vect3d n = normal();
	double len = v.module();

	if (len < EPSILON)
	{
		return COPLANAR;
	}

	v = v.scalarMul(1.0f / len);
	double d = v.dot(n);

	if (d > EPSILON)
	{
		return POSITIVE;
	}
	else if (d < -EPSILON)
	{
		return NEGATIVE;
	}
	else
	{
		return COPLANAR;
	}
}

Vect3d Triangle3d::normal()
{
	Vect3d v1 (_b.sub(_a));
	Vect3d v2 (_c.sub(_a));
	Vect3d n (v1.xProduct(v2));
	double module = n.module();

	return (n.scalarMul(1.0f / module));
}

Triangle3d & Triangle3d::operator=(const Triangle3d & triangle)
{
	_a = triangle._a;
	_b = triangle._b;
	_c = triangle._c;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Triangle3d& triangle)
{
	std::cout << "Triangle 3D -> " << triangle._a << ", " << triangle._b << ", " << triangle._c;
	return os;
}

void Triangle3d::set(Vect3d & va, Vect3d & vb, Vect3d & vc)
{
	_a = va;
	_b = vb;
	_c = vc;
}

bool Triangle3d::ray_tri(Ray3d& ray, Vect3d& p)
{
	constexpr float epsilon = 1.0e-10f;

	Vect3d ray_vector = ray.getDestination() - ray.getOrigin();

	Vect3d edge1 = _b - _a;
	Vect3d edge2 = _c - _a;

	Vect3d ray_cross_e2 = ray_vector.xProduct(edge2);
	float det = edge1.dot(ray_cross_e2);

	if (det > -epsilon && det < epsilon)
		return false;    // This ray is parallel to this triangle.

	float inv_det = 1.0 / det;
	Vect3d s = ray.getOrigin() - _a;
	float u = inv_det * s.dot(ray_cross_e2);

	if (u < 0 || u > 1)
		return false;

	Vect3d s_cross_e1 = s.xProduct(edge1);
	float v = inv_det * ray_vector.dot(s_cross_e1);

	if (v < 0 || u + v > 1)
		return false;

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = inv_det * edge2.dot(s_cross_e1);

	if (t > epsilon) // ray intersection
	{
		Vect3d ray_vector_t = ray_vector.scalarMul(t);
		p = ray.getOrigin().add(ray_vector_t);
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}

