#include "Spline.h"

//1. #include "OpenGLRenderer.h" et #include "virtualOpenGL.h" dans le .h (a implementer sur ta partie)
//2. class MaSuperClassPropre : public virtualOpenGl (a implementer sur ta partie)
//3. construire l'EBO et le VBO comme indiqué si dessous (a implementer sur ta partie)
//4. implémenter la classe draw (a implementer sur ta partie)
//5. OpenGLRenderer::AddElementToDraw(this);

Spline::Spline()
{
    this->splineDegrees_ = 3;
}

Point Spline::RandomPoint()
{
    return Point(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10));
}

void Spline::AddControlPoint(Point p) 
{ 
    this->controlPoint.push_back(p); 
    this->BindEbo(this->indicesRefPoint, this->vertexRefPoint, this->refPointEBO, this->refPointVBO, this->controlPoint); 
    this->renderRef = true; 
    if (renderSpline)
        construct();
}

void Spline::AddControlPoint(int x, int y) 
{ 
    this->controlPoint.push_back(Point(x, y)); 
    this->BindEbo(this->indicesRefPoint, this->vertexRefPoint, this->refPointEBO, this->refPointVBO, this->controlPoint);
    this->renderRef = true; 
    if (renderSpline)
        construct();
}

void Spline::tryGetPoint(Point p)
{
    Point* nearestPoint=nullptr;
    float dist;
    float mindist = FLT_MAX;
    for (int i = 0; i < this->controlPoint.size();i++)
    {
        dist = p.distance(this->controlPoint.at(i));
        if (dist < mindist)
        {
            nearestPoint = &this->controlPoint.at(i);
            mindist = dist;
        }
    }

    if (mindist < 0.5)
        this->SelectedPoint = nearestPoint;
}

void Spline::ChangeSelectedPointPos(Point p)
{
    this->SelectedPoint->x_set(p.x_get());
    this->SelectedPoint->y_set(p.y_get());
    this->SelectedPoint->z_set(p.z_get());
    this->BindEbo(this->indicesRefPoint, this->vertexRefPoint, this->refPointEBO, this->refPointVBO, this->controlPoint);
    this->renderRef = true;
    this->SelectedPoint = nullptr;
    if (renderSpline)
        construct();
}

//creation de l'objet OpenGL (a implementer sur ta partie)
void Spline::BindEbo(std::vector<unsigned short>& indices, std::vector<float>& vertex, GLuint& EBO, GLuint& VBO, std::vector<Point>& curve)
{
    vertex.clear();
    for (Point p : curve)
    {
        vertex.push_back(p.x_get());
        vertex.push_back(p.y_get());
        vertex.push_back(p.z_get());
    }

    indices.clear();
    for (int i = 0; i < curve.size(); i++)
    {
        if (i > 1)
            indices.push_back(i - 1);
        indices.push_back(i);
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

void Spline::construct()
{
    if (this->controlPoint.size() < this->splineDegrees_)
        return;

    float step = 5;
    std::vector<float> node;
    for (int i = 0; i < this->controlPoint.size() + this->splineDegrees_ + 1; ++i)
    {
        if (extrapoolExtremity && (i == 0 || i == this->controlPoint.size() + this->splineDegrees_))
        {
            for (int j = 0; j < this->splineDegrees_; ++j)
            {
                node.push_back(i);
            }
        }
        node.push_back(i);
    }

    std::vector<Point> tmp;

    for (int t = node.at(this->splineDegrees_); t < node.at(node.size() - this->splineDegrees_ - 1); ++t)
    {
        for (int k = 0; k < step; ++k)
        {
            Point tmpPoint(0,0);
            for (int i = 0; i < this->controlPoint.size(); i++)
            {
                Point p = this->controlPoint.at(i);
                tmpPoint += (p * DeBoor(i, this->splineDegrees_, t + (k / step), node));
            }
            tmp.push_back(tmpPoint);
        }
    }
    this->b_spline = tmp;
    this->BindEbo(this->indicesSpline, this->vertexSpline, this->splineEBO, this->splineVBO, this->b_spline);
    this->renderSpline = true;
}

float Spline::DeBoor(int i, int degrees, float t, std::vector<float>& node)
{
    if (degrees == 0)
    {
        if (t >= node.at(i) && t < node.at(i+1))
            return 1;
        return 0;
    }

    return this->DeBoorHelper(i,degrees,t,node) * this->DeBoor(i, degrees - 1, t, node) +
        (1-this->DeBoorHelper(i+1,degrees,t,node)) * this->DeBoor(i + 1, degrees - 1, t, node);

}

float Spline::DeBoorHelper(int i, int degrees, float t, std::vector<float>& node)
{
    if (node.at(i) >= node.at(i + degrees))
        return 0;
    return ((t - node.at(i)) / (node.at(i + degrees) - node.at(i)));
}

//fonction de dessin tu peux copier coller normalement si tu as bien fait les trucs avant (a implementer sur ta partie)
void Spline::draw(GLuint program)
{
    glPointSize(5.0f);

    if (this->renderRef && this->controlPoint.size() > 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, refPointVBO);

        GLint positionLocation = glGetAttribLocation(program, "a_position");
        glEnableVertexAttribArray(positionLocation);
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

        GLint colorLocation = glGetUniformLocation(program, "u_color");
        glUniform4f(colorLocation, this->myColor.RedValue, this->myColor.GreenValue, this->myColor.BlueValue, 1.0f);

        glDrawArrays(GL_POINTS, 0, this->controlPoint.size());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, refPointEBO);
        glDrawElements(GL_LINES, this->indicesRefPoint.size(), GL_UNSIGNED_SHORT, nullptr);
    }


    if (this->renderSpline && this->b_spline.size() > 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, splineVBO);

        GLint positionLocation = glGetAttribLocation(program, "a_position");
        glEnableVertexAttribArray(positionLocation);
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

        GLint colorLocation = glGetUniformLocation(program, "u_color");
        glUniform4f(colorLocation, this->myColor.RedValue, this->myColor.GreenValue, this->myColor.BlueValue, 1.0f);

        glDrawArrays(GL_POINTS, 0, this->b_spline.size());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, splineEBO);
        glDrawElements(GL_LINES, this->indicesSpline.size(), GL_UNSIGNED_SHORT, nullptr);
    }
}
