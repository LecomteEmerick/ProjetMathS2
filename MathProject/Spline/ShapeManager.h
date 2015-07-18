#pragma once
#include <vector>

#include "Shape.h"

class ShapeManager
{
public:
    ShapeManager();
    void ShapeManager::CreateShape();
    void ShapeManager::InputKey(unsigned char key);
    void ShapeManager::InputMouse(int state, int x, int y);
    void ShapeManager::SelectSpline(int index);
    Shape* ShapeManager::GetCurrentShape() { return this->currentShape; }
    ~ShapeManager();
private:
    enum ShapeManagerState { editPoint, addPoint };
    ShapeManagerState currentState = ShapeManagerState::addPoint;
    Shape* currentShape;
    std::vector<Shape*> shapeList;
};

