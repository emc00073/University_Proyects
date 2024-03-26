#include "stdafx.h"
#include "DrawSegment.h"

// Public methods

AlgGeom::DrawSegment::DrawSegment (SegmentLine &segment): Model3D()
{
    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(segment.getA().getX(), segment.getA().getY(), .0f) },
            VAO::Vertex { vec3(segment.getB().getX(), segment.getB().getY(), .0f) }
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}

AlgGeom::DrawSegment::DrawSegment(Segment3d& segment): Model3D()
{
    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(segment.getOrigin().getX(), segment.getOrigin().getY(), segment.getOrigin().getZ()) },
            VAO::Vertex { vec3(segment.getDestination().getX(), segment.getDestination().getY(), segment.getDestination().getZ()) }
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}
