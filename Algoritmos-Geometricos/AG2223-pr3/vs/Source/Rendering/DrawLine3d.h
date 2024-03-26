#pragma once

#include "Line3d.h"
#include "Model3D.h"
#include "Vect3d.h"

namespace AlgGeom
{
    class DrawLine3d : public Model3D
    {
    protected:
        Line3d _line;

    public:
        DrawLine3d(Line3d& t);
        DrawLine3d(const DrawLine3d& drawLine) = delete;
        virtual ~DrawLine3d() {};
    };
}