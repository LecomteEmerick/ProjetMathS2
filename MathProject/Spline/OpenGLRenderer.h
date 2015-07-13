#pragma once
#include "virtualOpenGL.h"
#include "Point.h"

#include <vector>

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
	void AddElementToDraw(virtualOpenGl* element) { elementToDraw.push_back(element); }
	~OpenGLRenderer();
private:
	void Initialize();
	std::vector<virtualOpenGl*> elementToDraw;
	GLuint terrainVBO;
	GLuint terrainEBO;
	EsgiShader basicShader;
	GLdouble _angleY;
	GLdouble _angleX;
	float depth = -7.0f;
	bool dragAction;
	bool isPaused;
	bool isStepByStep;
};

