#pragma once

typedef struct {
	float results[3];
	float accuracy[3];
} t_APP_RectangleResults;

typedef struct {
	float results[3];
	float accuracy[3];
} t_APP_TrapezoidResults;

typedef struct {
	float results[3];
	float accuracy[3];
} t_APP_SimpsonResults;

typedef struct {
	t_APP_RectangleResults rectangle;
	t_APP_TrapezoidResults trapezoid;
	t_APP_SimpsonResults simpson;
} t_APP_ContainerResults;

typedef struct {
	float resultRectangle;
	float resultTrapezoid;
	float resultSimpson;
} t_APP_SingleResult;

extern int APP_runTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[], const float *resultPolynomial, t_APP_ContainerResults* pDest);

extern int APP_runTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[], const float *resultTrigonometric, t_APP_ContainerResults* pDest);

extern int APP_calculateIntegral(const float (*function)(float x), float a, float b, unsigned short n, t_APP_SingleResult* pResult);