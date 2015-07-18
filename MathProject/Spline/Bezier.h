#pragma once
#include "Point.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include "virtualOpenGL.h"

class Bezier : public virtualOpenGl
{
public:
	Bezier();
	void computeCurve();
	void addPoint(int x, int y);
    void Bezier::tryGetPoint(Point p);
    void Bezier::ChangeSelectedPointPos(Point p);
	void createNewCurve();

    Point* SelectedPoint;
private:
	GLuint bezierEBO;
	GLuint bezierVBO;
	int step = 50.0;
	std::vector<float> pointsToDraw;
	std::vector<unsigned short> indicesToDraw;
	std::unique_ptr<std::vector<Point>> currentCurve;
	std::vector<std::unique_ptr<std::vector<Point>>> curvesHoriz;

	void createIndices();
	void Bezier::BindEbo();
	void draw(GLuint program);
	std::unique_ptr<std::vector<Point>> computeBezierCurve(std::vector<Point> curve, bool draw);
	Point getCasteljauPointIter(int r, int i, double t, std::vector<Point> points, bool draw);


};