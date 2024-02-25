#include "stdafx.h"
#include "RayLine.h"

#include "Line.h"
#include "../Constantes.h"

// Public methods

RayLine::RayLine(const Point& a, const Point& b) : SegmentLine(a, b)
{
}

RayLine::RayLine(const RayLine& ray) : SegmentLine(ray)
{
}

RayLine::~RayLine()
{
}

bool RayLine::incorrectSegmentIntersection(SegmentLine& segment)
{
	return false;
}

RayLine & RayLine::operator=(const RayLine & rayline)
{
	if (this != &rayline)
	{
		SegmentLine::operator=(rayline);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const RayLine& ray)
{
	os << "Point A: " << ray._orig << ", Point B: " << ray._dest << "\n";

	return os;
}

bool RayLine::intersects(Line& line, Vect2d& intersection)
{
	// Comprueba si la recta line intersecciona con el rayo actual
	// Si intersecciona, devuelve el punto de intersección en intersection

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = line.getA();
	Vect2d d = line.getB();

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	double n = ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (abs(n) < EPSILON)
	{
		return false;
	}

	double s = ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (s < 0)
	{
		return false;
	}

	intersection = getPoint(s);
	return true;
}

bool RayLine::intersects(RayLine& rayline, Vect2d& intersection)
{
	// Comprueba si la recta rayline intersecciona con el rayo actual
	// Si intersecciona, devuelve el punto de intersección en intersection

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = rayline.getA();
	Vect2d d = rayline.getB();

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	double n = ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (abs(n) < EPSILON)
	{
		return false;
	}

	double s = ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));
	double t = ((AB.getX() * AC.getY()) - (AC.getX() * AB.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (s < 0 || t < 0)
	{
		return false;
	}

	intersection = getPoint(s);
	return true;
}

bool RayLine::intersects(SegmentLine& segment, Vect2d& intersection)
{
	// Comprueba si el segmento intersecciona con el rayo actual
	// y si lo hace, calcula el punto de intersección

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = segment.getA();
	Vect2d d = segment.getB();

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	double n = ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (abs(n) < EPSILON)
	{
		return false;
	}

	double s = ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));
	double t = ((AB.getX() * AC.getY()) - (AC.getX() * AB.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (s < 0 || t < 0 || t > 1)
	{
		return false;
	}

	intersection = getPoint(s);
	return true;
}

float RayLine::distanceToPoint(const Vect2d& point)
{
	// Calcula la distancia de un punto a una recta

	Vect2d P = _orig;
	Vect2d Q = _dest;

	Vect2d d = Q - P;
	Vect2d A = point;

	double t0 = (d * (A - P)) / (d * d);

	if (t0 <= 0)
	{
		return (A - P).module();
	}
	else
	{
		return (A - (P + d.scalarMult(t0))).module();
	}
}