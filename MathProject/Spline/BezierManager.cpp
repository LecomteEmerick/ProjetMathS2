#include "BezierManager.h"
#include "OpenGLRenderer.h"

BezierManager::BezierManager()
{
}

void BezierManager::CreateBezier()
{
    if (this->currentBezier != nullptr)
        this->currentBezier->myColor = this->DisableColor;
    this->bezierList.push_back(new Bezier());
    this->currentBezier = this->bezierList.back();
    this->currentBezier->myColor = this->ActiveColor;
    OpenGLRenderer::AddElementToDraw(this->bezierList.back());
    currentState = BezierManagerState::addPoint;
}

void BezierManager::InputKey(unsigned char key)
{
    switch (key)
    {
    case 'a':
        this->CreateBezier();
        break;
    case 's':
        if (this->currentState == BezierManagerState::addPoint)
            this->currentState = BezierManagerState::editPoint;
        else
			this->currentState = BezierManagerState::addPoint;
		break;
	case 'c':
		this->currentBezier->computeCurve();
		break;
	case 'n':
		this->currentBezier->createNewCurve();
		break;
	case '9':
		this->currentBezier->upStep();
		break;
	case '3':
		this->currentBezier->downStep();
		break;
	case 'w':
		this->currentBezier->toggleWireframe();
		break;
    case '+':
        this->selectedBezierIndex--;
        this->selectedBezierIndex = this->selectedBezierIndex % this->bezierList.size();
        this->SelectBezier(this->selectedBezierIndex);
        break;
    case '-':
        this->selectedBezierIndex--;
        this->selectedBezierIndex = this->selectedBezierIndex % this->bezierList.size();
        this->SelectBezier(this->selectedBezierIndex);
        break;
    }
}

void BezierManager::InputMouse(int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    if (this->currentState == BezierManagerState::addPoint)
    {
        if (!waitForSecondeClick)
        {
            this->worldPoint = OpenGLRenderer::ProjectMouseClick(x, y);
            waitForSecondeClick = true;
            OpenGLRenderer::ForceSideView();
        }
        else{
            Point tmp = OpenGLRenderer::ProjectMouseClick(x, y);
            this->currentBezier->addPoint(worldPoint.x_get(), worldPoint.y_get(), tmp.x_get()); 
            waitForSecondeClick = false;
            OpenGLRenderer::ForceFrontView();
        }
    }
    else{
        if (this->currentBezier->SelectedPoint == nullptr)
            this->currentBezier->tryGetPoint(OpenGLRenderer::ProjectMouseClick(x, y));
        else
            this->currentBezier->ChangeSelectedPointPos(OpenGLRenderer::ProjectMouseClick(x, y));
    }
}

void BezierManager::SelectBezier(int index)
{
    this->currentState = BezierManagerState::editPoint;
    this->currentBezier->myColor = DisableColor;
    this->currentBezier = this->bezierList.at(index);
    this->currentBezier->myColor = ActiveColor;
}

BezierManager::~BezierManager()
{
    for (Bezier* b : this->bezierList)
        delete b;
}
