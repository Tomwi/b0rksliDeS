/*
Copyright 2010-2012 Tomwi
*/

	.text
@*********************************************************************************
	.global t_copyRow
	.type t_copyRow, %function
@*********************************************************************************
	.align 2
	.arm
@---------------------------------------------------------------------------------
@ This function will draw a row of 33 tiles taking the given position of
@ the map into account
@ r0 = bginf
@ r1 = tilex
@ r2 = tiley
@---------------------------------------------------------------------------------
t_copyRow:

	stmfd	sp!, {r4,r5}				
	mov r5, r3
	ldr		r3,[r0]				@ src
	ldr 	r4,[r0, #8]			@ mapwidth
	ldr		r0,[r0, #4]				@ dst
	
	lsl		ip, r1, #6				 	@ bit(5) = 2048 (blocksize)
	
	@ calculate src starting index
	mla		r1, r2, r4, r1			
	add		r1, r3, r1, lsl #1		
	
	mov		r2, r2, lsl #27				@ x %= 32
	add		r0, r0, r2, lsr #(26-5)		@ += x*64
	
	
.rowloop:

	ldrh	r3, [r1], #2
	and 	r4, ip, #(1<<11)			@ extract first/second block
	orr 	r3, ip, lsl #21				@ tilex %= 32, store in r3 hi (lo is mapval)
	orr		r4, r4, r3, lsr #26			@ 
	strh	r3, [r0, r4]			
	
	add		ip, ip, # (1 << 6)		
	subs	r5, r5, #1
	bne		.rowloop
		
	ldmfd	sp!, {r4,r5}
	bx		lr


	
@*********************************************************************************
	.global t_copyColumn
	.type t_copyColumn, %function
@*********************************************************************************
	.align 2
	.arm
@---------------------------------------------------------------------------------
@ This function will draw a column of 25 tiles taking the given position of
@ the map into account
@ r0 = bginf
@ r1 = tilex
@ r2 = tiley
@---------------------------------------------------------------------------------
t_copyColumn:

	stmfd	sp!, {r4}		
	
	ldr		r3, [r0]			@ tileMap
	ldr		ip, [r0, #8]			@ mapWidth
	ldr		r0, [r0, #4]			@ screenBase	
	
  @ src pointer
	mla		r4, r2, ip, r1		
	add		r3, r3, r4, lsl #1		
	
	movs	r1, r1, lsl #27		
	add		r0, r0, r1, lsr #26		
	addcs	r0, r0, #0x800			
	mov		r2, r2, lsl #27			
	
	
	mov		r4, #25							
	mov		r2, r2, lsr #(21)				
	mov		ip, ip, lsl #1					
	
.columnLoop:

	ldrh	r1, [r3], ip				
	and		r2, r2, #(31<<(5+1))			
	strh	r1, [r0, r2]
	
	add		r2, r2, #1<<(5+1)			
	subs	r4, r4, #1
	bne		.columnLoop
	
	ldmfd	sp!, {r4}
	bx lr
	



