#include "stdafx.h"
#include "DrawLine.h"

// Public methods

AlgGeom::DrawLine::DrawLine (Line &line): Model3D(), _line(line)
{
    // Calcular el punto de corte con el maximo y minimo de la pantalla
    // Dimensiones de la pantalla
    int MAX_X = 800;
    int MIN_X = -800;

    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
        VAO::Vertex { vec3(line.getPoint(MAX_X).getX(), line.getPoint(MAX_X).getY(), .0f)},
        VAO::Vertex { vec3(line.getPoint(MIN_X).getX(), line.getPoint(MIN_X).getY(), .0f)}
    });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}