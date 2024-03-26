#include "stdafx.h"
#include "DrawBezier.h"

// Public methods

AlgGeom::DrawBezier::DrawBezier(Bezier& bezier) : Model3D(), _bezier(bezier)
{
	Component* component = new Component;
	const float step = .01f;
	int segments = 1 / step;
	for (unsigned int i = 0; i < segments; i++)
	{
		Point p = bezier.getPoint(i * step);
		component->_vertices.insert(component->_vertices.end(), {
			VAO::Vertex { vec3(p.getX(), p.getY(), .0f) },
		});
		component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { i });
		if (i < segments - 1)
		{
			component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { i + 1 });
		}
	}

	this->_components.push_back(std::unique_ptr<Component>(component));

	component->completeTopology();
	this->buildVao(component);
}