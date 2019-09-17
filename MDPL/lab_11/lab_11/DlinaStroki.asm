.386
.model flat, c

public DlinaStroki

.code

DlinaStroki proc
        push    ebp
        mov     ebp, esp
        push    edi

        mov     al, 0
        mov     ecx, -1
        mov     edi, [ebp + 8]

        repne   scasb

        add     ecx, 2
        neg     ecx
        mov     eax, ecx

        pop     edi
        pop     ebp
        ret	4
DlinaStroki endp

end
