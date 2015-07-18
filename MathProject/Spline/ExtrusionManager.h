#pragma once
#include "Extrusion.h"

class ExtrusionManager
{
public:
    ExtrusionManager();
    void ExtrusionManager::CreateExtrusion(Spline sp, Shape sh);
    ~ExtrusionManager();
private:
    std::vector<Extrusion*> extrusionList;
};

