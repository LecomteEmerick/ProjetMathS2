#pragma once
#include <iostream>

const double PI = 3.1415926535;
const double PI_UNDER_180 = 180.0f / PI;
const double PI_OVER_180 = PI / 180.0f;

class OpenGLHelper
{
public:
	static void Identity(float *matrix);
	static void Orthographic(float *matrix, float L, float R, float T, float B, float N, float F);
	static void Perspective(float *matrix, float FOV, float width, float height, float N, float F);
	static void Translate(float *matrix, float tx, float ty, float tz = 0.f);
	static void OpenGLHelper::Rotate(float *mr, float *m, float angle, float x, float y, float z);
private:
	static float* OpenGLHelper::multiply(float* c, float* aa, float* bb);
};

