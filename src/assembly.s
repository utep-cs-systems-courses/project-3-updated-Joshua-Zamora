	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)
	
	.text 		; jt is constants (in flash)
jt:	.word default	;  jt[0]
	.word option1	;  jt[1]
	.word option2	;  jt[2]
	.word option3	;  jt[3]
	.word option4	;  jt[4]

	.global setButtonPress
setButtonPress:
	sub #2, r1
	mov.b #1, 0(r1)

	bis.b #0x20, &P1OUT 	; green led on

	cmp.b #2, 0(r1)
	jz skipTwo
	
        ;;;  range check on selector (state)
	cmp #5, r12	; state-5 doesn't borrow if s>4
	jhs default	
	cmp #-1, r12
	jz default

	add r12, r12
	mov jt(r12), r0

	;;;  switch table options
	;;;  same order as in source code
option4:
	call #buttonFourState
	jmp end
option3:
	call #buttonThreeState
	jmp end
option1:
	mov #1, r12
	call #buttonOneState
	mov r12, 0(r1)
	jmp end
option2:
	call #buttonTwoState
	jmp end	; break

default:
	jmp end
end:
skipTwo:
	bic.b #0x20, &P1OUT 	;green led off
	
	mov #1, r12
	add #2, r1
	pop r0         ; return

