.386
.model flat,c

include macrolib.inc

public  adder
public  p0

.data

.code

callfunc_cdecl int, adder, <x, y>, <esi, edi, f>

adder_enter:
  mov   esi, x
  mov   edi, y

  add   esi, edi
  mov   eax, esi

	jmp adder_exit

p0 proc
	ret
p0 endp

end
