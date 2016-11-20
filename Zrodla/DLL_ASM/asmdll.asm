.code 

asmFunction PROC strToOper: PTR BYTE, strToChange: PTR BYTE, strIWant: PTR BYTE

	;mov rax,5
	;add rax,2
	kromka:
	mov rax, strToOper
	;PCMPEQB
	jmp kromka
	ret

asmFunction endp

end