#include "ExtrusionManager.h"
#include "OpenGLRenderer.h"


ExtrusionManager::ExtrusionManager()
{
}

void ExtrusionManager::CreateExtrusion(Spline sp, Shape sh)
{
    this->extrusionList.push_back(new Extrusion(sp, sh));
    OpenGLRenderer::AddElementToDraw(this->extrusionList.back());
}


ExtrusionManager::~ExtrusionManager()
{
}
