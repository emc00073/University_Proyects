#include "stdafx.h"
#include "PointCloud.h"


PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
	// Construir una nube de size puntos aleatoria
	for (int i = 0; i < size; i++)
	{
		// Random entre -max_x y max_x
		double x = RandomUtilities::getUniformRandom(-max_x, max_x);
		// Random entre -max_y y max_y
		double y = RandomUtilities::getUniformRandom(-max_y, max_y);

		Point* p = new Point(x, y);
		addPoint(*p);
	}
}

PointCloud::PointCloud(const std::string& filename)
{
	// Construir una nube de puntos a partir de un fichero
	// Cargar fichero
	std::ifstream file(filename);
	std::string line;
	// Leer fichero
	while (std::getline(file, line))
	{
		// Procesar linea
		std::istringstream iss(line);
		double x, y;
		if (!(iss >> x >> y)) { break; } // error
		// Procesar x e y
		Point* p = new Point(x, y);
		addPoint(*p);
	}
}

PointCloud::~PointCloud()
{
}

void PointCloud::addPoint(const Point& p)
{
	_points.push_back(p);
}

Point PointCloud::centralPoint()
{
	double minDistance = std::numeric_limits<double>::max();
	Point centralPoint;

	// Devolver el punto que minimiza la distancia a cualquier punto de la nube
	for (size_t i = 0; i < _points.size(); i++) {
		double distance = 0;
		for (size_t j = 0; j < _points.size(); j++) {
			distance += _points[i].distance(_points[j]);
		}
		if (distance < minDistance) {
			minDistance = distance;
			centralPoint = _points[i];
		}
	}
    return centralPoint;
}

Point PointCloud::centralPoint(Point& p)
{
	double minDistance = std::numeric_limits<double>::max();
	Point centralPoint;

	// Devolver el punto que minimiza la distancia a un punto concreto de la nube
	for (size_t i = 0; i < _points.size(); i++) {
		double distance = p.distance(_points[i]);
		if (distance < minDistance) {
			minDistance = distance;
			centralPoint = _points[i];
		}
	}
	return centralPoint;
}

Point PointCloud::maxAbscissa()
{
	double max_x = std::numeric_limits<double>::min();
	Point maxAbscissa;

	// Devolver el punto que maximiza la abscisa
	for (size_t i = 0; i < _points.size(); i++) {
		if (_points[i].getX() > max_x) {
			max_x = _points[i].getX();
			maxAbscissa = _points[i];
		}
	}
	return maxAbscissa;
}

Point PointCloud::minAbscissa()
{
	double min_x = std::numeric_limits<double>::max();
	Point minAbscissa;

	// Devolver el punto que minimiza la abscisa
	for (size_t i = 0; i < _points.size(); i++) {
		if (_points[i].getX() < min_x) {
			min_x = _points[i].getX();
			minAbscissa = _points[i];
		}
	}
	return minAbscissa;
}

Point PointCloud::maxOrdinate()
{
	double max_y = std::numeric_limits<double>::min();
	Point maxOrdinate;

	// Devolver el punto que maximiza la ordenada
	for (size_t i = 0; i < _points.size(); i++) {
		if (_points[i].getY() > max_y) {
			max_y = _points[i].getY();
			maxOrdinate = _points[i];
		}
	}
	return maxOrdinate;
}

Point PointCloud::minOrdinate()
{
	double min_y = std::numeric_limits<double>::max();
	Point minOrdinate;

	// Devolver el punto que minimiza la ordenada
	for (size_t i = 0; i < _points.size(); i++) {
		if (_points[i].getY() < min_y) {
			min_y = _points[i].getY();
			minOrdinate = _points[i];
		}
	}
	return minOrdinate;
}

void PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}

void PointCloud::getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y)
{
}

Point PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return Point();
}

PointCloud & PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void PointCloud::save(const std::string& filename)
{
	// Guardar nube de puntos en fichero
	std::ofstream file(filename);
	for (size_t i = 0; i < _points.size(); i++)
	{
		file << _points[i].getX() << " " << _points[i].getY() << std::endl;
	}
}