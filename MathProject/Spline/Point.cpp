#include "Point.h"


/*Point::Point(int x, int y)
{
    this->x_ = x; 
    this->y_ = y;

    static const std::vector<float> g_Point = { this->x_, this->y_, 1.0f };

    glGenBuffers(1, &PointVBO);
    glBindBuffer(GL_ARRAY_BUFFER, PointVBO);
    glBufferData(GL_ARRAY_BUFFER, g_Point.size() * sizeof(float), &g_Point.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Point::draw(GLuint program)
{
    std::cout << "draw point" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, PointVBO);

    GLint positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glDrawArrays(GL_POINTS, 0, 3);
}*/
