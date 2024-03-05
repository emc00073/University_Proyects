#include "stdafx.h"
#include "DrawPlane.h"

AlgGeom::DrawPlane::DrawPlane(Plane& plane) : Model3D(), _plane(plane) 
{
    Component* component = new Component;

    Vect3d normal = plane.getNormal();

    Vect3d a = plane.getPointA();
    Vect3d b = plane.getPointB();
    Vect3d c = plane.getPointC();

    Vect3d ab = b.sub(a);
    Vect3d ac = c.sub(a);
    Vect3d bc = c.sub(b);
    Vect3d ba = a.sub(b);
    Vect3d ca = a.sub(c);
    Vect3d cb = b.sub(c);

    const float factor = 10000000;

    auto vertex = [&normal](Vect3d v) {
        return VAO::Vertex{ vec3 { v.getX(), v.getY(), v.getZ() }, vec3 { normal.getX(), normal.getY(), normal.getZ() }};
    };

    component->_vertices.insert(component->_vertices.end(), {
        vertex(cb.scalarMul(factor)),
        vertex(b),
        vertex(ab.scalarMul(factor)),
        vertex(ac.scalarMul(factor)),
        vertex(c),
        vertex(bc.scalarMul(factor)),
        vertex(ba.scalarMul(factor)),
        vertex(a),
        vertex(ca.scalarMul(factor)),
    });

    component->_indices[VAO::IBO_TRIANGLE].insert(component->_indices[VAO::IBO_LINE].end(), {
        0, 1, 2, RESTART_PRIMITIVE_INDEX,
        2, 1, 3, RESTART_PRIMITIVE_INDEX,
        3, 1, 4, RESTART_PRIMITIVE_INDEX,
        3, 4, 5, RESTART_PRIMITIVE_INDEX,
        5, 4, 6, RESTART_PRIMITIVE_INDEX,
        6, 4, 7, RESTART_PRIMITIVE_INDEX,
        6, 7, 8, RESTART_PRIMITIVE_INDEX,
        8, 7, 0, RESTART_PRIMITIVE_INDEX,
        7, 1, 0, RESTART_PRIMITIVE_INDEX,
        1, 7, 4
    });

    this->_components.push_back(std::unique_ptr<Component>(component));

    this->buildVao(component);
}

AlgGeom::DrawPlane::~DrawPlane()
{
}

