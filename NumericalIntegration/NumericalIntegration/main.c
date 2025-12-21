#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>


// 4x^4 + 7x^3 - 4x + 14
float function1(x)
{
	return (float) (4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}


// sin x - 7x + 8
float function2(x)
{
	return (float)(sin(x) - 7 * x + 8);
}

void main(void)
{

	float var = function1(5);

	printf("%f\n", var);

	printf("%f", function2(7));


	while (!_kbhit())
	{
		Sleep(1);
	}


}