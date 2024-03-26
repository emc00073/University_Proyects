#include "stdafx.h"
#include "Polygon.h"

// Public methods

Polygon::Polygon()
{
}

Polygon::Polygon(const Polygon& Polygon)
{
	_vertices = std::vector<Vertex>(Polygon._vertices);
}

Polygon::Polygon(std::vector<Vertex>& vertices)
{
	_vertices = std::vector<Vertex>(vertices);
}

SegmentLine Polygon::getEdge(int i)
{
	return SegmentLine(getVertexAt(i), getVertexAt((i + 1) % _vertices.size()));
}

Polygon::Polygon(const std::string & filename)
{
	// Constuir el poligono a partir del fichero
	// Cargar fichero
	std::ifstream file(filename);
	std::string line;
	int i = 0;
	// Leer fichero
	while (std::getline(file, line))
	{
		// Procesar linea
		std::istringstream iss(line);
		double x, y;
		if (!(iss >> x >> y)) { break; } // error
		// Procesar x e y
		Point point(x, y);
		Vertex vertex(point, this, i++);
		this->add(vertex);
	}
}

Polygon::~Polygon()
{
}

bool Polygon::add(const Vertex & vertex)
{
	size_t index = _vertices.size();

	//if (intersectsWithAnySegment(vertex)) return false;

	_vertices.push_back(vertex);
	_vertices[index].setPolygon(this);
	_vertices[index].setPosition(static_cast<int>(index));

	return true;
}

bool Polygon::add(const Point & point)
{
	Vertex vertex(point);

	return this->add(vertex);
}

Vertex Polygon::getVertexAt(int position)
{
	if (position >= 0 && position < _vertices.size())
	{
		return _vertices[position];
	}
	else 
	{
		return Vertex();
	}
}

bool Polygon::intersects(Line& line, Vect2d& interseccion)
{
	// Comprobar si la linea interseca con alguno de los segmentos del poligono
	for (int i = 0; i < _vertices.size(); i++)
	{
		SegmentLine segment = getEdge(i);
		if (segment.intersects(line, interseccion))
		{
			return true;
		}
	}
	return false;
}

bool Polygon::intersects(RayLine& ray, Vect2d& interseccion)
{
	// Comprobar si el rayo interseca con alguno de los segmentos del poligono
	for (int i = 0; i < _vertices.size(); i++)
	{
		SegmentLine segment = getEdge(i);
		if (segment.intersects(ray, interseccion))
		{
			return true;
		}
	}
	return false;
}

bool Polygon::convex()
{
	// True si el poligono es convexo: todos los angulos internos son menores que 180 grados
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (!_vertices[i].convex())
		{
			return false;
		}
	}
	return true;
}

bool Polygon::intersects(SegmentLine& segment, Vect2d& interseccion)
{
	// Comprobar si el segmento interseca con alguno de los segmentos del poligono
	for (int i = 0; i < _vertices.size(); i++)
	{
		SegmentLine segmento = getEdge(i);
		if (segmento.intersects(segment, interseccion))
		{
			return true;
		}
	}
	return false;
}

Vertex Polygon::next(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index + 1) % _vertices.size()];
	}

	return Vertex();
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon)
{
	for (int i = 0; i < polygon._vertices.size(); i++) 
	{
		os << polygon._vertices[i] << "\n";
	}

	return os;
}

Vertex Polygon::previous(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index - 1 + _vertices.size()) % _vertices.size()];
	}

	return Vertex();
}

Polygon & Polygon::operator=(const Polygon &polygon)
{
	if (this != &polygon)
	{
		this->_vertices = polygon._vertices;
	}

	return *this;
}

bool Polygon::pointInConvexPolygonGeo(Point& point)
{
    // Comprueba si un punto esta dentro de un poligono convexo
	// Tiene que estar a la izquierda de todos los segmentos
	for (int i = 0; i < _vertices.size(); i++)
	{
		SegmentLine segmento = getEdge(i);
		Point p1 = segmento.getA();
		Point p2 = segmento.getB();

		if (!point.left(p1, p2))
		{
			return false;
		}
	}
	return true;
}

void Polygon::save(const std::string& filename)
{
	// Guardar el poligono en un fichero
	// Crear fichero si no existe
	std::ofstream file(filename);
	// Escribir en el fichero
	for (int i = 0; i < _vertices.size(); i++)
	{
		file << _vertices[i].getPoint().getX() << " " << _vertices[i].getPoint().getY() << "\n";
	}
}

void Polygon::set(Vertex& vertex, int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}
