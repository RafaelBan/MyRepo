.386
.model Flat,C

public p1

.code
P1:
		PUSH	EBP
		MOV		EBP, ESP
		MOV		ECX, [EBP + 8]
		MOV		EBX, [EBP + 12]

		CMP		ECX, 1
		JLE		RET_1
		
		DEC		ECX

		PUSH	EBX
		PUSH	ECX
		CALL	P1
		ADD		ESP, 8

		INC		ECX
		MOV		EAX, DWORD PTR [EBX]
		MUL		ECX

		MOV		DWORD PTR [EBX], EAX
		JMP		EXIT

	RET_1:
		MOV		DWORD PTR [EBX], 1

	EXIT:
		POP		EBP
		RET		

END
