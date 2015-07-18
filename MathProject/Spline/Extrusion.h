#pragma once
#include "Shape.h"
#include "Spline.h"

class Extrusion : public virtualOpenGl
{
public:
    Extrusion(Spline sp, Shape sh);
    void Extrude(Spline sp, Shape sh);
    void Extrusion::Bind();
    void Extrusion::draw(GLuint program);
    ~Extrusion();
private:
    std::vector<Point> extrusionPoint;
    //
    int shapeSize = 0;
    //
    std::vector<float> vertex;
    std::vector<unsigned short> indices;
    bool extrusionRender = false;
    GLuint extrusionEBO;
    GLuint extrusionVBO;
};

