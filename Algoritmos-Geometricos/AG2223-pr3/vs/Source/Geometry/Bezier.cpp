#include "stdafx.h"
#include "Bezier.h"

// Bezier.cpp : implementation file
Bezier::Bezier()
{
}

Bezier::Bezier(const Bezier& bezier)
{
	this->P_start = bezier.P_start;
	this->P_end = bezier.P_end;
	this->P_control1 = bezier.P_control1;
	this->P_control2 = bezier.P_control2;
}

Bezier::~Bezier()
{
}

Bezier::Bezier(Point& start, Point& end, Point& control1, Point& control2)
{	
	this->P_start = start;
	this->P_end = end;
	this->P_control1 = control1;
	this->P_control2 = control2;
}

Point Bezier::getStart()
{
	return this->P_start;
}

Point Bezier::getEnd()
{
	return this->P_end;
}

Point Bezier::getControl1()
{
	return this->P_control1;
}

Point Bezier::getControl2()
{
	return this->P_control2;
}

void Bezier::setStart(Point& start)
{
	this->P_start = start;
}

void Bezier::setEnd(Point& end)
{
	this->P_end = end;
}

void Bezier::setControl1(Point& control1)
{
	this->P_control1 = control1;
}

void Bezier::setControl2(Point& control2)
{
	this->P_control2 = control2;
}

Point Bezier::getPoint(float t)
{
	Point p;
	p.setX((1 - t)*(1 - t)*(1 - t)*P_start.getX() + 3 * (1 - t) * (1 - t) * t * P_control1.getX() + 3 * (1 - t) * t * t * P_control2.getX() + t * t * t * P_end.getX());
	p.setY((1 - t)*(1 - t)*(1 - t)*P_start.getY() + 3 * (1 - t) * (1 - t) * t * P_control1.getY() + 3 * (1 - t) * t * t * P_control2.getY() + t * t * t * P_end.getY());
	return p;
}
