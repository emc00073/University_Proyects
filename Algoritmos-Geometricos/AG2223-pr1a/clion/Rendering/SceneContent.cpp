#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "PointCloud.h"
#include "RandomUtilities.h"


// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    vec2 minBoundaries = vec2(-3.0f, -.4), maxBoundaries = vec2(-minBoundaries);

    // Random segments
    int numSegments = 8;

    for (int segmentIdx = 0; segmentIdx < numSegments; ++segmentIdx)
    {
        Point a(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y));
        Point b(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y));
        SegmentLine* segment = new SegmentLine(a, b);

        this->addNewModel((new DrawSegment(*segment))->setLineColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
        delete segment;
    }

    // Random points
    int numPoints = 200;

    for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
    {
        Point point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x));
        this->addNewModel((new DrawPoint(point))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    }

    // Polygon
    float polygonAngle = .0f;
    constexpr float polygonAlpha = 2.0f * glm::pi<float>() / 5.0f;
    Polygon* polygon = new Polygon;

    while (polygonAngle < 2.0f * glm::pi<float>())
    {
        polygon->add(Point(std::cos(polygonAngle), std::sin(polygonAngle)));
        polygonAngle += polygonAlpha;
    }

    this->addNewModel((new DrawPolygon(*polygon))->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f))->overrideModelName()->setModelMatrix(glm::rotate(mat4(1.0f), (glm::abs(4 * polygonAlpha - glm::pi<float>() / 2.0f * 3.0f)), vec3(.0f, .0f, 1.0f))));
    delete polygon;
}

void AlgGeom::SceneContent::buildCamera(uint16_t width, uint16_t height)
{
    Camera* camera = new Camera(width, height, true);
    camera->setPosition(vec3(.0f, .0f, 4.0f));
    camera->setLookAt(vec3(.0f, .0f, 0.0f));
    camera->saveCamera();

    this->_camera.push_back(std::unique_ptr<Camera>(camera));
}


// ------------------------------------------------------------------------------------------


AlgGeom::SceneContent::SceneContent()
{
}

AlgGeom::SceneContent::~SceneContent()
{
	_camera.clear();
	_model.clear();
}

void AlgGeom::SceneContent::addNewCamera(ApplicationState* appState)
{
	_camera.push_back(std::unique_ptr<Camera>(new Camera(appState->_viewportSize.x, appState->_viewportSize.y, true)));
}

void AlgGeom::SceneContent::addNewModel(Model3D* model)
{	
	_model.push_back(std::unique_ptr<Model3D>(model));
}

AlgGeom::Model3D* AlgGeom::SceneContent::getModel(Model3D::Component* component)
{
	for (auto& model : _model)
	{
		if (model->belongsModel(component))
			return model.get();
	}

	return nullptr;
}
