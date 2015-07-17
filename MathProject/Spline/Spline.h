#pragma once

#include <vector>
#include <algorithm>
#include <ctime>
#include "Point.h"
#include "OpenGLInclude.h"

class Spline : public virtualOpenGl
{
public:
    Spline();
    Point Spline::RandomPoint();
    Spline(int splineDegrees) {this->splineDegrees_ = splineDegrees;}
    //construction Function
    void construct();
    //getter setter
    std::vector<Point> getControlPoint(){ return this->controlPoint; }
    void AddControlPoint(Point p) { this->controlPoint.push_back(p); this->BindEbo(); }
    void setSplineDegrees(int value) { this->splineDegrees_ = value; }
    //
    void draw(GLuint program);
    //
    ~Spline() {this->controlPoint.clear();}
private:
    Point DeBoor(int i, int degrees, Point t);
    double Spline::DeBoorHelper(int i, int degrees, Point t);
    int splineDegrees_;
    std::vector<Point> controlPoint;

    void Spline::BindEbo();

    float randFloat(float min, float max) {  return (min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)))); }

    std::vector<unsigned short> indices;
    std::vector<float> vertex;
    GLuint splineEBO;
    GLuint splineVBO;
};

