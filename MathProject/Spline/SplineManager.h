#pragma once
#include <vector>
#include "Spline.h"

class SplineManager
{
public:
    SplineManager();
    void SplineManager::CreateSpline();
    void SplineManager::InputKey(unsigned char key);
    void SplineManager::InputMouse(int state, int x, int y);
    void SplineManager::SelectSpline(int index);
    Spline* SplineManager::GetCurrentSpline() { return this->currentActiveSpline; }
    ~SplineManager();
private:
    enum SplineManagerState {editPoint, addPoint};
    SplineManagerState currentState = SplineManagerState::addPoint;
    Spline* currentActiveSpline;
    std::vector<Spline*> SplineList;
};

