#include "OpenGLRenderer.h"

Point lastPoint;
OpenGLRenderer* g_currentInstance;
int previousTime = 0;
std::vector<virtualOpenGl*> OpenGLRenderer::elementToDraw = std::vector<virtualOpenGl*>();

void _drawCallback()
{
	g_currentInstance->Render();
}

void _mouseCallback(int button, int state, int x, int y)
{
	g_currentInstance->MouseHandler(button,state,x,y);
}

void _motionCallback(int x, int y)
{
	g_currentInstance->MotionHandler( x,  y);
}

void _mouseWheelCallback(int button, int dir, int x, int y)
{
	g_currentInstance->MouseWheelHandler(button, dir, x, y);
}

void _keypressCallback(unsigned char key, int x, int y)
{
	g_currentInstance->KeyBoardHandler(key, x, y);
}

OpenGLRenderer::OpenGLRenderer(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Math project");

#ifdef FREEGLUT
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	this->Initialize();

	g_currentInstance = this;
	//
	glutMouseWheelFunc(_mouseWheelCallback);
	glutMouseFunc(_mouseCallback);
	glutMotionFunc(_motionCallback);
	glutDisplayFunc(_drawCallback);
	glutKeyboardFunc(_keypressCallback);

    glutMainLoop();
}

void OpenGLRenderer::Initialize()
{
	GLenum error = glewInit();
	if (error != GL_NO_ERROR) {
		// TODO
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	basicShader.LoadVertexShader("basic.vs");
	basicShader.LoadFragmentShader("basic.fs");
	basicShader.Create();

	previousTime = glutGet(GLUT_ELAPSED_TIME);

    this->splineManager = SplineManager();

    depth = 10.0f * -2.0f  - 7.0f;
}

void OpenGLRenderer::Render()
{
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glClearColor(0.f, 0.f, 0.0f, 1.0f);
	glClearDepth(1.F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint program = basicShader.GetProgram();
	glUseProgram(program);

	float w = (float)glutGet(GLUT_WINDOW_WIDTH);
	float h = (float)glutGet(GLUT_WINDOW_HEIGHT);

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int delta = currentTime - previousTime;
	previousTime = currentTime;
	static float time = 1.f;
	time += delta / 1000.f;
	GLint timeLocation = glGetUniformLocation(program, "u_time");
	glUniform1f(timeLocation, time);

	float projection[16];
	OpenGLHelper::Perspective(projection, 45.f, w, h, 0.1f, 1000.f);
	GLint projLocation = glGetUniformLocation(program, "u_projectionMatrix");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, projection);

	float viewTransform[16];
	OpenGLHelper::Identity(viewTransform);
	viewTransform[14] = depth;
	GLint viewLocation = glGetUniformLocation(program, "u_viewMatrix");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewTransform);

	float worldTransform[16];
	OpenGLHelper::Identity(worldTransform);
	float worldTransform2[16];
	OpenGLHelper::Rotate(worldTransform2, worldTransform, _angleY, .0f, 1.0f, .0f);
    float worldTransform3[16];
    OpenGLHelper::Rotate(worldTransform3, worldTransform2, _angleX, 1.0f, .0f, .0f);
	GLint worldLocation = glGetUniformLocation(program, "u_worldMatrix");
	glUniformMatrix4fv(worldLocation, 1, GL_FALSE, worldTransform3);

	for (auto element : this->elementToDraw)
	{
		element->draw(program);
	}

	glUseProgram(0);

	glutSwapBuffers();
}

void OpenGLRenderer::MouseHandler(int button, int state, int x, int y)
{
    if (currentMode == OpenGLRendererMode::RenderMode)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            lastPoint.x_set(x);
            lastPoint.y_set(y);
            if (state == GLUT_DOWN)
                dragAction = true;
            else
                dragAction = false;
        }
    }
    else{
        this->splineManager.InputMouse(state, x, y);
    }
}

void OpenGLRenderer::SwitchMode(OpenGLRendererMode mode)
{
    currentMode = mode;
    switch (mode)
    {
        case OpenGLRendererMode::EditMode:
            std::cout << "Edit Mode" << std::endl;
            this->_angleX = 0;
            this->_angleY = 0;
            dragAction = false;
            break;
        case OpenGLRendererMode::RenderMode:
            std::cout << "RenderMode" << std::endl;
            break;
    }
    glutPostRedisplay();
}

void OpenGLRenderer::MotionHandler(int x, int y)
{
	if (dragAction)
	{
		double distanceX = x - lastPoint.x_get();
		_angleY += 0.2*distanceX;
        double distanceY = y - lastPoint.y_get();
        _angleX += 0.2*distanceY;
	}
	lastPoint.x_set(x);
	lastPoint.y_set(y);
	glutPostRedisplay();
}

void OpenGLRenderer::KeyBoardHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'm' :
        if (currentMode == OpenGLRendererMode::RenderMode)
            this->SwitchMode(OpenGLRendererMode::EditMode);
        else
            this->SwitchMode(OpenGLRendererMode::RenderMode);
        break;
    default:
        if (currentMode == OpenGLRendererMode::EditMode)
            this->splineManager.InputKey(key);
	}
    glutPostRedisplay();
}

void OpenGLRenderer::MouseWheelHandler(int button, int dir, int x, int y)
{
	depth += dir*2;
	glutPostRedisplay();
}

Point OpenGLRenderer::ProjectMouseClick(int x, int y)
{
    float matModelViewf[16], matProjectionf[16];
    int viewport[16];

    float w = (float)glutGet(GLUT_WINDOW_WIDTH);
    float h = (float)glutGet(GLUT_WINDOW_HEIGHT);
    OpenGLHelper::Perspective(matProjectionf, 45.f, w, h, 0.1f, 1000.f);

    OpenGLHelper::Identity(matModelViewf);
    matModelViewf[14] = g_currentInstance->depth;

    glGetIntegerv(GL_VIEWPORT, viewport);
    double winX = (double)x;
    double winY = viewport[3] - (double)y;

    float matProjection[16];
    OpenGLHelper::multiply(matProjection, matModelViewf, matProjectionf);
    CMatrix4x4 matInverse = matProjection.inverse();
    float in[4];
    float winZ = 1.0;
    in[0] = (2.0f*((float)(x - 0) / (w - 0))) - 1.0f,
        in[1] = 1.0f - (2.0f*((float)(y - 0) / (h - 0)));
    in[2] = 2.0* winZ - 1.0;
    in[3] = 1.0;

    float vIn[4] { in[0], in[1], in[2], in[3] };
    pos = vIn * matInverse;

    pos.w = 1.0 / pos.w;

    pos.x *= pos.w;
    pos.y *= pos.w;
    pos.z *= pos.w;

    return Point(0, 0);
}

OpenGLRenderer::~OpenGLRenderer()
{
}
