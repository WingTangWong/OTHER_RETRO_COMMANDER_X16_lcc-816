
# -~x
# ~-x


# signed decrement.
reg: BCOMI2(NEGI2(reg)) {
	lda %0
	dec
	sta %c
} 3

# unsigned decrement
reg: BCOMU2(ADDU2(BCOMU2(reg), const_1)) {
	lda %0
	dec
	sta %c
} 3


# signed increment
reg: NEGI2(BCOMI2(reg)) {
	lda %0
	inc
	sta %c
} 3

# unsigned increment already optimized by lcc.

# signed -~a
reg: NEGI4(BCOMI4(reg)) {
	lda %0
	sec
	sbc #1
	sta %c
	lda %0+2
	sbc #0
	sta %c+2
} 7


reg: BCOMI4(NEGI4(reg)) {
	lda %0
	clc
	adc #1
	sta %c
	lda %0+2
	adc #0
	sta %c+2
} 7

reg: BCOMU4(ADDU4(BCOMU4(reg), const_1)) {
	lda %0
	sec
	sbc #1
	sta %c
	lda %0+2
	sbc #0
	sta %c+2
} 7
