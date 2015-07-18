#include "ShapeManager.h"
#include "OpenGLRenderer.h"

ShapeManager::ShapeManager()
{
}

void ShapeManager::CreateShape()
{
    std::cout << "add shape" << std::endl;
    this->shapeList.push_back(new Shape());
    this->currentShape = this->shapeList.back();
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

void ShapeManager::SelectSpline(int index)
{

}

ShapeManager::~ShapeManager()
{
}
