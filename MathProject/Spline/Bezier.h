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
	void upStep();
	void downStep();
	void toggleWireframe();

    Point* SelectedPoint;
private:
	int step = 2;
	bool wireframe;
	std::unique_ptr<std::vector<Point>> currentCurve;
	std::vector<std::unique_ptr<std::vector<Point>>> curvesHoriz;
	std::vector<float> pointsToDraw;
	std::vector<unsigned short> indicesToDraw;
	std::vector<unsigned short> wireframeIndicesToDraw;
	std::vector<float> controlPointsToDraw;
	std::vector<unsigned short> controlIndicesToDraw;
	GLuint bezierEBO;
	GLuint bezierWireFrameEBO;
	GLuint bezierVBO;
	GLuint controlEBO;
	GLuint controlVBO; 

	void bindControlPoints();
	void createIndices();
	void Bezier::BindEbo();
	void Bezier::BindVbo();
	void draw(GLuint program);
	std::unique_ptr<std::vector<Point>> computeBezierCurve(std::vector<Point> curve, bool draw);
	Point getCasteljauPointIter(int r, int i, double t, std::vector<Point> points, bool draw);


};