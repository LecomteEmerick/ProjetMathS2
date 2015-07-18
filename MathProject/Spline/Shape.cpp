#include "Shape.h"


Shape::Shape()
{
}


void Shape::AddPoint(Point p)
{
    this->ShapePoint.push_back(p);
    this->Compute();
    this->barycentrePoint = this->Barycentre();
}

void Shape::Compute()
{
    vertex.clear();
    for (Point p : this->ShapePoint)
    {
        vertex.push_back(p.x_get());
        vertex.push_back(p.y_get());
        vertex.push_back(p.z_get());
    }

    indices.clear();
    for (int i = 0; i < this->ShapePoint.size(); i++)
    {
        if (i > 1)
            indices.push_back(i - 1);
        indices.push_back(i);
    }
    if (this->ShapePoint.size() > 2)
    {
        indices.push_back(this->ShapePoint.size() - 1);
        indices.push_back(0);
    }
    glGenBuffers(1, &shapeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &shapeEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices.front(), GL_STATIC_DRAW);

    this->shapeRender = true;
}

void Shape::tryGetPoint(Point p)
{
    Point* nearestPoint = nullptr;
    float dist;
    float mindist = FLT_MAX;
    for (int i = 0; i < this->ShapePoint.size(); i++)
    {
        dist = p.distance(this->ShapePoint.at(i));
        if (dist < mindist)
        {
            nearestPoint = &this->ShapePoint.at(i);
            mindist = dist;
        }
    }

    if (mindist < 0.5)
        this->SelectedPoint = nearestPoint;
}

void Shape::ChangeSelectedPointPos(Point p)
{
    this->SelectedPoint->x_set(p.x_get());
    this->SelectedPoint->y_set(p.y_get());
    this->SelectedPoint->z_set(p.z_get());
    this->Compute();
    this->shapeRender = true;
    this->SelectedPoint = nullptr;
}

Point Shape::Barycentre()
{
    Point barycentre(0, 0);
    for (Point p : this->ShapePoint)
    {
        barycentre += p;
    }
    barycentre /= (float)this->ShapePoint.size();
    return barycentre;
}

std::vector<Point*> Shape::BarycentreBase()
{
    std::vector<Point*> basePoint;
    this->barycentrePoint = this->Barycentre();
    for (Point p : this->ShapePoint)
    {
        basePoint.push_back(new Point(p - this->barycentrePoint));
    }
    return basePoint;
}

void Shape::draw(GLuint program)
{
    if (!shapeRender || this->ShapePoint.size() < 1)
        return;

    glPointSize(5.0f);

    glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);

    GLint positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glDrawArrays(GL_POINTS, 0, this->ShapePoint.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeEBO);
    glDrawElements(GL_LINES, this->indices.size(), GL_UNSIGNED_SHORT, nullptr);
}

Shape::~Shape()
{
}
