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
    void ShapeManager::SelectShape(int index);
    Shape* ShapeManager::GetCurrentShape() { return this->currentShape; }
    ~ShapeManager();
private:
    enum ShapeManagerState { editPoint, addPoint };

    int selectedShapeIndex = 0;

    CustomColor ActiveColor = CustomColor(1.0, 0.0, 0.0);
    CustomColor DisableColor = CustomColor(0.0, 1.0, 0.0);

    ShapeManagerState currentState = ShapeManagerState::addPoint;
    Shape* currentShape;
    std::vector<Shape*> shapeList;
};

