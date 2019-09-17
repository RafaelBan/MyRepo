#include "pch.h"
#include <iostream>
#include <bitset>

extern "C" void P0(void);
extern "C" int A;
extern "C" int B;

extern "C" int D;
extern "C" int E;

extern "C" int S;
extern "C" int N1;
extern "C" int N2;
extern "C" int P1;
extern "C" int P2;

extern "C" int CNT_R;

int main()
{
	std::cout << "S: " << std::bitset<32>(S) << '\n';
	std::cout << "Set " << P1 << " on " << N1 << " bit" << '\n';
	std::cout << "Set " << P2 << " on " << N2 << " bit" << '\n';
	std::cout << '\n';

	std::cout << "A: " << std::bitset<32>(A) << " " << std::bitset<6>(*(&(A)+1)) << '\n';
	std::cout << "\\" << '\n';
	std::cout << "B: " << std::bitset<32>(B) << " " << std::bitset<6>(*(&(B)+1)) << '\n';
	std::cout << '\n';

	std::cout << "D: " << std::bitset<32>(D) << " " << std::bitset<6>(*(&(D)+1)) << '\n';
	std::cout << "u" << '\n';
	std::cout << "E: " << std::bitset<32>(E) << " " << std::bitset<6>(*(&(E)+1)) << '\n';
	std::cout << '\n';

	P0();

	std::cout << "S: " << std::bitset<32>(S) << '\n';
	std::cout << "A: " << std::bitset<32>(A) << " " << std::bitset<6>(*(&(A) + 1)) << '\n';
	std::cout << "A count: " << CNT_R << '\n';
	std::cout << "D: " << std::bitset<32>(D) << " " << std::bitset<6>(*(&(D)+1)) << '\n';
}
