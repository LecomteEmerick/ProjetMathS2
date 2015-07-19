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
    int selectedSplineIndex = 0;
    enum SplineManagerState {editPoint, addPoint};
    SplineManagerState currentState = SplineManagerState::addPoint;
    Spline* currentActiveSpline;
    std::vector<Spline*> SplineList;
    CustomColor ActiveColor = CustomColor(1.0, 0.0, 0.0);
    CustomColor DisableColor = CustomColor(0.0, 0.0, 1.0);
};

