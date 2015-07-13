#pragma once
#include <vector>
#include "Point.h"

class Spline
{
public:
    Spline() {this->splineDegrees_ = 3;}
    Spline(int splineDegrees) {this->splineDegrees_ = splineDegrees;}
    //construction Function
    void construct();
    //getter setter
    void setSplineDegrees(int value) { this->splineDegrees_ = 3; }
    void setControlPoint();
    ~Spline() {this->controlPoint.clear();}
private:
    int splineDegrees_;
    std::vector<Point> controlPoint;
};

