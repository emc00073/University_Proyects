#include "stdafx.h"
#include "DrawRay3D.h"

AlgGeom::DrawRay3D::DrawRay3D(Ray3d& ray): Model3D(), _ray(ray)
{
    // Dimensiones de la pantalla
    int MAX_X = 800;

    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
        VAO::Vertex { vec3(ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ())}
,       VAO::Vertex { vec3(ray.getPoint(MAX_X).getX(), ray.getPoint(MAX_X).getY(), ray.getPoint(MAX_X).getZ())},
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}
