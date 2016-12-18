
.STACK 4096

.DATA
prompt1 BYTE    "str to searching in: ", 0
prompt2 BYTE    "word im looking for: ", 0
prompt3 BYTE    "word i will replace: ", 0
target  BYTE    80 DUP (?)
key     BYTE    80 DUP (?)
strSub  BYTE    80 DUP (?)
trgtLength  DWORD   ?
keyLength   DWORD   ?
lastPosn    DWORD   ?
strSubLen   DWORD   ?
resultLbl BYTE  "The new sentence is: ", 0

.code 

asmFunction PROC strToOper: PTR BYTE, strToChange: PTR BYTE, strIWant: PTR BYTE

	 push bp
	        push bp,sp
	        push ax
	        push di
	        push es
	        push ds
	        xor al,al
	    les di,[bp+4]
	    mov cx, 0xffff
	    xor al,al
	    repne SCAS
	    mov ax, 0xffff
	    sub ax, cx
	    dec ax
	    mov cx, ax
	        pop ds
	        pop es
	        pop di
	        pop ax
	        pop bp
start:
	    mov ax, message1
	    push ax
	    mov ax, message2   
	    push ax
	    call strlength
CompStr:
	        push cx
	    lds si, [bp+2]
	    les di, [bp+4]
	    repne CMPS
	    dec di
	    dec si
	    cmp si,0
	    je exit
	    mov ax,1
	        pop cx

SubComp:
	    repe CMPS
	    cmp cx,0
	    jne exit
	    mov ax,1
exit:
	    mov ax,0
	    mov ax, 0x4c00s

asmFunction endp

;end

_MainProc PROC
    input prompt1, target, 80   ;input target string
    lea eax, target             ;address of target
    push eax                    ;parameter
    call strlen                 ;strlen(target)
    add esp, 4                  ;remove parameter
    mov trgtLength, eax         ;save length of target
    input prompt2, key, 80      ;input key string
    lea eax, key                ;address of key
    push eax                    ;parameter
    call strlen                 ;strlen(key)
    add esp, 4                  ;remove parameter
    mov keyLength, eax          ;save length of key
    input prompt3, strSub, 80   ;input word to search for
            lea eax, strSub             ;address of key
    push eax                    ;parameter
    call strlen                 ;strlen(strSub)
    add esp, 4                  ;remove parameter
    mov strSubLen, eax          ;save length of key

    mov eax, trgtLength
    sub eax, keyLength
    inc eax                     ;trgtLength - keyLength +1
    mov lastPosn, eax
    cld                         ;Left to Right comparison
    mov eax, 1                  ;starting position

    whilePosn:
        cmp eax, lastPosn       ;position <= last_posn?
        jnle endWhilePosn       ;exit if past last position

        lea esi, target         ;address of target string
        add esi, eax            ;add position
        dec esi                 ;address of position to check
        lea edi, key            ;address of key
        mov ecx, keyLength      ;number of position to check
        repe cmpsb              ;check
        jz found                ;exit of success
        inc eax                 ;increment position
        jmp whilePosn           ;repeat

    endWhilePosn:
        output resultLbl, [esi] ;display new sentence
        jmp quit

    found:
        sub edi, keyLength
        mov ecx, strSubLen
        lea esi, strSub
        cld
        rep movsb
        inc eax
        jmp whilePosn

    quit:
        mov     eax, 0  ; exit with return code 0
        ret
_MainProc ENDP


strlen  PROC
push ebp                    ;establish stack frame
mov ebp, esp
push ebx                    ;save EBX
sub eax, eax                ;length := 0
mov ebx, [ebp+8]            ;address of string

whileChar:
cmp BYTE PTR [ebx], 0       ;null byte?
je endWhileChar             ;exit if so
inc eax                     ;increment length
inc ebx                     ;point at next character
jmp whileChar               ;repeat

endWhileChar:
pop ebx                     ;restore registers
pop ebp
ret
strlen  ENDP
END