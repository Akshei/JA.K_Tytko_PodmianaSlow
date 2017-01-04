.data
.code 

Func PROC

	ret
Func endp

asmFunction PROC
	cld
	push rdi ; save all non volatile registers
	push rsi
	push rbx
	push rbp
	push rsp
	push r12
	push r13
	push r14
	push r15
	push r10
	push r11
	mov r10, r8
	mov r11, r9
	mov r8, rcx
	mov r9, rdx
	; FINDING LEGTH OF ALL STRINGS #########################################################################################################
	
	mov rdi, r8	; rdi <- address of main string
	mov rcx, 0ffffffffffffffffh
	mov rax, 0
	repne scasb
	neg rcx
	dec rcx
	dec rcx
	mov r12,rcx ; length of main string

	mov rdi, r9	; rdi <- address of string to find
	mov rcx, 0ffffffffffffffffh
	mov rax, 0
	repne scasb
	neg rcx
	dec rcx
	dec rcx
	mov r13,rcx ; length of string to find

	mov rdi, r10	; rdi <- address of string to change to
	mov rcx, 0ffffffffffffffffh
	mov rax, 0
	repne scasb
	neg rcx
	dec rcx
	dec rcx
	mov r14,rcx ; length of string to change to

	; END FINDING LENGTH OF ALL STRINGS ###############################################################################################################
try_once_more:
	mov rax, [r9] ; rax <- substring to find
	movd xmm1, rax ; vector instruction! xmm1 <- substring to find

	pcmpistrm xmm1, [r8], 12 ; vector instruction!  which find substrings in string

	movd rax, xmm0 ; vector instruction! accumulator <- result
	mov rcx, rax
	mov rax, 1
	and rax, rcx

	jz przepisz_literke
	jmp wklej_stringa_R10

przepisz_literke:
	mov al,[r8]  ; al <- one letter from main string
	mov [r11], al ; result string <- one letter from al
	inc r8        ; increment pointer to main string
	inc r11		  ; increment pointer to result string
	jmp sprawdz_koniec

wklej_stringa_R10:
	mov rcx, r14
	mov rbx, r10
R10_loop:		
	mov al, [rbx]
	mov [r11], al
	inc rbx
	inc r11
	dec rcx
	jz increment_R8
	jmp R10_loop

increment_R8:
	mov rcx, r13
R8_loop:
	inc r8
	dec rcx
	jz sprawdz_koniec
	jmp R8_loop

sprawdz_koniec:
	cmp byte ptr [r8],0
	je lol
	jmp try_once_more

lol:
	pop r11
	pop r10
	pop r15
	pop r14
	pop r13
	pop r12
	pop rsp
	pop rbp
	pop rbx
	pop rsi
	pop rdi
	ret

asmFunction endp

end
