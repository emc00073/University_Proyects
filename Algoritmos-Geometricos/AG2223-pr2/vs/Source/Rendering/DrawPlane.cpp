#include "stdafx.h"
#include "DrawPlane.h"

AlgGeom::DrawPlane::DrawPlane(Plane& plane) : Model3D(), _plane(plane) 
{
    // Calcular el punto de corte con el maximo y minimo de la pantalla
    // Dimensiones de la pantalla
    int MAX_T = 8000;

    Vect3d pointA = _plane.getPointA();
    Vect3d pointB = _plane.getPointB();
    Vect3d pointC = _plane.getPointC();

    Line3d lineAB(pointA, pointB);
    Line3d lineBC(pointB, pointC);
    Line3d lineCA(pointC, pointA);
    Line3d lineBA(pointB, pointA);
    Line3d lineCB(pointC, pointB);
    Line3d lineAC(pointA, pointC);

    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
        VAO::Vertex { vec3(lineAB.getPoint(MAX_T).getX(), lineAB.getPoint(MAX_T).getY(), lineAB.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(lineAC.getPoint(MAX_T).getX(), lineAC.getPoint(MAX_T).getY(), lineAC.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(lineBC.getPoint(MAX_T).getX(), lineBC.getPoint(MAX_T).getY(), lineBC.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(lineBA.getPoint(MAX_T).getX(), lineBA.getPoint(MAX_T).getY(), lineBA.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(lineCA.getPoint(MAX_T).getX(), lineCA.getPoint(MAX_T).getY(), lineCA.getPoint(MAX_T).getZ())},
        VAO::Vertex { vec3(lineCB.getPoint(MAX_T).getX(), lineCB.getPoint(MAX_T).getY(), lineCB.getPoint(MAX_T).getZ())}
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}

AlgGeom::DrawPlane::~DrawPlane()
{
}

