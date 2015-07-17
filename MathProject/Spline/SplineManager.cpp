#include "SplineManager.h"
#include "OpenGLRenderer.h"

SplineManager::SplineManager()
{
}


void SplineManager::CreateSpline()
{
    std::cout << "add spline" << std::endl;
    this->currentActiveSpline = Spline();
    this->SplineList.push_back(this->currentActiveSpline);
    currentState = SplineManagerState::addPoint;
}

void SplineManager::InputKey(unsigned char key)
{
    switch (key)
    {
    case 'a':
        this->CreateSpline();
        break;
    case 'c':
        std::cout << "construct" << std::endl;
        this->currentActiveSpline.construct();
        break;
    }
}

void SplineManager::InputMouse(int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    if (this->currentState == SplineManagerState::addPoint)
    {
        std::cout << "add point" << std::endl;
        this->currentActiveSpline.AddControlPoint(OpenGLRenderer::ProjectMouseClick(x,y));
    }
}

void SplineManager::SelectSpline(int index)
{

}

SplineManager::~SplineManager()
{
}
