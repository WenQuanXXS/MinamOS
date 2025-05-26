global context_switch
context_switch:
    ; 参数: [esp+4] old, [esp+8] new

    pushfd
    pushad

    mov eax, [esp + 36]     ; old context 指针
    mov [eax + 0x00], eax   ; eax
    mov [eax + 0x04], ebx
    mov [eax + 0x08], ecx
    mov [eax + 0x0C], edx
    mov [eax + 0x10], esi
    mov [eax + 0x14], edi
    mov [eax + 0x18], ebp
    lea edx, [esp + 40]     ; esp
    mov [eax + 0x1C], edx
    mov edx, [esp + 44]     ; eip
    mov [eax + 0x20], edx
    mov edx, [esp]          ; eflags
    mov [eax + 0x24], edx

    popad
    popfd

    mov eax, [esp + 8]      ; new context 指针

    mov esp, [eax + 0x1C]
    push dword [eax + 0x24]
    popfd
    mov eax, [eax + 0x00]
    mov ebx, [eax + 0x04]
    mov ecx, [eax + 0x08]
    mov edx, [eax + 0x0C]
    mov esi, [eax + 0x10]
    mov edi, [eax + 0x14]
    mov ebp, [eax + 0x18]
    push dword [eax + 0x20] ; eip
    ret