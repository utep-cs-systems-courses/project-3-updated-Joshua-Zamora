	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)
	
	.text 		; jt is constants (in flash)
jt:	.word default	;  jt[0]
	.word option1	;  jt[1]
	.word option2	;  jt[2]
	.word option3	;  jt[3]
	.word option4	;  jt[4]

	.global state_advance
state_advance:

	sub #2, r1 		; make space for local var
	mov #0, 0(r1)		; move 0 into var (bool val for success)
	
	cmp #0, r12		; state < 0; signed comparison
	jl default
	
	cmp #5, r12		; state > 5; unsigned comparison
	jhs default
	
	add r12, r12
	mov jt(r12), r0

	;;;  switch table options
option1:
	add #1, 0(r1)
	call #buttonOneState
	jmp end
option2:
	add #1, 0(r1)
	call #buttonTwoState
	jmp end
option3:
	add #1, 0(r1)
	call #buttonThreeState
	jmp end
option4:
	mov #-40, r12		; offset var for buttonFour method
	call #buttonFourState
	add r12, 0(r1)
	jmp end
default:
	jmp end			; on default do not add 1
end:
	mov 0(r1), r12		;If val == 0 no cases were met
	add #2, r1
	pop r0         ; return

