#include "Bezier.h"
#include "OpenGLRenderer.h" 

Point Bezier::getCasteljauPointIter(int r, int i, double t, std::vector<Point> points, bool draw) {
	double* xTab = (double*)malloc(sizeof(double)*r*r);
	double* yTab = (double*)malloc(sizeof(double)*r*r);
	double* zTab = (double*)malloc(sizeof(double)*r*r);
	auto point = points.begin();
	int j = 0;
	while (point != points.end())
	{
		xTab[j] = (*point).x_get();
		yTab[j] = (*point).y_get();
		zTab[j] = (*point).z_get();
		j++;
		point++;
	}
	for (int i = 1; i < r; i++)
	{
		for (int j = 0; j < r - i; j++)
		{
			zTab[j + i*r] = t*zTab[(i - 1)*r + (j + 1)] + (1 - t)*zTab[(i - 1)*r + j];
			yTab[j + i*r] = t*yTab[(i - 1)*r + (j + 1)] + (1 - t)*yTab[(i - 1)*r + j];
			xTab[j + i*r] = t*xTab[(i - 1)*r + (j + 1)] + (1 - t)*xTab[(i - 1)*r + j];
		}
	}
	if (draw)
	{
		pointsToDraw.push_back(xTab[r*(r - 1)]);
		pointsToDraw.push_back(yTab[r*(r - 1)]);
		pointsToDraw.push_back(zTab[r*(r - 1)]);
		std::cout << xTab[r*(r - 1)] << " : " << yTab[r*(r - 1)] << " : " << zTab[r*(r - 1)] << std::endl;
	}
	Point p(xTab[r*(r - 1)], yTab[r*(r - 1)], zTab[r*(r - 1)]);
	free(zTab);
	free(yTab);
	free(xTab);
	return p;
}

void renderLite() {}

std::unique_ptr<std::vector<Point>> Bezier::computeBezierCurve(std::vector<Point> curve, bool draw)
{
	std::unique_ptr<std::vector<Point>> bezier = std::unique_ptr<std::vector<Point>>(new std::vector<Point>);
	for (int t = 0; t <= step; t += 1)
	{
		Point p = (getCasteljauPointIter(curve.size(), 0, (1.0 * t / step), curve, draw));
		bezier->push_back(Point(p.x_get(), p.y_get(), p.z_get()));
	}
	/*Point p = curve[curve.size() - 1];
	bezier->push_back(p);*/
	return bezier;
}


void Bezier::computeCurve()
{
	if (curvesHoriz.size() > 0)
	{
		std::vector<std::unique_ptr<std::vector<Point>>> bezierHoriz;
		auto curvesHorizIterator = curvesHoriz.begin();
		while (curvesHorizIterator != curvesHoriz.end())
		{
			bezierHoriz.push_back(std::move(computeBezierCurve(*(*curvesHorizIterator), false)));
			curvesHorizIterator++;
		}
		pointsToDraw.clear();
		//indicesToDraw.clear();
		for (int i = 0; i < step + 1; i++)
		{
			std::vector<Point> curve = std::vector<Point>();
			auto bezierHorizIterator = bezierHoriz.begin();
			while (bezierHorizIterator != bezierHoriz.end())
			{
				curve.push_back((*(*bezierHorizIterator)).at(i));
				bezierHorizIterator++;
			}
			computeBezierCurve(curve, true);
		}
		BindEbo();
	}
}
void Bezier::createIndices()
{
	int s = step + 1;
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			
			indicesToDraw.push_back(i + j*s); // LEFT DOWN
			indicesToDraw.push_back(i + (j + 1)*s); // RIGHT DOWN
			indicesToDraw.push_back(i + 1 + j*s); // LEFT UP
			
			indicesToDraw.push_back(i + (j + 1)*s); // RIGHT DOWN
			indicesToDraw.push_back(i + 1 + (j + 1)*s); // RIGHT UP
			indicesToDraw.push_back(i + 1 + j*s); // LEFT UP
		}
	}
}

void Bezier::BindEbo()
{
	glGenBuffers(1, &bezierVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* pointsToDraw.size(), &pointsToDraw.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &bezierEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* indicesToDraw.size(), &indicesToDraw.front(), GL_STATIC_DRAW);
}

void Bezier::draw(GLuint program)
{
	glPointSize(5.0f);
	if (this->pointsToDraw.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);

		GLint positionLocation = glGetAttribLocation(program, "a_position");
		glEnableVertexAttribArray(positionLocation);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 3, 0);

        GLint colorLocation = glGetUniformLocation(program, "u_color");
        glUniform4f(colorLocation, this->myColor.RedValue, this->myColor.GreenValue, this->myColor.BlueValue, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, pointsToDraw.size());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);
		glDrawElements(GL_TRIANGLES, this->indicesToDraw.size(), GL_UNSIGNED_SHORT, nullptr);
	}	
	if (this->controlPointsToDraw.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, controlVBO);

		GLint positionLocation = glGetAttribLocation(program, "a_position");
		glEnableVertexAttribArray(positionLocation);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 3, 0);

        GLint colorLocation = glGetUniformLocation(program, "u_color");
        glUniform4f(colorLocation, this->myColor.RedValue, this->myColor.GreenValue, this->myColor.BlueValue, 1.0f);

		glDrawArrays(GL_POINTS, 0, pointsToDraw.size());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, controlEBO);
		glDrawElements(GL_POINTS, this->indicesToDraw.size(), GL_UNSIGNED_SHORT, nullptr);
	}
}



void Bezier::bindControlPoints()
{
	glGenBuffers(1, &controlVBO);
	glBindBuffer(GL_ARRAY_BUFFER, controlVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* controlPointsToDraw.size(), &controlPointsToDraw.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &controlEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, controlEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* controlIndicesToDraw.size(), &controlIndicesToDraw.front(), GL_STATIC_DRAW);
}

Bezier::Bezier()
{
	//OpenGLRenderer::AddElementToDraw(this);
	curvesHoriz = std::vector<std::unique_ptr<std::vector<Point>>>();
	currentCurve = std::unique_ptr<std::vector<Point>>(new std::vector<Point>());
	pointsToDraw = std::vector<float>();
	indicesToDraw = std::vector<unsigned short>();
	controlPointsToDraw = std::vector<float>();
	controlIndicesToDraw = std::vector<unsigned short>();
	createIndices();
}

void Bezier::addPoint(int x, int y)
{
	//float z = -((rand() / 100) % 100);
	float z = 1.0f;
	currentCurve->push_back(Point(x, y, z));
	controlIndicesToDraw.push_back(controlPointsToDraw.size() / 3);
	controlPointsToDraw.push_back(x);
	controlPointsToDraw.push_back(y);
	controlPointsToDraw.push_back(z);
	bindControlPoints();
}

void Bezier::tryGetPoint(Point p)
{
    Point* nearestPoint = nullptr;
    float dist;
    float mindist = FLT_MAX;
    for (int i = 0; i < this->currentCurve->size(); i++)
    {
        dist = p.distance(this->currentCurve->at(i));
        if (dist < mindist)
        {
            nearestPoint = &this->currentCurve->at(i);
            mindist = dist;
        }
    }

    if (mindist < 0.5)
        this->SelectedPoint = nearestPoint;
}

void Bezier::ChangeSelectedPointPos(Point p)
{
    this->SelectedPoint->x_set(p.x_get());
    this->SelectedPoint->y_set(p.y_get());
    this->SelectedPoint->z_set(p.z_get());
    this->computeCurve();
    this->SelectedPoint = nullptr;
}

void Bezier::createNewCurve()
{
	this->curvesHoriz.push_back(std::move(this->currentCurve));
	this->currentCurve = std::unique_ptr<std::vector<Point>>(new std::vector<Point>);
}
