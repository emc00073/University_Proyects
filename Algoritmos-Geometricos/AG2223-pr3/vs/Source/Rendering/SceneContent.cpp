#include "stdafx.h"
#include "SceneContent.h"

#include <chrono>
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

    char Pr3 = 'a';

    // Práctica 3
    /*
        Prueba 3.a
            1. Cargar un modelo .obj y obtener su caja envolvente asociada al
            modelo con: AABB getAABB(). Por el momento no pintamos la caja.
            2. Cargar un modelo .obj y obtener su nube de puntos asociada.
            3. Crear un plano aleatorio donde uno de los tres puntos sea el centro
            de la caja, los otros dos pueden ser aleatorios.
            4. Pintar los triángulos que estén en el lado positivo de un color, los que
            estén en el lado negativo en otro y los que crucen al plano en un
            tercer color
    */

    if (Pr3 == 'a') {
        // 1. Cargar un modelo .obj y obtener su caja envolvente asociada al
        // modelo con: AABB getAABB(). Por el momento no pintamos la caja.
        TriangleModel* triangleModel = new TriangleModel("Assets/Models/Dog.obj");
        AABB aabb = triangleModel->getAABB();

        // 2. Cargar un modelo .obj y obtener su nube de puntos asociada.
        PointCloud3d pointCloud(PointCloud3d(triangleModel->getCloud()));
        this->addNewModel((new DrawPointCloud(pointCloud))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName());
        
        // 3. Crear un plano aleatorio donde uno de los tres puntos sea el centro
        // de la caja, los otros dos pueden ser aleatorios.
        Vect3d center = aabb.getCenter();
        Vect3d p1 = center;
        Vect3d p2 = Vect3d(aabb.getMax());
        Vect3d p3 = Vect3d(aabb.getMin());

        Triangle3d trianglePlane = Triangle3d(p1, p2, p3);

        Plane* plane = new Plane(p1, p2, p3, true);
        this->addNewModel((new DrawPlane(*plane))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());

        // 4. Pintar los triángulos que estén en el lado positivo de un color, los que
        // estén en el lado negativo en otro y los que crucen al plano en un
        // tercer color

        for (int i = 0; i < triangleModel->numTriangles(); i++) {
            Triangle3d triangle = triangleModel->getFace(i);
            Vect3d a = triangle.getA();
            Vect3d b = triangle.getB();
            Vect3d c = triangle.getC();

            Triangle3d::PointPosition position1 = trianglePlane.classify(a);
            Triangle3d::PointPosition position2 = trianglePlane.classify(b);
            Triangle3d::PointPosition position3 = trianglePlane.classify(c);

            if (position1 == Triangle3d::PointPosition::POSITIVE && position2 == Triangle3d::PointPosition::POSITIVE && position3 == Triangle3d::PointPosition::POSITIVE) {
				this->addNewModel((new DrawTriangle(triangle))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(1.0f, 0.0f, 0.0f, 1.0f))->overrideModelName());
			}
            else if (position1 == Triangle3d::PointPosition::NEGATIVE && position2 == Triangle3d::PointPosition::NEGATIVE && position3 == Triangle3d::PointPosition::NEGATIVE) {
				this->addNewModel((new DrawTriangle(triangle))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 1.0f, 0.0f, 1.0f))->overrideModelName());
			}
            else {
				this->addNewModel((new DrawTriangle(triangle))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 0.0f, 1.0f, 1.0f))->overrideModelName());
			}
        }

        delete plane;

    }

    // Práctica 3.b
    /* 
        5. Pintar la caja AABB del modelo.
        6. Crear una nube de puntos dentro de la AABB.
        7. Pintar de distinto color los puntos que quedan dentro/fuera del
        modelo. Medir los tiempos de cálculo para toda la nube.
    */

    if (Pr3 == 'b') {
		// 5. Pintar la caja AABB del modelo.
		TriangleModel* triangleModel = new TriangleModel("Assets/Models/Dog.obj");
		AABB aabb = triangleModel->getAABB();
		this->addNewModel((new DrawAABB(aabb))->overrideModelName());

		// 6. Crear una nube de puntos dentro de la AABB.
		PointCloud3d pointCloud(PointCloud3d(1000, 3));

		// 7. Pintar de distinto color los puntos que quedan dentro/fuera del
		// modelo. Medir los tiempos de cálculo para toda la nube.

        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < pointCloud.size(); i++) {
			Vect3d point = pointCloud.getPoint(i);
            if (triangleModel->pointIntoMesh(point)) {
				this->addNewModel((new DrawPoint(point))->setPointColor(vec4(1.0f, 0.0f, 0.0f, 1.0f))->setPointSize(3.0f)->overrideModelName());
			}
            else {
				this->addNewModel((new DrawPoint(point))->setPointColor(vec4(0.0f, 1.0f, 0.0f, 1.0f))->setPointSize(3.0f)->overrideModelName());
			}
		}
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float, std::milli> duration = end - start;

        std::cout << "Time: " << duration.count() << " ms" << std::endl;
	}

    // Práctica 3.c
    /*
        8. Lanzar un rayo aleatorio desde fuera de la caja y que intersecte con el
        modelo pintando de otro color los triángulos por donde cruza el rayo.
    */

    if (Pr3 == 'c') {
		TriangleModel* triangleModel = new TriangleModel("Assets/Models/Dog.obj");
		AABB aabb = triangleModel->getAABB();

		// 8. Lanzar un rayo aleatorio desde fuera de la caja y que intersecte con el
		// modelo pintando de otro color los triángulos por donde cruza el rayo.

		Vect3d origin = Vect3d(1.0f, 0.0f, 3.0f);
		Vect3d direction = Vect3d(0.0f, 0.0f, -1.0f);

		Ray3d ray = Ray3d(origin, direction);
        this->addNewModel((new DrawRay3D(ray))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName());

        std::vector<Vect3d> p;
        std::vector<Triangle3d> t;

        triangleModel->rayTraversalExh(ray, p, t);
        
        for (int i = 0; i < triangleModel->numTriangles(); i++) {
            bool found = false;
            Triangle3d triangle = triangleModel->getFace(i);
            for (int j = 0; j < t.size(); j++) {
                Vect3d pointA = t[j].getA();
                Vect3d pointB = t[j].getB();
                Vect3d pointC = t[j].getC();

                if ((triangle.getA().distance(pointA) < EPSILON && triangle.getB().distance(pointB) < EPSILON && triangle.getC().distance(pointC) < EPSILON)){
					this->addNewModel((new DrawTriangle(triangle))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(1.0f, 0.0f, 0.0f, 1.0f))->overrideModelName());
                    found = true;
                    break;
				}
		    }

            if(!found)
                this->addNewModel((new DrawTriangle(triangle))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->setTriangleColor(vec4(0.0f, 1.0f, 0.0f, 1.0f))->overrideModelName());
        }
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
