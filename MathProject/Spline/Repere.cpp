#include "Repere.h"


Repere::Repere()
{
    const float xAxis[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f
    };

    const unsigned short indices[] = {
        0,1,
        0,2
    };

    glGenBuffers(1, &repereXVBO);
    glBindBuffer(GL_ARRAY_BUFFER, repereXVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(xAxis), &xAxis, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &repereXEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereXEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * sizeof(indices), &indices, GL_STATIC_DRAW);

    const float zAxis[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f
    };

    glGenBuffers(1, &repereZVBO);
    glBindBuffer(GL_ARRAY_BUFFER, repereZVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(zAxis), &zAxis, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &repereZEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereZEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * sizeof(indices), &indices, GL_STATIC_DRAW);

    const float yAxis[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };

    glGenBuffers(1, &repereYVBO);
    glBindBuffer(GL_ARRAY_BUFFER, repereYVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(yAxis), &yAxis, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &repereYEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereYEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * sizeof(indices), &indices, GL_STATIC_DRAW);
}


void Repere::draw(GLuint program)
{
    if (!this->showRepere)
        return;
    glPointSize(5.0f);

    glBindBuffer(GL_ARRAY_BUFFER, repereXVBO);

    GLint positionLocationX = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocationX);
    glVertexAttribPointer(positionLocationX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    GLint colorLocationX = glGetUniformLocation(program, "u_color");
    glUniform4f(colorLocationX, this->xColor.RedValue, this->xColor.GreenValue, this->xColor.BlueValue, 1.0f);

    glDrawArrays(GL_POINTS, 0, 9);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereXEBO);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, nullptr);

    //Y
    glBindBuffer(GL_ARRAY_BUFFER, repereYVBO);

    GLint positionLocationY = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocationY);
    glVertexAttribPointer(positionLocationY, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    GLint colorLocationY = glGetUniformLocation(program, "u_color");
    glUniform4f(colorLocationY, this->yColor.RedValue, this->yColor.GreenValue, this->yColor.BlueValue, 1.0f);

    glDrawArrays(GL_POINTS, 0, 9);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereYEBO);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, nullptr);

    //Z
    glBindBuffer(GL_ARRAY_BUFFER, repereZVBO);

    GLint positionLocationZ = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocationZ);
    glVertexAttribPointer(positionLocationZ, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    GLint colorLocationZ = glGetUniformLocation(program, "u_color");
    glUniform4f(colorLocationZ, this->zColor.RedValue, this->zColor.GreenValue, this->zColor.BlueValue, 1.0f);

    glDrawArrays(GL_POINTS, 0, 9);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, repereZEBO);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, nullptr);
}

Repere::~Repere()
{
}
