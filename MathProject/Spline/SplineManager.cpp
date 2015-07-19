#include "SplineManager.h"
#include "OpenGLRenderer.h"

SplineManager::SplineManager()
{
}


void SplineManager::CreateSpline()
{
    if (this->currentActiveSpline != nullptr)
        this->currentActiveSpline->myColor = DisableColor;
    this->currentActiveSpline = new Spline();
    this->currentActiveSpline->myColor = ActiveColor;
    OpenGLRenderer::AddElementToDraw(this->currentActiveSpline);
    this->SplineList.push_back(this->currentActiveSpline);
    selectedSplineIndex = this->SplineList.size() - 1;
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
        this->currentActiveSpline->construct();
        break;
    case 's':
        if (this->currentState == SplineManagerState::addPoint)
            this->currentState = SplineManagerState::editPoint;
        else
            this->currentState = SplineManagerState::addPoint;
        break;
    case '+':
        this->selectedSplineIndex++;
        this->selectedSplineIndex = this->selectedSplineIndex % this->SplineList.size();
        this->SelectSpline(this->selectedSplineIndex);
        break;
    case '-':
        this->selectedSplineIndex--;
        this->selectedSplineIndex = this->selectedSplineIndex % this->SplineList.size();
        this->SelectSpline(this->selectedSplineIndex);
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
        this->currentActiveSpline->AddControlPoint(OpenGLRenderer::ProjectMouseClick(x,y));
    }
    else{
        if (this->currentActiveSpline->SelectedPoint == nullptr)
            this->currentActiveSpline->tryGetPoint(OpenGLRenderer::ProjectMouseClick(x, y));
        else
            this->currentActiveSpline->ChangeSelectedPointPos(OpenGLRenderer::ProjectMouseClick(x, y));
    }
}

void SplineManager::SelectSpline(int index)
{
    this->currentState = SplineManagerState::editPoint;
    this->currentActiveSpline->myColor = DisableColor;
    this->currentActiveSpline = this->SplineList.at(index);
    this->currentActiveSpline->myColor = ActiveColor;
}

SplineManager::~SplineManager()
{
    for (Spline* s : this->SplineList)
        delete s;
}
