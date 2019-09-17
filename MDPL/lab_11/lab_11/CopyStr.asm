.386
.model flat, c

public CopyStr

.code

CopyStr proc
        push    ebp
        mov     ebp, esp
        push    esi
        push    edi

        mov     esi, [ebp + 8]      ; s1 offset
        mov     edi, [ebp + 12]     ; s2 offset
        mov     ecx, [ebp + 16]     ; L

        inc     ecx                 ; with '\0'
        mov     eax, edi            ; s2 offset for return

        cmp     esi, edi
        jl      backward            ; s1 offset < s2 offset
        je      exit

    foward:
        cld
        jmp     copy

    backward:
        add     esi, ecx
        dec     esi
        add     edi, ecx
        dec     edi
        std

    copy:
        rep     movsb
        cld

    exit:
        pop     edi
        pop     esi
        pop     ebp
        ret
CopyStr endp

end
