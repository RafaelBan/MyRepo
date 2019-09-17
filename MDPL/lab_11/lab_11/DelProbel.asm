.386
.model flat, c

public  DelProbel
extern  DlinaStroki: near
extern  CopyStr: near

.code

DelProbel proc
        push    ebp
        mov     ebp, esp
        push    esi
        push    edi
        push    ebx

        mov     ebx, [ebp + 8]

        push    ebx
        call    DlinaStroki
        add     esp, 4

        cmp     eax, 0
        je      exit

        mov     ecx, -1
        mov     edi, ebx
        add     edi, eax
        mov     al, ' '
        sub     edi, 2      ; without '\0'
        std

        repe    scasb
        cld
        add     edi, 2
        mov     byte ptr [edi], 0

        mov     edx, edi
        ;sub     edx, ebx

        mov     ecx, -1
        mov     al, ' '
        mov     edi, ebx

        repe    scasb
        dec     edi

        mov     eax, edi
        ;sub     eax, ebx
        sub     edx, eax

        push    edx
        push    ebx
        push    edi
        call    CopyStr
        add     esp, 8
        pop     eax

    exit:
        pop     ebx
        pop     edi
        pop     esi
        pop     ebp
        ret
DelProbel endp

end
