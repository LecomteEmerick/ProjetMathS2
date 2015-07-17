#pragma once
#include <math.h>

class Point
{
public:
    Point(){}
    Point(float x, float y) : x_(x), y_(y), z_(1) {}
    Point(float x, float y, float z) : x_(x), y_(y), z_(z) {}
    Point operator*(float f){ return Point(this->x_ * f, this->y_ * f, this->z_ * f); }
    Point operator*(Point p){ return Point(this->x_ * p.x_, this->y_ * p.y_, this->z_ * p.z_); }
    Point operator+(Point p){ return Point(this->x_ + p.x_, this->y_ + p.y_, this->z_ + p.z_); }
    bool operator==(Point p){ if (this->x_ == p.x_ && this->y_ == p.y_ && this->z_ == p.z_) return true; return false; }
    Point operator-(Point p){ return Point(this->x_ - p.x_, this->y_ - p.y_, this->z_ - p.z_); }
    Point operator/(Point p){ return Point(this->x_ / p.x_, this->y_ / p.y_, this->z_ / p.z_); }
    bool operator>=(Point p){ return !(sqrt(this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_) < sqrt(p.x_ * p.x_ + p.y_ * p.y_ + this->z_ * this->z_));}
    float x_get() { return this->x_; }
    float y_get() { return this->y_; }
    void x_set(float newX) { this->x_ = newX; }
    void y_set(float newY) { this->y_ = newY; }
    float z_get() { return this->z_; }
    void z_set(float newZ) { this->z_ = newZ; }
    ~Point() {}
private:
    float x_, y_, z_;
};