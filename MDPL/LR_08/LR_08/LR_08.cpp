#include "pch.h"
#include <stdio.h>

unsigned char m[8][8] = {
	"11111",
	"22222",
	"33333",
	"44444",
	"55555"
};

int main()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	///*
	__asm
	{
		MOV	EBX, 0
		MOV	ECX, 7

		LOOP1:
			MOV		ESI, EBX
			INC		ESI

			MOV		EDI, EBX
			ADD		EDI, 8

			MOV		EDX, ECX
			LOOP2:
				XCHG	AL, BYTE PTR m[EDI]
				XCHG	AL, BYTE PTR m[ESI]
				XCHG	AL, BYTE PTR m[EDI]

				INC		ESI
				ADD		EDI, 8

				LOOP 	LOOP2
			MOV		ECX, EDX

			ADD		EBX, 9

			DEC		ECX
			JNZ		LOOP1
	}
	//*/

	/*
	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			m[i][j] ^= m[j][i];
			m[j][i] ^= m[i][j];
			m[i][j] ^= m[j][i];
		}
	}
	//*/

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}