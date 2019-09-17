#include "pch.h"
#include <iostream>

#include <cstring>

extern "C" int DelProbel(char *s);
extern "C" int DlinaStroki(char *s);
extern "C" char *CopyStr(char *s1, char *s2, int L);

int main()
{
	int l1;
	char s1[100] = "    the best string            ";

	std::cout << "s1: |" << s1 << "|" << '\n';
	l1 = DelProbel(s1);
	std::cout << "s1: |" << s1 << "|" << '\n' << l1 << '\n' << '\n';

	return 0;
}
