#pragma once

typedef struct {
	float results[3];
	float accuracy[3];
} t_TST_RectangleResults;

typedef struct {
	float results[3];
	float accuracy[3];
} t_TST_TrapezoidResults;

typedef struct {
	float results[3];
	float accuracy[3];
} t_TST_SimpsonResults;

typedef struct {
	t_TST_RectangleResults rect;
	t_TST_TrapezoidResults trap;
	t_TST_SimpsonResults simp;
} t_TST_Container;

extern int TST_runTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

extern int TST_runTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

extern int TST_getResults(t_TST_Container* resultsContainer);

static int TST_calculateIntegral(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

static int TST_calculateAccuracyPolynomial(void);

static int TST_calculateAccuracyTrigonometric(void);