#include "stdafx.h"
#include "DrawLine3d.h"

// Public methods

AlgGeom::DrawLine3d::DrawLine3d(Line3d& line) : Model3D(), _line(line)
{
    // Calcular el punto de corte con el maximo y minimo de la pantalla
    // Dimensiones de la pantalla
    int MAX_T = 8000;
    int MIN_T = -8000;

    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
        VAO::Vertex { vec3(line.getPoint(MAX_T).getX(), line.getPoint(MAX_T).getY(), line.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(line.getPoint(MIN_T).getX(), line.getPoint(MIN_T).getY(), line.getPoint(MIN_T).getZ())}
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}