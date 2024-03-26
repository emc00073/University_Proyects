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
 * File:   DrawPolygon.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:18
 */

#include "Polygon.h"
#include "Model3D.h"

namespace AlgGeom
{
    class DrawPolygon : public Model3D {
    protected:
        Polygon _polygon;

    public:
        DrawPolygon(Polygon& polygon);
        DrawPolygon(const DrawPolygon& ddt) = delete;
        virtual ~DrawPolygon() {};
    };
}