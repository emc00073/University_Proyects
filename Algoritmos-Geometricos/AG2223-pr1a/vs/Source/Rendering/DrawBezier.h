#pragma once

#include "Bezier.h"
#include "Model3D.h"

namespace AlgGeom
{
    class DrawBezier : public Model3D {
    protected:
        Bezier _bezier;

    public:
        DrawBezier(Bezier& t);
        DrawBezier(const DrawBezier& drawSegment) = delete;
        virtual ~DrawBezier() {};
    };
}