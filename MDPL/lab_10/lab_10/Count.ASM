.386
.model FLAT,C
PUBLIC Count

.CODE

Count:
		PUSH	EBP
		MOV		EBP,ESP

		PUSH	ESI

		MOV		ECX, DWORD PTR[EBP+12]	; L
		MOV		EBX, DWORD PTR[EBP+8]	; S
		MOV		EAX, 0

	SET_S:
		MOV		EDX, [EBX]
		ADD		EBX, 4
		MOV		ESI, 0

	M1:
		CMP		ESI, 32
		JE		SET_S

		BT		EDX, ESI
		JNC		SKIP_INC
		INC		EAX

	SKIP_INC:
		INC		ESI
		LOOP	M1
        
		POP		ESI

		POP		EBP
		RET

END