#include "Extrusion.h"


Extrusion::Extrusion(Spline sp, Shape sh)
{
    this->Extrude(sp, sh);
    this->Bind();
}

void Extrusion::Extrude(Spline sp, Shape sh)
{
    std::vector<Point> splinePoint = sp.getBSplinePoint();
    if (splinePoint.size() < 1 || sh.getShapePoint().size() < 3)
        return;

    this->extrusionPoint.clear();

    std::vector<Point*> shape = sh.BarycentreBase();
    this->shapeSize = shape.size();

    this->extrusionPoint.reserve(shape.size() * splinePoint.size());

    for (Point p : splinePoint)
    {
        for (Point* ps : shape)
        {
            Point tmp;
            tmp.x_set(p.x_get());
            tmp.y_set(p.y_get() + ps->y_get());
            tmp.z_set(p.x_get() + ps->x_get());
            this->extrusionPoint.push_back(tmp);
        }
    }
}

void Extrusion::Bind()
{
    vertex.clear();
    for (Point p : this->extrusionPoint)
    {
        vertex.push_back(p.x_get());
        vertex.push_back(p.y_get());
        vertex.push_back(p.z_get());
    }

    indices.clear();
    for (int i = 0; i < this->extrusionPoint.size() - this->shapeSize; i++)
    {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + shapeSize - 1);
        indices.push_back(i + 1);
        indices.push_back(i + shapeSize);
        indices.push_back(i + shapeSize - 1);
    }

    glGenBuffers(1, &extrusionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, extrusionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &extrusionEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, extrusionEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices.front(), GL_STATIC_DRAW);

    this->extrusionRender = true;
}

void Extrusion::draw(GLuint program)
{
    if (!extrusionRender || this->extrusionPoint.size() < 1)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, extrusionVBO);

    GLint positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glDrawArrays(GL_TRIANGLES, 0, this->extrusionPoint.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, extrusionEBO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, nullptr);
}

Extrusion::~Extrusion()
{
}
