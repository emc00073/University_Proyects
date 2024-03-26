/*   Copyright (C) 2023 Lidia Ortega Alvarado, Alfonso Lopez Ruiz
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see https://github.com/AlfonsoLRz/AG2223.
*/

#pragma once

/* 
 * File:   Vertex.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 10:22
 */

#include "Point.h"
#include "SegmentLine.h"

class Polygon;			// Forward declaration due to circular reference betwen both classes

class Vertex : public Point
{
protected:
	const static int INVALID_POSITION = -1;

protected:
	Polygon*			_polygon;						//!< Polygon where the vertex belongs to
	int					_position;						//!< Position of the vertex in the polygon

public:
	/**
	*	@brief Constructor of a vertex no associated to any polygon (position = -1).
	*/
	Vertex();

	/**
	*	@brief Constructor of a vertex no associated to any polygon (position = -1). The point is valid tho.
	*/
	Vertex(const Point& point);

	/**
	*	@brief Constructor of a valid point associated to a polygon.
	*/
	Vertex(const Point& point, Polygon* polygon, int pos = -1);

	/**
	*	@brief Destructor.
	*/
	virtual ~Vertex();

	/**
	*	@brief Determines if the vertex is in a concave position of the polygon.
	*/
	bool concave();

	/**
	*	@brief Determines if the vertex is in a convex position of the polygon.
	*/
	bool convex();

	/**
	*	@brief Returns the point value.
	*/
	Point getPoint() { return Point(_x, _y); }

	/**
	*	@brief Returns the polygon associated to this vertex.
	*/
	Polygon* getPolygon() { return _polygon; }

	/**
	*	@brief Returns the position of the current vertex in the polygon, if any.
	*/
	int getPositionInPolygon() { return _position; }

	/**
	*	@brief Next vertex in counterclockwise order.
	*/
	Vertex next();

	/**
	*	@brief Next edge in counterclockwise order.
	*/
	SegmentLine nextEdge();
	
	/**
	*	@brief Assignment operator.
	*/
	virtual Vertex& operator=(const Vertex& vertex);

	/**
	*	@brief Overriding cout call.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

	/**
	*	@brief Next vertex in clockwise order.
	*/
	Vertex previous();

	/**
	*	@brief Next edge in clockwise order.
	*/
	SegmentLine previousEdge();

	/**
	*	@brief Modifies the coordinates of the vertex.
	*/
	void setPoint(Point& point) { _x = point.getX(); _y = point.getY(); }

	/**
	*	@brief Modifies the polygon associated to this vertex.
	*/
	void setPolygon(Polygon* polygon) { _polygon = polygon; }

	/**
	*	@brief Modifies the position of the vertex in the polygon, if any.
	*/
	void setPosition(int pos) { _position = pos; }
};

