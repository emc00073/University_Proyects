#include "stdafx.h"
#include "DrawAABB.h"

/*
AlgGeom::DrawAABB::DrawAABB(AABB &aabb): Model3D()
{
    Component* component = this->getVoxel();
    vec3 aabbCenter(aabb.getCenter().getX(), aabb.getCenter().getY(), aabb.getCenter().getZ());
    vec3 extent(aabb.getExtent().getX(), aabb.getExtent().getY(), aabb.getExtent().getZ());

    for (VAO::Vertex& vertex : component->_vertices)
    {
        vertex._position = (vertex._position * 2.0f * extent) + aabbCenter;
    }

    this->buildVao(component);
    this->_components.push_back(std::unique_ptr<Component>(component));
}
*/

AlgGeom::DrawAABB::DrawAABB(AABB& aabb) : Model3D()
{
    Component* component = new Component;

    Vect3d minPoint = aabb.getMin();
    Vect3d maxPoint = aabb.getMax();

    Vect3d a = minPoint;
    Vect3d b = Vect3d(maxPoint.getX(), minPoint.getY(), minPoint.getZ());
    Vect3d c = Vect3d(maxPoint.getX(), minPoint.getY(), maxPoint.getZ());
    Vect3d d = Vect3d(minPoint.getX(), minPoint.getY(), maxPoint.getZ());
    Vect3d e = Vect3d(minPoint.getX(), maxPoint.getY(), minPoint.getZ());
    Vect3d f = Vect3d(maxPoint.getX(), maxPoint.getY(), minPoint.getZ());
    Vect3d g = maxPoint;
    Vect3d h = Vect3d(minPoint.getX(), maxPoint.getY(), maxPoint.getZ());

    auto vertex = [](Vect3d v) {
        return VAO::Vertex{ vec3 { v.getX(), v.getY(), v.getZ() } };
        };

    component->_vertices.insert(component->_vertices.end(), {
        vertex(a),
        vertex(b),
        vertex(b),
        vertex(c),
        vertex(c),
        vertex(d),
        vertex(d),
        vertex(a),
        vertex(e),
        vertex(f),
        vertex(f),
        vertex(g),
        vertex(g),
        vertex(h),
        vertex(h),
        vertex(e),
        vertex(a),
        vertex(e),
        vertex(b),
        vertex(f),
        vertex(c),
        vertex(g),
        vertex(d),
        vertex(h),
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
        });

    this->_components.push_back(std::unique_ptr<Component>(component));

    this->buildVao(component);
}


AlgGeom::DrawAABB::~DrawAABB()
{
}

