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
    // Elegir entre ejercicio 1A y 1B
    bool exercise1A = false;
    if (exercise1A)
    {
		// Ejercicio 1A	
        int dim_X = 3, dim_Y = 2;

        // Dibujar una nube de 100 puntos
        PointCloud* pointCloud = new PointCloud(100, dim_X, dim_Y);
        this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
        pointCloud->save("pointCloud.txt");

        // Dibujar un segmento azul entre 2 puntos aleatorios de la nube
        SegmentLine* segment = new SegmentLine(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)], pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
	    this->addNewModel((new DrawSegment(*segment))->setLineColor(vec4(.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
    
        // Dibujar una recta roja entre 2 puntos aleatorios de la nube
        Line* line = new Line(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)], pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
        this->addNewModel((new DrawLine(*line))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
    
        // Dibujar un rayo magenta entre 2 puntos aleatorios de la nube
        RayLine* ray = new RayLine(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)], pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
        this->addNewModel((new DrawRay(*ray))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

        delete ray;
        delete line;
        delete segment;

    
        // Dibujar un poligono con los puntos más cercanos a las esquinas de la nube
        Polygon* polygon = new Polygon;
        Point p1(dim_X, -dim_Y);
        Point p2(dim_X, dim_Y);
        Point p3(-dim_X, dim_Y);
        Point p4(-dim_X, -dim_Y);

        polygon->add(pointCloud->centralPoint(p1));
        polygon->add(pointCloud->centralPoint(p2));
        polygon->add(pointCloud->centralPoint(p3));
        polygon->add(pointCloud->centralPoint(p4));
        this->addNewModel((new DrawPolygon(*polygon))->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f))->overrideModelName());

        delete polygon;

        // Dibujar un poligono con los puntos de mayor/menos ascisa/ordenada de la nube
        Point minPoint_x = pointCloud->minAbscissa();
        Point minPoint_y = pointCloud->minOrdinate();
        Point maxPoint_x = pointCloud->maxAbscissa();
        Point maxPoint_y = pointCloud->maxOrdinate();

        Polygon* polygon2 = new Polygon;
        polygon2->add(minPoint_y);
        polygon2->add(maxPoint_x);
        polygon2->add(maxPoint_y);
        polygon2->add(minPoint_x);
        this->addNewModel((new DrawPolygon(*polygon2))->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f))->overrideModelName());

        delete polygon2;

    
        // Dibujar una curva de Bezier con los puntos de la nube
        Bezier* bezier = new Bezier(pointCloud->getPoints()[0], pointCloud->getPoints()[1], pointCloud->getPoints()[2], pointCloud->getPoints()[3]);
        this->addNewModel((new DrawBezier(*bezier))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
        delete bezier;
    

        delete pointCloud;
    }
    else
    {
        
        // Ejercicio 1B
        float dim_X = 2.5, dim_Y = 1.75;

        // Dibujar una nube de 100 puntos
        PointCloud* pointCloud = new PointCloud(100, dim_X, dim_Y);
        //this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
        pointCloud->save("pointCloud.txt");

        // Intersección entre segmento y recta
        if (false) {
            Vect2d p1 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p2 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            SegmentLine* segment = new SegmentLine(p1, p2);
            this->addNewModel((new DrawSegment(*segment))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

            // Comprobar la intersección con la recta
            // Dos puntos aleatorios de la nube y pasarlos a vect2d
            Vect2d p3 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p4 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Line* line = new Line(p3, p4);
            this->addNewModel((new DrawLine(*line))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

            Vect2d res;
            // Dibujar el punto de intersección
            if (segment->intersects(*line, res)) {
                Point intersection3 = Point(res.getX(), res.getY());
                this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
            }
            delete line;
            delete segment;
        }

        // Intersección entre segmento y rayo
        if (false) {
            Vect2d p1 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p2 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            SegmentLine* segment = new SegmentLine(p1, p2);
            this->addNewModel((new DrawSegment(*segment))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

            // Comprobar la intersección con la recta
            // Dos puntos aleatorios de la nube y pasarlos a vect2d
            Vect2d p3 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p4 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            RayLine* ray = new RayLine(p3, p4);
			this->addNewModel((new DrawRay(*ray))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

            Vect2d res;
            // Dibujar el punto de intersección
            if (segment->intersects(*ray, res)) {
                Point intersection3 = Point(res.getX(), res.getY());
                this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
            }
            delete ray;
            delete segment;
        }

        // Intersección entre 2 segmentos
        if (false) {
            // Dibujar un segmento azul entre 2 puntos aleatorios de la nube
            Vect2d p1 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p2 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            SegmentLine* segment = new SegmentLine(p1, p2);
            this->addNewModel((new DrawSegment(*segment))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));


            float s, t;
            // Dos puntos aleatorios de la nube y pasarlos a vect2d
            Vect2d p3 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            Vect2d p4 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
            segment->intersects(p3, p4, s, t);

            // Dibujar el segmento de p1 a p2
            SegmentLine* segment2 = new SegmentLine(p3, p4);
            this->addNewModel((new DrawSegment(*segment2))->setLineColor(vec4(1.0f, 1.0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));


            Vect2d res;
            if (segment->intersects(*segment2, res))
            {
                Point intersection3 = Point(res.getX(), res.getY());
				this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
			}

            delete segment;
            delete segment2;
        }

        // Distancia entre punto y segmento
        if (false) {
            Vect2d p1 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
			Vect2d p2 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
			SegmentLine* segment = new SegmentLine(p1, p2);
			this->addNewModel((new DrawSegment(*segment))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

			// Comprobar la distancia entre el punto y el segmento
			Vect2d p3 = Vect2d(pointCloud->getPoints()[RandomUtilities::getUniformRandom(0, pointCloud->getPoints().size() - 1)]);
			double distance = segment->distPointSegment(p3);

            // Dibujar el punto
			Point intersection3 = Point(p3.getX(), p3.getY());
			this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));

            // Dibujar la recta que une el punto con el punto de intersección
            std::cout << "Distance: " << distance << std::endl;

			delete segment;
        }
        delete pointCloud;

        /*
        1. Definir un conjunto de dos segmentos (S1 y S2), dos rayos (R1 y R2), dos
           rectas (L1 y L2) y un polígono (P1) de manera que haya las siguientes
           intersecciones (no más): L1-L2, S1-S2, S1-R1, L1-P, R2-P. Pintar el punto de
           intersección en todos los casos.
        */
        SegmentLine* segment1 = new SegmentLine(Vect2d(0.5, -0.3), Vect2d(-2.0, -2.0));
        SegmentLine* segment2 = new SegmentLine(Vect2d(-1.4, -1.3), Vect2d(1.0, -1.0));
        RayLine* ray1 = new RayLine(Vect2d(.0, -0.4), Vect2d(2.0, -.4));
        RayLine* ray2 = new RayLine(Vect2d(-1.0, 1.0), Vect2d(-2.0, 1.5));
        Line* line1 = new Line(Vect2d(.0, .0), Vect2d(2.0, 1.0));
        Line* line2 = new Line(Vect2d(0.0, 0.0), Vect2d(.35, .25));
        Polygon* polygon = new Polygon;
        // Añaadir los vertices del poligono
        Vect2d vertices[5];
        vertices[0] = Vect2d(-1.3, 1.5);
        vertices[1] = Vect2d(-2.5, .75);
        vertices[2] = Vect2d(-2.0, -1.2);
        vertices[3] = Vect2d(-.2, .4);
        vertices[4] = Vect2d(-.3, 1.0);

        for (int i = 0; i < 5; i++)
            polygon->add(vertices[i]);

        // S1 Rojo, S2 Azul, R1 Magenta, R2 Cyan, L1 Amarillo, L2 Verde, P1 Naranja
        this->addNewModel((new DrawSegment(*segment1))->setLineColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawSegment(*segment2))->setLineColor(vec4(.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawRay(*ray1))->setLineColor(vec4(1.0f, .0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawRay(*ray2))->setLineColor(vec4(.0f, 1.0f, 1.0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawLine(*line1))->setLineColor(vec4(.0f, 1.0f, .0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawLine(*line2))->setLineColor(vec4(1.0f, 1.0f, .0f, 1.0f))->overrideModelName()->setLineWidth(1.0f));
        this->addNewModel((new DrawPolygon(*polygon))->setTriangleColor(vec4(1.0f, .5f, .0f, 1.0f))->overrideModelName());

        Vect2d res;
        if (segment1->intersects(*segment2, res))
        {
			Point intersection3 = Point(res.getX(), res.getY());
			this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
		}
        if (segment1->intersects(*ray1, res))
        {
            Point intersection3 = Point(res.getX(), res.getY());
            this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
        }
        if (line1->intersects(*line2, res))
        {
			Point intersection3 = Point(res.getX(), res.getY());
			this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
		}
        if (polygon->intersects(*line1, res))
		{ 
   			Point intersection3 = Point(res.getX(), res.getY());
            this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
        }
        if (polygon->intersects(*ray2, res))
        {
			Point intersection3 = Point(res.getX(), res.getY());
			this->addNewModel((new DrawPoint(intersection3))->setPointColor(vec4(1.0f, .0f, .0f, 1.0f))->overrideModelName()->setPointSize(10.0f));
		}

        /*
            2. Calcular las distancias entre cada punto del polígono y S1, S2, R1, R2, L1 y L2.
        */
        for (int i = 0; i < 5; i++)
        {
			std::cout << "\n\nDistance between point " << i + 1 << " and S1: " << segment1->distPointSegment(polygon->getVertexAt(i)) << std::endl;
			std::cout << "Distance between point " << i + 1 << " and S2: " << segment2->distPointSegment(polygon->getVertexAt(i)) << std::endl;
			std::cout << "Distance between point " << i + 1 << " and R1: " << ray1->distanceToPoint(polygon->getVertexAt(i)) << std::endl;
            std::cout << "Distance between point " << i + 1 << " and R2: " << ray2->distanceToPoint(polygon->getVertexAt(i)) << std::endl;
            std::cout << "Distance between point " << i + 1 << " and L1: " << line1->distancePointLine(polygon->getVertexAt(i)) << std::endl;
            std::cout << "Distance between point " << i + 1 << " and L2: " << line2->distancePointLine(polygon->getVertexAt(i)) << std::endl;
		}

        delete segment1;
		delete segment2;
		delete ray1;
		delete ray2;
		delete line1;
		delete line2;
		delete polygon;
    }
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

