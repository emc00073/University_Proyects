#include "stdafx.h"
#include "DrawPointCloud.h"

// Public methods

AlgGeom::DrawPointCloud::DrawPointCloud (PointCloud &pointCloud): Model3D(), _pointCloud(pointCloud)
{
    // Dibujar la nube de puntos
    Component* component = new Component;
    for (size_t i = 0; i < _pointCloud.getPoints().size(); i++)
    {
        component->_vertices.insert(component->_vertices.end(), {VAO::Vertex { vec3(_pointCloud.getPoints()[i].getX(), _pointCloud.getPoints()[i].getY(), .0f) } });
        component->_indices[VAO::IBO_POINT].insert(component->_indices[VAO::IBO_POINT].end(), { (unsigned int)i });
    }
    this->_components.push_back(std::unique_ptr<Component>(component));

    this->buildVao(component);
}
