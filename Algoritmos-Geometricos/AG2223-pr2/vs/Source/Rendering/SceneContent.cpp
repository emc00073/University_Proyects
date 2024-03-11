#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw3D.h"
#include "PointCloud.h"
#include "RandomUtilities.h"


// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    /*
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);

    // Random segments
    int numSegments = 8;

    for (int segmentIdx = 0; segmentIdx < numSegments; ++segmentIdx)
    {
        Vect3d a(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
        Vect3d b(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
        Segment3d* segment = new Segment3d(a, b);

        this->addNewModel((new DrawSegment(*segment))->setLineColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
        delete segment;
    }

    // Random points
    int numPoints = 100;

    for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
    {
        Point point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x));
        this->addNewModel((new DrawPoint(point))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    }

    // Random triangles
    int numTriangles = 30;
    float alpha = 2 * glm::pi<float>() / static_cast<float>(numTriangles);

    for (int triangleIdx = 0; triangleIdx < numTriangles; ++triangleIdx)
    {
        float rand_b = RandomUtilities::getUniformRandom(.9f, 1.3f), rand_c = RandomUtilities::getUniformRandom(.8f, 1.4f);
        Vect3d a(.0f, .0f, .0f);
        Vect3d b(glm::cos(alpha * triangleIdx) * rand_b, glm::sin(alpha * triangleIdx) * rand_b, RandomUtilities::getUniformRandom(-.1f, .1f));
        Vect3d c(glm::cos(alpha * (triangleIdx + 1)) * rand_c, glm::sin(alpha * (triangleIdx + 1)) * rand_c, RandomUtilities::getUniformRandom(-.1f, .1f));
        Triangle3d* triangle = new Triangle3d(a, b, c);

        this->addNewModel((new DrawTriangle(*triangle))->setLineColor(RandomUtilities::getUniformRandomColor())->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f))
            ->overrideModelName());
        delete triangle;
    }

    // Point cloud
    PointCloud3d* pointCloud = new PointCloud3d(numPoints * 10, maxBoundaries.y * 6.0f);
    this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    delete pointCloud;

    // Mesh
    TriangleModel* triangleModel = new TriangleModel("Assets/Models/Ajax.obj");
    auto model = (new DrawMesh(*triangleModel))->setModelMatrix(glm::translate(mat4(1.0f), vec3(.0f, .0f, .8f)))->overrideModelName();
    this->addNewModel(model);

    // AABB
    AABB aabb(Vect3d(-1.0f, -2.0f, -1.5f), Vect3d(2.0f, 3.0f, 1.0f));
    this->addNewModel((new DrawAABB(aabb))->overrideModelName());
    */

    int numPoints = 50;
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);

    if (false) {
        // 2 Vect3d
        Vect3d a(4.0f, -0.19939f, 3.0f), b(5.0f, 3.80061f, 5.0f);
        Vect3d c(-0.93961f, 0.60697f, 5.0f), d(0.06039f, 1.60697f, 7.0f);

        // 2 Line3d
        Line3d* line1 = new Line3d(a, b);
        Line3d* line2 = new Line3d(c, d);

        // Mostrar las lineas
        this->addNewModel((new DrawLine3d(*line1))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawLine3d(*line2))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName());

        // Distance between 2 lines
        float distance = line1->distance(*line2);

        std::cout << "Distance between 2 lines: " << distance << std::endl;

        delete line1;
        delete line2;
    }

    if (false) {
        // 2 Vect3d
        Vect3d a(4.0f, -0.19939f, 3.0f), b(5.0f, 3.80061f, 5.0f);
        Vect3d p(-0.93961f, 0.60697f, 5.0f);

        // 1 Line3d
        Line3d* line = new Line3d(a, b);

        // Mostrar la linea
        this->addNewModel((new DrawLine3d(*line))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());
        // Mostrar el punto
        this->addNewModel((new DrawPoint(p))->setPointColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setPointSize(3.0f)->overrideModelName());

        // Line that contains the point normal to the first line
        Line3d lineNormal = line->normalLine(p);

        // Mostrar la linea
        this->addNewModel((new DrawLine3d(lineNormal))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName());

        delete line;
    }

    if (false) {
        // Comprobar si dos lineas son paralelas o perpendiculares
        Vect3d a(0.0f, 0.0f, 0.0f), b(1.0f, 0.0f, 0.0f);
        Vect3d c(0.0f, 0.0f, 1.0f), d(1.0f, 0.0f, 1.0f);

        // 2 Line3d
        Line3d* line1 = new Line3d(a, b);
        Line3d* line2 = new Line3d(c, d);

        // Mostrar las lineas
        this->addNewModel((new DrawLine3d(*line1))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawLine3d(*line2))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName());

        // Comprobar si son paralelas
        bool areParallel = line1->classify(*line2) == Line3d::classifyLines::PARALLEL;

        std::cout << "Are parallel: " << areParallel << std::endl;

        // Comprobar si son perpendiculares
        bool arePerpendicular = line1->classify(*line2) == Line3d::classifyLines::INTERSECT;

        std::cout << "Are perpendicular: " << arePerpendicular << std::endl;
    }

    if (false) {
        // Crear un plano con 3 Vect3d y dibujarlo
        Vect3d a(0.0f, 0.0f, 0.0f), b(1.0f, 0.0f, 0.0f), c(0.0f, 1.0f, 0.0f);
        Plane* plane = new Plane(a, b, c, true);

        // Mostrar el plano
        this->addNewModel((new DrawPlane(*plane))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());

        delete plane;
    }


    // Práctica 2a
    /*
        Construir una escena con:
        1. Una nube de puntos aleatoria de tamaño 50. Fijar un color para que
        todos los puntos de la nube tengan el mismo.
        2. Usar puntos de la nube de forma aleatoria para crear una recta L1, un
        rayo R1 y un segmento S1. Dibujar las cuatro primitivas.
        3. Crear la recta L2 paralela a L1=P+t(Q-P) que pasa por el punto más
        cercano a P de la nube (y que no coincida con Q).
        4. Comprobar si L1 y L2 son paralelas.
        5. Encontrar el punto V más distanciado a la recta L1 y crear S2 como el
        segmento perpendicular a L1 en V. Comprobar que L1 y S2 son
        perpendiculares.
        6. Calcular las distancias entre L1 y L2.
        7. Calcula y dibuja la caja AABB de la nube de puntos.
        8. Obtener el plano P, correspondiente a la tapa superior de la caja y
        pintarlo.
    */
    if (true) {
        // 1. Una nube de puntos aleatoria de tamaño 50. Fijar un color para que
		// todos los puntos de la nube tengan el mismo.
		PointCloud3d* pointCloud = new PointCloud3d(numPoints, maxBoundaries.y * 6.0f);
		this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(4.0f));
        
        // 2. Usar puntos de la nube de forma aleatoria para crear una recta L1, un
        // rayo R1 y un segmento S1. Dibujar las cuatro primitivas.

        Vect3d a = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d b = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d c = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d d = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d e = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d f = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));

        Line3d* line1 = new Line3d(a, b);
        Ray3d* ray1 = new Ray3d(c, d);
        Segment3d* segment1 = new Segment3d(e, f);

        this->addNewModel((new DrawLine3d(*line1))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawRay3D(*ray1))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawSegment(*segment1))->setLineColor(vec4(.0f, .0f, 1.0f, 1.0f))->overrideModelName());

        // 3. Crear la recta L2 paralela a L1=P+t(Q-P) que pasa por el punto más
        // cercano a P de la nube (y que no coincida con Q).
        Vect3d p = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d q = pointCloud->getPoint(RandomUtilities::getUniformRandom(0, numPoints - 1));
        Vect3d vector = q - p;
        Vect3d point;
        float distancia = 10000000000.0f;
        for (int i = 0; i < numPoints; i++)
        {
			Vect3d checkPoint = pointCloud->getPoint(i);
            if (checkPoint.distance(p) < distancia) {
                distancia = checkPoint.distance(checkPoint);
				point = checkPoint;
            }
		}

        Line3d L1 = Line3d(p, q);
        Vect3d point2 = point.add(vector);
        Line3d L2 = Line3d(point, point2);

        this->addNewModel((new DrawLine3d(L2))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName());





        delete line1;
        delete ray1;
        delete segment1;
        delete pointCloud;

    }



    //delete pointCloud;
}

void AlgGeom::SceneContent::buildCamera(uint16_t width, uint16_t height)
{
    Camera* camera = new Camera(width, height, false);
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
