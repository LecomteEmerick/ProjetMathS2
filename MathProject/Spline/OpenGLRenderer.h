#pragma once
#include <vector>
#include <algorithm>

#include "virtualOpenGL.h"
#include "SplineManager.h"

class OpenGLRenderer
{
public:
	OpenGLRenderer(int argc, char* argv[]);
	void Render();
	void MouseHandler(int button, int state, int x, int y);
	void MotionHandler(int x, int y);
	void KeyBoardHandler(unsigned char key, int x, int y);
	void MouseWheelHandler(int button, int dir, int x, int y);
	void IdleHandler();
	void StartDisplay();
    static void OpenGLRenderer::AddElementToDraw(virtualOpenGl* element) { elementToDraw.push_back(element); }
    static Point OpenGLRenderer::ProjectMouseClick(int x, int y);
	~OpenGLRenderer();
private:
    enum OpenGLRendererMode { EditMode, RenderMode };
    //
    void Initialize();
    void SwitchMode(OpenGLRendererMode mode);
    //
    SplineManager splineManager;
    OpenGLRendererMode currentMode = OpenGLRendererMode::RenderMode;
    static std::vector<virtualOpenGl*> elementToDraw;
	EsgiShader basicShader;
	GLdouble _angleY=0;
	GLdouble _angleX=0;
	float depth = -7.0f;
	bool dragAction;
};

