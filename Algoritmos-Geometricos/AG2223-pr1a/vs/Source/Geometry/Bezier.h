
#pragma once

#include "Point.h"

/**
*	@brief This class represents a Bezier curve.
*	@author Emilio
*/
class Bezier
{
	private:
		Point P_start;
		Point P_end;
		Point P_control1;
		Point P_control2;

	public:
		// Constructors
		Bezier();
		Bezier(const Bezier &bezier);

		// Destructor
		~Bezier();

		Bezier(Point& start, Point& end, Point& control1, Point& control2);

		Point getStart();
		Point getEnd();
		Point getControl1();
		Point getControl2();

		void setStart(Point& start);
		void setEnd(Point& end);
		void setControl1(Point& control1);
		void setControl2(Point& control2);

		Point getPoint(float t);
};

