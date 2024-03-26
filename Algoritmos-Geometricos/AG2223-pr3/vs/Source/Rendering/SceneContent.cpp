#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw3D.h"
#include "PointCloud.h"
#include "RandomUtilities.h"
#include "../Constantes.h"


// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    int numPoints = 50;
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);

    char Pra2 = 'c';

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
    if (Pra2 == 'a') {
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

        this->addNewModel((new DrawLine3d(*line1))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawRay3D(*ray1))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawSegment(*segment1))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());

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
            if (checkPoint.distance(p) < distancia && checkPoint.distance(p) > EPSILON) {
                distancia = checkPoint.distance(p);
				point = checkPoint;
            }
		}

        Line3d L1 = Line3d(p, q);
        Vect3d point2 = point.add(vector);
        Line3d L2 = Line3d(point, point2);

        this->addNewModel((new DrawLine3d(L1))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawLine3d(L2))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName());


        // 4. Comprobar si L1 y L2 son paralelas.

        bool areParallel = L1.isParallel(L2);
        std::cout << "Son paralelas: " << areParallel << std::endl;

        // 5. Encontrar el punto V más distanciado a la recta L1 y crear S2 como el
        // segmento perpendicular a L1 en V. Comprobar que L1 y S2 son
        // perpendiculares.

        Vect3d v;
        distancia = -10000000000.0f;
        for (int i = 0; i < numPoints; i++)
        {
            Vect3d checkPoint = pointCloud->getPoint(i);
            if (L1.distance(checkPoint) > distancia) {
                distancia = L1.distance(checkPoint);
                v = checkPoint;
            }
        }

        Vect3d v2 = L1.normalLine(v).getDestination();

        Segment3d S2 = Segment3d(v, v2);
        this->addNewModel((new DrawSegment(S2))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName());

        Line3d L3 = Line3d(v, v2);
        bool arePerpedicular = L1.isPerpendicular(L3);
        std::cout << "Son perpendiculares: " << arePerpedicular << std::endl;

        // 6. Calcular las distancias entre L1 y L2.
        float distance = L1.distance(L2);
        std::cout << "Distancia entre L1 y L2: " << distance << std::endl;

        // 7. Calcula y dibuja la caja AABB de la nube de puntos.

        float minX = 10000000000.0f, minY = 10000000000.0f, minZ = 10000000000.0f;
        float maxX = -10000000000.0f, maxY = -10000000000.0f, maxZ = -10000000000.0f;

        for (int i = 0; i < numPoints; i++)
        {
			Vect3d checkPoint = pointCloud->getPoint(i);
			if (checkPoint.getX() < minX) minX = checkPoint.getX();
            if (checkPoint.getY() < minY) minY = checkPoint.getY();
            if (checkPoint.getZ() < minZ) minZ = checkPoint.getZ();
            if (checkPoint.getX() > maxX) maxX = checkPoint.getX();
            if (checkPoint.getY() > maxY) maxY = checkPoint.getY();
            if (checkPoint.getZ() > maxZ) maxZ = checkPoint.getZ();
		}

        AABB aabb = AABB(Vect3d(minX, minY, minZ), Vect3d(maxX, maxY, maxZ));
        this->addNewModel((new DrawAABB(aabb))->overrideModelName());

        // 8. Obtener el plano P, correspondiente a la tapa superior de la caja y
        // pintarlo.

        Vect3d p1 = Vect3d(minX, maxY, minZ);
        Vect3d p2 = Vect3d(maxX, maxY, minZ);
        Vect3d p3 = Vect3d(minX, maxY, maxZ);

        Plane* plane = new Plane(p1, p2, p3, true);
        this->addNewModel((new DrawPlane(*plane))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName());

        delete line1;
        delete ray1;
        delete segment1;
        delete pointCloud;

    }


    // Práctica 2b
    /*
        1. Crear el plano A con tres puntos aleatorios.
        2. Crear una recta L3 que intersecta con A y crear y pintar la recta
        reflejo en dicho plano L4.
        3. Crear un punto aleatorio V1, pintarlo de otro color y calcular su
        distancia al plano A. Obtener el punto V2 como el punto reflejado en
        A de V1.
        4. Comprobar que la distancia de V1 y V2 al plano A es la misma.
    */
    if (Pra2 == 'b') {
        // 1. Crear el plano A con tres puntos aleatorios (plano vertical).

        Vect3d a = Vect3d(0.0f, 0.0f, -4.0f);
        Vect3d b = Vect3d(1.0f, 0.0f, -4.0f);
        Vect3d c = Vect3d(0.0f, 1.0f, -4.0f);

        Plane* plane = new Plane(a, b, c, true);
        this->addNewModel((new DrawPlane(*plane))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());


        // 2. Crear una recta L3 que intersecta con A y crear y pintar la recta

        Vect3d d = Vect3d(4.0f, 4.0f, 3.0f);
        Vect3d e = Vect3d(1.0f, 1.0f, 1.0f);

        Line3d* line3 = new Line3d(d, e);
        this->addNewModel((new DrawLine3d(*line3))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());

        // reflejo en dicho plano L4.

        // Obtener la intersección de line3 con el plano
        Vect3d point;
        plane->intersect(*line3, point);

        // Obtener la dirección de la recta reflejo
        Vect3d dir = d;
        dir = plane->reflectedPoint(dir);

        Line3d* line4 = new Line3d(point, dir);
        this->addNewModel((new DrawLine3d(*line4))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName());

        // 3. Crear un punto aleatorio V1, pintarlo de otro color y calcular su
        // distancia al plano A. Obtener el punto V2 como el punto reflejado en
        // A de V1.

        Vect3d v1 = Vect3d(-2.0f, 0.0f, -2.2f);
        Vect3d v__;
        this->addNewModel((new DrawPoint(v1))->setPointColor(vec4(.0f, .0f, .0f, .0f))->setPointSize(3.0f)->overrideModelName());

        float distance = plane->distance(v1, v__);
        std::cout << "Distancia de V1 al plano A: " << distance << std::endl;

        Vect3d v2 = plane->reflectedPoint(v1);
        this->addNewModel((new DrawPoint(v2))->setPointColor(vec4(.0f, .0f, .0f, .0f))->setPointSize(3.0f)->overrideModelName());

        // 4. Comprobar que la distancia de V1 y V2 al plano A es la misma.

        float distance2 = plane->distance(v2, v__);
        std::cout << "Distancia de V2 al plano A: " << distance2 << std::endl;

        delete plane;
        delete line3;
        delete line4;
    }

    // Práctica 2c
    /*
        1. Crea un objeto TriangleModel a partir de cualquier .obj y mostrarlo
        en modo alambre.
        2. Dibujar con otro color los triángulos, en principio 6 distintos, cuyas
        normales se asemejen más a los 6 planos ortogonales (1,0,0), (0,1,0),
        (0,0,1), (-1,0,0), (0,-1,0), (0,0,-1).
    */
    if (Pra2 == 'c') {
        // 1. Crea un objeto TriangleModel a partir de cualquier .obj y mostrarlo
        // en modo alambre.
        TriangleModel* triangleModel = new TriangleModel("Assets/Models/Dog.obj");
        auto model = (new DrawMesh(*triangleModel))->overrideModelName();
        this->addNewModel(model);

        // 2. Dibujar con otro color los triángulos, en principio 6 distintos, cuyas
        // normales se asemejen más a los 6 planos ortogonales (1,0,0), (0,1,0),
        // (0,0,1), (-1,0,0), (0,-1,0), (0,0,-1).

        // Vectores normales de los planos ortogonales
        Vect3d normal1 = Vect3d(1.0f, 0.0f, 0.0f);
        Vect3d normal2 = Vect3d(0.0f, 1.0f, 0.0f);
        Vect3d normal3 = Vect3d(0.0f, 0.0f, 1.0f);
        Vect3d normal4 = Vect3d(-1.0f, 0.0f, 0.0f);
        Vect3d normal5 = Vect3d(0.0f, -1.0f, 0.0f);
        Vect3d normal6 = Vect3d(0.0f, 0.0f, -1.0f);

        // Guardar los triángulos que se asemejen a los planos ortogonales
        Triangle3d triangle1, triangle2, triangle3, triangle4, triangle5, triangle6;
        float dot1 = 0.0f, dot2 = 0.0f, dot3 = 0.0f, dot4 = 0.0f, dot5 = 0.0f, dot6 = 0.0f;

        for (int i = 0; i < triangleModel->numTriangles(); i++) {
            Triangle3d triangle = triangleModel->getFace(i);

            Vect3d normal = triangle.normal().normalize();

            float dot = normal.dot(normal1);
            if (dot > dot1) {
				dot1 = dot;
				triangle1 = triangle;

                std::cout << "Triangle " << i << " vertices: " << triangle.getA().getX() << " " << triangle.getA().getY() << " " << triangle.getA().getZ() << std::endl;
                std::cout << "Triangle " << i << " vertices: " << triangle.getB().getX() << " " << triangle.getB().getY() << " " << triangle.getB().getZ() << std::endl;
                std::cout << "Triangle " << i << " vertices: " << triangle.getC().getX() << " " << triangle.getC().getY() << " " << triangle.getC().getZ() << std::endl;

                std::cout << "Triangle1 " << i << " vertices: " << triangle1.getA().getX() << " " << triangle1.getA().getY() << " " << triangle1.getA().getZ() << std::endl;
                std::cout << "Triangle1 " << i << " vertices: " << triangle1.getB().getX() << " " << triangle1.getB().getY() << " " << triangle1.getB().getZ() << std::endl;
                std::cout << "Triangle1 " << i << " vertices: " << triangle1.getC().getX() << " " << triangle1.getC().getY() << " " << triangle1.getC().getZ() << std::endl;

                // Cout normales y dot
                std::cout << "Triangle " << i << " normal: " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
                std::cout << "Dot: " << dot << std::endl;
			}

            dot = normal.dot(normal2);
            if (dot > dot2) {
                dot2 = dot;
                triangle2 = triangle;

                std::cout << "Triangle " << i << " vertices: " << triangle.getA().getX() << " " << triangle.getA().getY() << " " << triangle.getA().getZ() << std::endl;
                std::cout << "Triangle " << i << " vertices: " << triangle.getB().getX() << " " << triangle.getB().getY() << " " << triangle.getB().getZ() << std::endl;
                std::cout << "Triangle " << i << " vertices: " << triangle.getC().getX() << " " << triangle.getC().getY() << " " << triangle.getC().getZ() << std::endl;

                std::cout << "Triangle2 " << i << " vertices: " << triangle2.getA().getX() << " " << triangle2.getA().getY() << " " << triangle2.getA().getZ() << std::endl;
                std::cout << "Triangle2 " << i << " vertices: " << triangle2.getB().getX() << " " << triangle2.getB().getY() << " " << triangle2.getB().getZ() << std::endl;
                std::cout << "Triangle2 " << i << " vertices: " << triangle2.getC().getX() << " " << triangle2.getC().getY() << " " << triangle2.getC().getZ() << std::endl;

                // Cout normales y dot
                std::cout << "Triangle " << i << " normal: " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
                std::cout << "Dot: " << dot << std::endl;
            }

            dot = normal.dot(normal3);
            if (dot > dot3) {
				dot3 = dot;
				triangle3 = triangle;
			}

            dot = normal.dot(normal4);
            if (dot > dot4) {
                dot4 = dot;
                triangle4 = triangle;
            }

            dot = normal.dot(normal5);
            if (dot > dot5) {
				dot5 = dot;
				triangle5 = triangle;
			}

            dot = normal.dot(normal6);
            if (dot > dot6) {
				dot6 = dot;
				triangle6 = triangle;
			}
        }

        // Mostrar los triángulos especiales
        this->addNewModel((new DrawTriangle(triangle1))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(1.0f, 0.0f, 0.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawTriangle(triangle2))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 1.0f, 0.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawTriangle(triangle3))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 0.0f, 1.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawTriangle(triangle4))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(1.0f, 1.0f, 0.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawTriangle(triangle5))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());
        this->addNewModel((new DrawTriangle(triangle6))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(1.0f, 0.0f, 1.0f, 1.0f))->overrideModelName());
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
