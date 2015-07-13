// Specifique a Windows
#if _WIN32
#include <Windows.h>
#define FREEGLUT_LIB_PRAGMAS 0
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glu32.lib")
#endif

#define GLEW_STATIC 1
#include <GL/glew.h>

// FreeGLUT
#include "GL/freeglut.h"

#include <iostream> 
#include <vector>
#include "Spline.h"

std::vector<Point> points;

void InitializeOpenGl();
void Render();
void mouseClicks(int button, int state, int x, int y);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spline");

#ifdef FREEGLUT
    // Note: glutSetOption n'est disponible qu'avec freeGLUT
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    InitializeOpenGl();

    glutMouseFunc(mouseClicks);
    glutDisplayFunc(Render);

    glutMainLoop();

    return 0;
}

void InitializeOpenGl()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);
    for (auto point : points)
    {
        glVertex3f(point.x_get(), point.y_get(),-1);
    }
    glEnd();

    glutPostRedisplay();
    glFlush();
}

void mouseClicks(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        points.push_back(Point(x, y));
        glutPostRedisplay();
    }
}