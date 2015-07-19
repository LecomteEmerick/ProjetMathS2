#pragma once
#include "virtualOpenGL.h"
#include "CustomColor.h"

class Repere : public virtualOpenGl
{
public:
    bool showRepere = true;

    Repere();
    void draw(GLuint program);
    ~Repere();
private:
    GLuint repereXEBO;
    GLuint repereXVBO;

    GLuint repereYEBO;
    GLuint repereYVBO;

    GLuint repereZEBO;
    GLuint repereZVBO;

    CustomColor xColor = CustomColor(1.0, 0.0, 0.0);
    CustomColor yColor = CustomColor(0.0, 1.0, 0.0);
    CustomColor zColor = CustomColor(0.0, 0.0, 1.0);
};

