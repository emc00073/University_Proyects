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
 * File:   Vect2d.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:01
 */

#include "Point.h"

class Vect2d : public Point  
{
public:      
    Vect2d () : Point () { }
    Vect2d (double x, double y): Point (x, y) { } 
   
	/**
	*	@return X coordinate.
	*/
    double getX() {return _x; }

	/**
	*	@return Y coordinate.
	*/
    double getY() {return _y; }
    
    /**
	*	@brief Copy constructor.
	*/
	Vect2d(const Vect2d& vector);

	/**
	*	@brief Copy constructor.
	*/
	Vect2d(const Point& point);

	/**
	*	@brief Destructor.
	*/
	virtual ~Vect2d();

	/**
	*	@brief Returns a . b (scalar product).
	*/
	double dot(Vect2d& b);

	/**
	*	@brief Assignment operator.
	*/
	virtual Vect2d& operator=(const Vect2d& vector);

	/**
	*	@brief Returns this + b (sum of vectors).
	*/
	Vect2d operator+(const Vect2d& b);

	/**
	*	@brief Returns a - b (substraction of vectors).
	*/
	Vect2d operator-(const Vect2d& b);

	/**
	*	@brief Returns t . a (vector product by a scalar).
	*/
	Vect2d scalarMult(double t);
};

