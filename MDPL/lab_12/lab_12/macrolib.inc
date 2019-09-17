swapb	macro	 x1, x2
	xchg 	al, x1
  xchg 	al, x2
  xchg	al, x1
endm

swapw 	macro 	x1, x2
  xchg 	ax, x1
  xchg 	ax, x2
  xchg 	ax, x1
endm

swapd 	macro 	x1, x2
  xchg 	eax, x1
  xchg 	eax, x2
  xchg 	eax, x1
endm

pushr macro rg:vararg

	for reg, <rg>
		ifidn <reg>, <f>
			pushf
		else
			push reg
    endif
  endm

endm   

popr macro rg:vararg

  local n
  n = 0

  for cur, <rg>
    n = n + 1
    @catstr(var, %n) textequ <cur>
  endm

  rept n
    value equ @catstr(var, %n)

    ifidn value, <f>
			popf
    else
      pop 	@catstr(var, %n)
    endif

    n = n - 1
  endm

endm

callfunc_cdecl macro t:req, name:req, par, reg

  local n
  n = 8

name:
  push 	ebp
  mov		ebp, esp
  pushr reg

  for p, <par>
    temp equ @catstr(<p>,< equ >, <[ebp + %n]>)
    temp
    n = n + 4
  endm
  
	jmp		@catstr(name, _enter)
	@catstr(name, _exit):

  popr	reg
  pop 	ebp

	ret
endm
