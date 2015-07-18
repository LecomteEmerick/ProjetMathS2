#pragma once
#include <vector>

#include "OpenGLInclude.h"
#include "Point.h"

class Shape : public virtualOpenGl
{
public:
    Point* SelectedPoint=nullptr;

    Shape();
    void Shape::AddPoint(Point p);
    void Shape::Compute();
    void Shape::tryGetPoint(Point p);
    void Shape::ChangeSelectedPointPos(Point p);
    Point Shape::Barycentre();
    std::vector<Point*> Shape::BarycentreBase();
    std::vector<Point> getShapePoint() { return this->ShapePoint; }
    void Shape::draw(GLuint program);
    ~Shape();
private:
    Point barycentrePoint;

    std::vector<Point> ShapePoint;

    std::vector<float> vertex;
    std::vector<unsigned short> indices;
    bool shapeRender = false;
    GLuint shapeEBO;
    GLuint shapeVBO;
};

