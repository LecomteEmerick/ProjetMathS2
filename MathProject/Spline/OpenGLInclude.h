#pragma once

#if _WIN32
#include <Windows.h>
#define FREEGLUT_LIB_PRAGMAS 0
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glu32.lib")
#endif

#define GLEW_STATIC 1
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common\EsgiShader.h"
#include "OpenGLHelper.h"
#include "OpenGLRenderer.h"