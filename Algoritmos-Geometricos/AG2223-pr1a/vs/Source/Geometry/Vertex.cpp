#include "stdafx.h"
#include "Polygon.h"

#include "Vertex.h"

// Public methods

Vertex::Vertex() : Point()
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point& point) : Point(point)
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point & point, Polygon* polygon, int pos) : Point(point)
{
	_position = pos;
	_polygon = polygon;
}

Vertex::~Vertex()
{
}

bool Vertex::convex()
{
	// Comprobar si el vertice es convexo con respecto a los dos segmentos que lo rodean
	Vertex previous = this->previous();
	Vertex next = this->next();
	return (next.left(previous, *this));
}

bool Vertex::concave()
{
	// Comprobar si el vertice es concavo con respecto a los dos segmentos que lo rodean
	return !this->convex();
}

Vertex Vertex::next()
{
	// Devuelve el siguiente vertice del poligono segun el orden de los vertices
	if (_position >= 0)
	{
		return _polygon->getVertexAt((_position + 1) % _polygon->getNumVertices());
	}
	return *this;
}

SegmentLine Vertex::nextEdge()
{
	// Construir el segmento que une el vertice con el siguiente
	return SegmentLine(*this, this->next());
}

Vertex & Vertex::operator=(const Vertex & vertex)
{
	if (this != &vertex)
	{
		Point::operator=(vertex);
		this->_polygon = vertex._polygon;
		this->_position = vertex._position;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
	os << "Position: " << std::to_string(vertex._position);

	return os;
}

Vertex Vertex::previous()
{
	// Devuelve el vertice anterior del poligono segun el orden de los vertices
	if (_position >= 0)
	{
		return _polygon->getVertexAt((_position - 1 + _polygon->getNumVertices()) % _polygon->getNumVertices());
	}
	return Vertex();
}

SegmentLine Vertex::previousEdge()
{
	// Construir el segmento que une el vertice con el anterior
	return SegmentLine(this->previous(), *this);
}