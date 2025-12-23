#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>


// 4x^4 + 7x^3 - 4x + 14
float function1(float x)
{
	return (float) (4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}


// sin x - 7x + 8
float function2(float x)
{
	return (float)(sin(x) - 7 * x + 8);
}

float function3(float (*f)(float x), float *rResult)
{
	*rResult = f(2.5);
	return 0;
}

void main(void)
{

	float var = function1(2.5);

	//printf("%f\n", var);

	printf("%f\n", function1(2.5));
	
	float result = 0;
	float* pResult = &result;
	float (*pFunc)(float x) = &function1;

	function3(pFunc, pResult);

	printf("result is: %f\n", result);


	while (!_kbhit())
	{
		Sleep(1);
	}


}