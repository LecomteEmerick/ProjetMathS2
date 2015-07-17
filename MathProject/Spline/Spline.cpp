#include "Spline.h"

Spline::Spline()
{
    this->splineDegrees_ = 3;
    this->controlPoint.push_back(Point(-5, -5, 1));
    this->controlPoint.push_back(Point(-5, 5, 1));
    this->controlPoint.push_back(Point(5, 5, 1));
    this->controlPoint.push_back(Point(5, -5, 1));
    //for (int i = 0; i < 10; i++)
        //this->controlPoint.push_back(this->RandomPoint());
    construct();
    this->BindEbo();
    OpenGLRenderer::AddElementToDraw(this);
}

Point Spline::RandomPoint()
{
    //srand(time(0));
    return Point(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10));
}

void Spline::BindEbo()
{
    this->vertex.clear();
    for (Point p : this->controlPoint)
    {
        vertex.push_back(p.x_get());
        vertex.push_back(p.y_get());
        vertex.push_back(p.z_get());
    }

    indices.clear();
    for (int i = 0; i < this->controlPoint.size(); i++)
    {
        if (i > 1)
            indices.push_back(i - 1);
        indices.push_back(i);
    }

    glGenBuffers(1, &splineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, splineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &splineEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, splineEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

void Spline::construct()
{
    std::vector<Point> tmp;
    int i = 0;
    for (Point p : this->controlPoint)
    {
        tmp.push_back(DeBoor(i, 3, p));
        i++;
    }
    this->controlPoint = tmp;
    /*initialisation n p S(point de controle) T(vecteur nodal)
    T a calculer pour application coox de boor
    coox de boor
    partition de l unité recalculer pour chaque segment les points intermédiaire pour lisser la courbe*/
}

Point Spline::DeBoor(int i, int degrees, Point t)
{
    if (this->splineDegrees_ == 0)
    {
        if (t == this->controlPoint.at(i))
            return t;
        return Point(0,0);
    }

    return ((t - this->controlPoint.at(i)) /
        (this->controlPoint.at(i + degrees) - this->controlPoint.at(i))) * this->DeBoor(i, degrees - 1, t) +
        ((this->controlPoint.at(i + degrees + 1) - t) /
        (this->controlPoint.at(i + degrees + 1) - this->controlPoint.at(i + 1))) * this->DeBoor(i + 1, degrees - 1, t);

}

void Spline::draw(GLuint program)
{
    std::cout << "draw spline" << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, splineVBO);

    GLint positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glDrawArrays(GL_POINTS, 0, this->controlPoint.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, splineEBO);
    glDrawElements(GL_LINES, this->indices.size(), GL_UNSIGNED_SHORT, nullptr);
}

/*Point Spline::DeBoorHelper(int i, int degrees, Point t)
{
    if (this->controlPoint.at(i) >= this->controlPoint.at(i + degrees)) 
        return Point(0,0);
    return (t - this->controlPoint.at(i)) / (this->controlPoint.at(i + degrees) - this->controlPoint.at(i)));
}*/
