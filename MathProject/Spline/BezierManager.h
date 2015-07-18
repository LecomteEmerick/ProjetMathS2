#pragma once
#include "Bezier.h"

class BezierManager
{
public:
    BezierManager();
    void BezierManager::CreateBezier();
    void BezierManager::InputKey(unsigned char key);
    void BezierManager::InputMouse(int state, int x, int y);
    void BezierManager::SelectBezier(int index);
    Bezier* BezierManager::GetCurrentBezier() { return this->currentBezier; }
    ~BezierManager();
private:
    enum BezierManagerState { editPoint, addPoint };
    BezierManagerState currentState = BezierManagerState::addPoint;
    Bezier* currentBezier;
    std::vector<Bezier*> bezierList;
};

