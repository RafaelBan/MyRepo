#include "pch.h"
#include <iostream>

extern "C" int adder(int x, int y);
extern "C" void p0();

int main(int argc, char **argv)
{
	std::cout << adder(1, 5);

	return 0;
}
