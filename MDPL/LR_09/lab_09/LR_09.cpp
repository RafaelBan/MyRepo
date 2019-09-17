#include "pch.h"
#include <iostream>

extern "C" void p1(int N, int *h);

int N = 6, NF = 7;

int main()
{
	p1(N, &NF);

	printf("%d\n", NF);

	return 0;
}