.386
.model FLAT,C
PUBLIC SetCler 

.CODE

SetCler:
	PUSH EBP
	MOV  EBP, ESP

	MOV  ECX, [EBP + 16]		; P
	MOV  EAX, [EBP + 12]		; N

	MOV  EBX, [EBP + 8]			; X

	M:
		CMP  ECX, 0
		JE     ZERO
		JMP  ONE

		ZERO:
			BTR  [EBX], EAX
			JMP  _EXIT
		ONE:
			BTS  [EBX], EAX

	_EXIT:
		POP  EBP
		RET




















SetCler_:
		PUSH	EBP
		MOV		EBP,ESP

		PUSH	ESI
  
		MOV		EAX, DWORD PTR[EBP+8]	; S

		MOV		ESI, 32
		MOV		ECX, DWORD PTR[EBP+12]
		SUB		ESI, ECX				; N
  
		CMP		DWORD PTR[EBP+16], 0	; P
		JNZ		PUT_1
		BTR		[EAX], ESI
		JMP		EXIT

	PUT_1:
		BTS		[EAX], ESI
  
	EXIT:
		POP		ESI

		POP		EBP
		RET

END