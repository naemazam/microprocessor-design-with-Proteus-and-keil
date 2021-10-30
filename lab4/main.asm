;
; This code reads a keyboard consisting of 10 keys and displays corresponding
; number on a 7 segment display.
; Based on the 8051 microcontroller.


bounce equ 14h
next equ 32h
newkey equ 70h
flag equ 00h

org 0000h
orl TMOD, #00010001b
anl TMOD, #11111101b
mov dptr, #disp_7seg
sjmp getkey

disp_7seg:
	db 3fh ;0
	db 06h ;1
	db 5bh ;2
	db 4fh ;3
	db 66h ;4
	db 6dh ;5
	db 7dh ;6
	db 07h ;7
	db 7fh ;8
	db 6fh ;9

getkey:
	mov p1, #0ffh
	mov p3, #0ffh

scan:
	acall keydown
	jz scan
	acall convert
	jbc flag, scan
	mov newkey, a
	mov a, #bounce
	acall softime
	acall keydown
	jz scan
	acall convert

	jbc flag, scan
	cjne a, newkey, scan
	acall vendit

wait:
	acall keydown
	jnz wait
	mov a, #next
	acall softime
	acall keydown
	jnz wait
	sjmp scan

keydown:
	mov r0, p1
	mov a, p3
	orl a, #0f3h
	anl a, r0
	cpl a
	ret

convert:
	clr flag
	clr a
	mov r1, p1
	mov r3, p3
	orl 03h, #0f3h
	cjne r1, #0feh, one
	sjmp check3

one:
	inc a
	cjne r1, #0fdh, two
	sjmp check3

two:
	inc a
	cjne r1, #0fbh, three
	sjmp check3

three:
	inc a
	cjne r1, #0f7h, four
	sjmp check3

four:
	inc a
	cjne r1, #0efh, five
	sjmp check3

five:
	inc a
	cjne r1, #0dfh, six
	sjmp check3

six:
	inc a
	cjne r1, #0bfh, seven
	sjmp check3

seven:
	inc a
	cjne r1, #07fh, eight
	sjmp check3

eight:
	inc a
	cjne r3, #0fbh, nine
	jnb p3.3, bad
	sjmp good

nine:
	inc a
	cjne r3, #0f7h, bad

good:
	ret

check3:
	jnb p3.3, bad
	jnb p3.4, bad
	sjmp good

bad:
	setb flag
	ret

softime:
	mov TL0, #0CCh
	mov TH0, #0D4h
	setb TR0
	again:
		jnb TF0, again
	clr TR0
	clr TF0
	ret ;softime

vendit:
	movc a, @a+dptr
	cpl a ;common anode display
	mov p2, a
	ret

end
