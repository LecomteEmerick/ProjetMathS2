#pragma once
class Point
{
public:
    Point();
    Point(int x, int y){
        this->x_ = x; this->y_ = y;
    }
    void operator*(float f){ this->x_ *= f; this->y_ *= f; }
    float x_get() { return this->x_; }
    float y_get() { return this->y_; }
    ~Point();
private:
    int x_, y_;
};