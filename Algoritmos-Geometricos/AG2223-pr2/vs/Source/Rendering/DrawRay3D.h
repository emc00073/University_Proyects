#pragma once
class DrawRay3D
{
};

#pragma once

#include "Ray3d.h"
#include "Model3D.h"
#include "Vect3d.h"

namespace AlgGeom
{
    class DrawRay3D : public Model3D
    {
    protected:
        Ray3d _ray;

    public:
        DrawRay3D(Ray3d& t);
        DrawRay3D(const DrawRay3D& drawRay3d) = delete;
        virtual ~DrawRay3D() {};
    };
}