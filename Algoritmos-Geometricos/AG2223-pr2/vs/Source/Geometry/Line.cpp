#include "stdafx.h"
#include "Line.h"

#include "RayLine.h"
#include "SegmentLine.h"
#include "../Constantes.h"


Line::Line(const Point & a, const Point & b) : SegmentLine(a, b)
{
}

Line::Line(const Line & s) : SegmentLine(s)
{
}

Line::~Line()
{
}

double Line::distancePointLine(const Vect2d& v)
{
	// Calcula la distancia de un punto a una recta

	Vect2d P = _orig;
	Vect2d Q = _dest;

	Vect2d d = Q - P;
	Vect2d A = v;

	double t0 = (d * (A - P)) / (d * d);

	return (A - (P + d.scalarMult(t0))).module();
}

bool Line::intersects(Line& line, Vect2d& intersection)
{
	// Comprueba si la recta line intersecciona con la recta actual
	// Si intersecciona, devuelve el punto de intersección en intersection

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = line._orig;
	Vect2d d = line._dest;

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	double n = ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (abs(n) < EPSILON)
	{
		return false;
	}

	double s = ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	intersection = getPoint(s);
	return true;
}

bool Line::intersects(RayLine& rayline, Vect2d& intersection)
{
	// Comprueba si el rayo rayline intersecciona con la recta actual
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
	
	if (t < 0)
	{
		return false;
	}

	intersection = getPoint(s);
	return true;
}

bool Line::intersects(SegmentLine& segment, Vect2d& intersection)
{
	// Comprueba si el segmento segment intersecciona con la recta actual
	// Si intersecciona, devuelve el punto de intersección en intersection

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

	if (t < 0 || t > 1)
	{
		return false;
	}

	intersection = getPoint(s);
	return true;
}

bool Line::incorrectSegmentIntersection(SegmentLine& l)
{
	return false;
}

Line & Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "Line --->\n\tPoint A: " << line._orig << "\n\tPoint B: " << line._dest << "\n";

	return os;
}

bool Line::segmentIntersection(SegmentLine& l)
{
	// XXXX
	return false;
}