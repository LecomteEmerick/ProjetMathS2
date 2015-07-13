#include "OpenGLHelper.h"


void OpenGLHelper::Identity(float *matrix)
{
	memset(matrix, 0, sizeof(float)* 16);
	matrix[0] = 1.0f; matrix[5] = 1.0f; matrix[10] = 1.0f; matrix[15] = 1.0f;
}

void OpenGLHelper::Orthographic(float *matrix, float L, float R, float T, float B, float N, float F)
{
	memset(matrix, 0, sizeof(float)* 16);
	matrix[0] = 2.f / (R - L);
	matrix[5] = 2.f / (T - B);
	matrix[10] = -2.f / (F - N);
	matrix[12] = -(R + L) / (R - L);
	matrix[13] = -(T + B) / (T - B);
	matrix[14] = -(F + N) / (F - N);
	matrix[15] = 1.f;
}

void OpenGLHelper::Perspective(float *matrix, float FOV, float width, float height, float N, float F)
{
	memset(matrix, 0, sizeof(float)* 16);
	float aspect = width / height;

	float xymax = N * tan(FOV * (3.141592f / 180.f) * 0.5f);
	float ymin = -xymax;
	float xmin = -xymax;
	width = xymax - xmin;
	height = xymax - ymin;
	float depth = F - N;
	float q = -(F + N) / depth;
	float qn = -2.0f * (F*N) / depth;

	float w = 2.0f * N / width;
	w = w / aspect;
	float h = 2.0f * N / height;

	matrix[0] = w;
	matrix[5] = h;
	matrix[10] = q;
	matrix[11] = -1.f;
	matrix[14] = qn;
}

void OpenGLHelper::Translate(float *matrix, float tx, float ty, float tz)
{
	memset(matrix, 0, sizeof(float)* 16);
	matrix[0] = 1.f;
	matrix[5] = 1.f;
	matrix[10] = 1.f;
	matrix[12] = tx;
	matrix[13] = ty;
	matrix[14] = tz;
	matrix[15] = 1.f;
}

void OpenGLHelper::Rotate(float *matrixReturn, float *matrix, float angle, float x, float y, float z)
{
	float a = angle*PI_OVER_180;
	float m2[16] = { 0 };

	float c = cos(a);
	float s = sin(a);

	float xx = x*x,
		yy = y*y,
		zz = z*z;


	m2[0] = xx + (1.0f - xx)*c;
	m2[4] = (1.0f - c)*x*y - s*z;
	m2[8] = (1.0f - c)*x*z + s*y;
	m2[3] = 0.0f;

	m2[1] = (1.0f - c)*y*x + s*z;
	m2[5] = yy + (1.0f - yy)*c;
	m2[9] = (1.0f - c)*y*z - s*x;
	m2[7] = 0.0f;

	m2[2] = (1.0f - c)*z*x - s*y;
	m2[6] = (1.0f - c)*z*y + s*x;
	m2[10] = zz + (1.0f - zz)*c;
	m2[11] = 0.0f;

	m2[12] = 0;
	m2[13] = 0;
	m2[14] = 0;
	m2[15] = 1.0f;

	multiply(matrixReturn, matrix, m2);
}

float* OpenGLHelper::multiply(float* c, float* aa, float* bb)
{
	for (int i = 0; i < 4; i++)
	{
		c[i * 4] = bb[i * 4] * aa[0] + bb[i * 4 + 1] * aa[4] + bb[i * 4 + 2] * aa[8] + bb[i * 4 + 3] * aa[12];
		c[i * 4 + 1] = bb[i * 4] * aa[1] + bb[i * 4 + 1] * aa[5] + bb[i * 4 + 2] * aa[9] + bb[i * 4 + 3] * aa[13];
		c[i * 4 + 2] = bb[i * 4] * aa[2] + bb[i * 4 + 1] * aa[6] + bb[i * 4 + 2] * aa[10] + bb[i * 4 + 3] * aa[14];
		c[i * 4 + 3] = bb[i * 4] * aa[3] + bb[i * 4 + 1] * aa[7] + bb[i * 4 + 2] * aa[11] + bb[i * 4 + 3] * aa[15];
	}
	return c;
}
