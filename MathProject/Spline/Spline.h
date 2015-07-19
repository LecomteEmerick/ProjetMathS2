#pragma once

#include <vector>
#include <algorithm>
#include <ctime>

#include "Point.h"
#include "OpenGLInclude.h"
#include "CustomColor.h"

class Spline : public virtualOpenGl
{
public:
    CustomColor myColor;

    Spline();
    Point Spline::RandomPoint();
    Spline(int splineDegrees) {this->splineDegrees_ = splineDegrees;}
    //construction Function
    void construct();
    //getter setter
    std::vector<Point> getControlPoint(){ return this->controlPoint; }
    Point* SelectedPoint = nullptr;
    void AddControlPoint(Point p);
    void AddControlPoint(int x, int y);
    void setSplineDegrees(int value) { this->splineDegrees_ = value; }
    void tryGetPoint(Point p);
    void Spline::ChangeSelectedPointPos(Point p);
    std::vector<Point> getBSplinePoint() { return this->b_spline; }
    //
    void draw(GLuint program);
    //
    ~Spline() {  this->controlPoint.clear(); }
private:
    bool isIncludeForRendering = false;

    float Spline::DeBoor(int i, int degrees, float t, std::vector<float>& node);
    float Spline::DeBoorHelper(int i, int degrees, float t, std::vector<float>& node);
    int splineDegrees_;
    bool extrapoolExtremity = false;

    std::vector<Point> controlPoint;
    std::vector<Point> b_spline;

    void Spline::BindEbo(std::vector<unsigned short>& indices, std::vector<float>& vertex, GLuint& EBO, GLuint& VBO,std::vector<Point>& curve);
    float randFloat(float min, float max) {  return (min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)))); }

    bool renderSpline = false;
    std::vector<unsigned short> indicesSpline;
    std::vector<float> vertexSpline;
    GLuint splineEBO;
    GLuint splineVBO;

    bool renderRef = false;
    std::vector<unsigned short> indicesRefPoint;
    std::vector<float> vertexRefPoint;
    GLuint refPointEBO;
    GLuint refPointVBO;
};

