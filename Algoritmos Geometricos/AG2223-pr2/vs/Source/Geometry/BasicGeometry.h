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

#include "stdafx.h"

namespace BasicGeometry
{
	const float EPSILON = glm::epsilon<float>();

	bool equal(double a, double b);
	double determinant2x2(double a, double b, double c, double d);
	double determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i);
	double min3(double a, double b, double c);
	double max3(double a, double b, double c);
	double min2(double a, double b);
	double max2(double a, double b);   
};

inline bool BasicGeometry::equal(double a, double b) 
{
	return (abs(a - b) < glm::epsilon<float>());
}

inline double BasicGeometry::determinant2x2(double x1, double y1, double x2, double y2)
{
	return glm::determinant(glm::mat2(x1, y1, x2, y2));
}

inline double BasicGeometry::determinant3x3(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
	return glm::determinant(mat3(x1, y1, z1, x2, y2, z2, x3, y3, z3));
}

inline double BasicGeometry::min3(double a, double b, double c)
{
	return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

inline double BasicGeometry::max3(double a, double b, double c)
{
	return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

inline double BasicGeometry::min2(double a, double b)
{
	return (a < b ? a : b);
}

inline double BasicGeometry::max2(double a, double b)
{
	return (a > b ? a : b);
}