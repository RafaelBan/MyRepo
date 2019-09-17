.386
.model FLAT,C
PUBLIC A_u_B

.CODE

A_u_B:
		PUSH	EBP
		MOV		EBP,ESP
		PUSH	EDI
		PUSH	ESI
		PUSH	EBX
	
		MOV		EBX, [EBP + 8]
		MOV		ESI, [EBP + 12]
		MOV		EAX, [EBP + 16]
		MOV		ECX, 32
		MOV		EDX, 0
		DIV		ECX
		MOV		ECX, EAX
	
		CMP		EDX, 0
		JE		UNION_L
		INC		ECX
	
	UNION_L:	
		MOV		EDX, [ESI]
		OR		[EBX], EDX
		MOV		[ESI], EDX

		ADD		EBX, 4
		ADD		ESI, 4
		LOOP	UNION_L
	
		POP		EBX
		POP		ESI
		POP		EDI
		POP		EBP
	
		RET
















A_u_B_:
		PUSH EBP
		MOV  EBP, ESP
	
		MOV  EAX, [EBP + 8]		; A
		MOV  EBX, [EBP + 12]	; B
		MOV  ECX, [EBP + 16]	; L
		MOV  EDX, 0
	
		COMP:
			BT   [EBX], EDX
			JNC  E_COMP
		
			BTS  [EAX], EDX
	
		E_COMP:
			INC  EDX
			CMP  EDX, 32
			JNE  RE_COMP
		
			MOV  EDX, 0
			ADD  EAX, 4
			ADD  EBX, 4
	
		RE_COMP:
			LOOP COMP

	EXIT:
		POP  EBP
		RET

END