#include "ShapeManager.h"
#include "OpenGLRenderer.h"

ShapeManager::ShapeManager()
{
}

void ShapeManager::CreateShape()
{
    if (this->currentShape != nullptr)
        this->currentShape->myColor = DisableColor;
    this->shapeList.push_back(new Shape());
    this->currentShape = this->shapeList.back();
    this->currentShape->myColor = ActiveColor;
    OpenGLRenderer::AddElementToDraw(this->shapeList.back());
    currentState = ShapeManagerState::addPoint;
}

void ShapeManager::InputKey(unsigned char key)
{
    switch (key)
    {
        case 'a':
            this->CreateShape();
            break;
        case 's':
            if (this->currentState == ShapeManagerState::addPoint)
                this->currentState = ShapeManagerState::editPoint;
            else
                this->currentState = ShapeManagerState::addPoint;
            break;
        case '+':
            this->selectedShapeIndex++;
            this->selectedShapeIndex = this->selectedShapeIndex % this->shapeList.size();
            this->SelectShape(this->selectedShapeIndex);
            break;
        case '-':
            this->selectedShapeIndex--;
            this->selectedShapeIndex = this->selectedShapeIndex % this->shapeList.size();
            this->SelectShape(this->selectedShapeIndex);
            break;
    }
}

void ShapeManager::InputMouse(int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    if (this->currentState == ShapeManagerState::addPoint)
    {
        std::cout << "add point" << std::endl;
        this->currentShape->AddPoint(OpenGLRenderer::ProjectMouseClick(x, y));
    }
    else{
        if (this->currentShape->SelectedPoint == nullptr)
            this->currentShape->tryGetPoint(OpenGLRenderer::ProjectMouseClick(x, y));
        else
            this->currentShape->ChangeSelectedPointPos(OpenGLRenderer::ProjectMouseClick(x, y));
    }
}

void ShapeManager::SelectShape(int index)
{
    this->currentState = ShapeManagerState::editPoint;
    this->currentShape->myColor = DisableColor;
    this->currentShape = this->shapeList.at(index);
    this->currentShape->myColor = ActiveColor;
}

ShapeManager::~ShapeManager()
{
    for (Shape* s : this->shapeList)
        delete s;
}
