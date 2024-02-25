#include "stdafx.h"
#include "SegmentLine.h"

#include "Line.h"
#include "RayLine.h"
#include "../Constantes.h"

// Public methods

SegmentLine::SegmentLine()
{
}

SegmentLine::SegmentLine(const Point& a, const Point& b) : _orig(a), _dest(b)
{
}

SegmentLine::SegmentLine(const SegmentLine& segment) : _orig(segment._orig), _dest(segment._dest)
{
}

SegmentLine::SegmentLine(double ax, double ay, double bx, double by) : _orig(ax, ay), _dest(bx, by)
{
}

SegmentLine::~SegmentLine()
{
}

SegmentLine & SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}

bool SegmentLine::segmentIntersection(SegmentLine& l)
{
	// Comprueba si el segmento l intersecciona de forma propia con el segmento actual

	if (impSegmentIntersection(l)) 
	{
		return false;
	}else 
	{
		return (l._orig.left(_orig, _dest) ^ l._dest.left(_orig, _dest) &&
						_orig.left(l._orig, l._dest) ^ _dest.left(l._orig, l._dest));
	}
	return false;
}

double SegmentLine::getC()
{
	// Calcular el término independiente de la ecuación de la recta que pasa por el segmento
	// y = mx + c -> c = y - mx

	// Si la pendiente es infinita, el término independiente es infinito
	if (isVertical())
	{
		return INFINITY;
	}

	// Si no, calcular el término independiente
	return _orig.getY() - (slope() * _orig.getX());
}

bool SegmentLine::distinct(SegmentLine & segment)
{
	return !equal(segment);
}

bool SegmentLine::equal(SegmentLine & segment)
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

Point SegmentLine::getPoint(double t)
{
    // Obtener el punto perteneciente al segmento o colineal a éste para un t
	// concreto en la ecuación paramétrica : result = a + t(b - a).
	double x = _orig.getX() + t * (_dest.getX() - _orig.getX());
	double y = _orig.getY() + t * (_dest.getY() - _orig.getY());
	return Point(x,y);
}

bool SegmentLine::impSegmentIntersection(SegmentLine& segment)
{
	// Comprueba si el segmento l intersecciona de forma impropia con el segmento actual

	if (_orig.colinear(segment._orig, segment._dest) 
		|| _dest.colinear(segment._orig, segment._dest)
		|| segment._orig.colinear(_orig, _dest) 
		|| segment._dest.colinear(_orig, _dest))
	{
		return true;
	}
}

bool SegmentLine::isHorizontal()
{
	// Comprueba si el segmento es horizontal usando EPSILON
	return (fabs(_orig.getY() - _dest.getY()) < EPSILON);
}

bool SegmentLine::isVertical()
{
    // Comprueba si el segmento es vertical usando EPSILON
	return (fabs(_orig.getX() - _dest.getX()) < EPSILON);
}

double SegmentLine::slope()
{
	// Si el segmento es vertical, la pendiente es infinita
	if (isVertical())
	{
		return INFINITY;
	}
	// Si el segmento es horizontal, la pendiente es 0
	if (isHorizontal())
	{
		return 0.0;
	}
	// Calcular la pendiente de la recta implícita por el segmento
	return (_dest.getY() - _orig.getY()) / (_dest.getX() - _orig.getX());
}

// Protected methods

std::ostream& operator<<(std::ostream& os, const SegmentLine& segment)
{
	os << "Point A: " << segment._orig << ", Point B: " << segment._dest << "\n";

	return os;
}

bool SegmentLine::intersects(Vect2d& c, Vect2d& d, float& s, float& t) {
	
	// Comprueba si las rectas formadas por los segmentos se interseccionan
	// y si lo hacen, calcula los valores de t y s para obtener el punto de intersección

	Vect2d a = _dest;
	Vect2d b = _orig;

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	s = 1 - ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));
	t = ((AB.getX() * AC.getY()) - (AC.getX() * AB.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	return true;
}

bool SegmentLine::intersects(const Line& l, Vect2d& res)
{
	// Comprueba si el segmento intersecciona con la recta l
	// y si lo hace, calcula el punto de intersección

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = l._orig;
	Vect2d d = l._dest;

	Vect2d AB = b - a;
	Vect2d AC = c - a;
	Vect2d CD = d - c;

	double n = ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (abs(n) < EPSILON)
	{
		return false;
	}

	double s = ((CD.getX() * AC.getY()) - (AC.getX() * CD.getY())) / ((CD.getX() * AB.getY()) - (AB.getX() * CD.getY()));

	if (s < 0 || s > 1)
	{
		return false;
	}

	res = getPoint(s);
	return true;
}

bool SegmentLine::intersects(const RayLine& r, Vect2d& res) {
	// Comprueba si el segmento intersecciona con la recta l
	// y si lo hace, calcula el punto de intersección

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = r._orig;
	Vect2d d = r._dest;

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

	if (s < 0 || s > 1 || t < 0)
	{
		return false;
	}

	res = getPoint(s);
	return true;
}

bool SegmentLine::intersects(const SegmentLine& r, Vect2d& res) {
	// Comprueba si el segmento intersecciona con el segmento s
	// y si lo hace, calcula el punto de intersección

	Vect2d a = _orig;
	Vect2d b = _dest;
	Vect2d c = r._orig;
	Vect2d d = r._dest;

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

	if (s < 0 || s > 1 || t < 0 || t > 1)
	{
		return false;
	}

	res = getPoint(s);
	return true;
}

double SegmentLine::distPointSegment(const Vect2d& v)
{
	// Calcula la distancia de un punto a un segmento

	Vect2d P = _orig;
	Vect2d Q = _dest;

	Vect2d d = Q - P;
	Vect2d A = v;

	double t0 = (d * (A - P)) / (d * d);

	if (t0 <= 0)
	{
		return (A - P).module();
	}
	else if (t0 >= 1)
	{
		return (A - (P + d)).module();
	}
	else
	{
		return (A - (P + d.scalarMult(t0))).module();
	}
}