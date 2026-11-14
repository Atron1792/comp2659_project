;; File Name: raster.s
;; Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky
;; 
;; Implements framebuffer clearing, primitive drawing, bitmap plotting,
;; and font rendering routines in Assembly 68000
;; 
	text
	even
_clearScreen:
	link	a6,#-2
	move.l	d3,-(a7)
	moveq	#0,d3
	bra	L2
L1:
	ext.l	d3
	move.l	d3,d0
	asl.l	#2,d0
	move.l	d0,a0
	move.l	8(a6),d0
	add.l	d0,a0
	clr.l	(a0)
L4:
	addq.w	#1,d3
L2:
	cmp.w	#8000,d3
	blt	L1
L3:
	move.l	(a7)+,d3
	unlk	a6
	rts
_clearRegion:
	link	a6,#-10
	movem.l	d3/d4,-(a7)
	move.l	8(a6),-8(a6)
	move.w	12(a6),d4
	bra	L6
L5:
	move.w	14(a6),d3
	bra	L10
L9:
	tst.w	d4
	blt	L13
	cmp.w	#400,d4
	bge	L13
	tst.w	d3
	blt	L13
	cmp.w	#640,d3
	bge	L13
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-9(a6)
	move.l	-8(a6),a0
	move.w	d4,d0
	muls	#80,d0
	ext.l	d0
	add.l	d0,a0
	move.w	d3,d0
	asr.w	#3,d0
	ext.l	d0
	add.l	d0,a0
	clr.w	d0
	move.b	-9(a6),d0
	not.w	d0
	and.b	d0,(a0)
L13:
L12:
	addq.w	#1,d3
L10:
	move.w	14(a6),d0
	add.w	18(a6),d0
	cmp.w	d0,d3
	bcs	L9
L11:
L8:
	addq.w	#1,d4
L6:
	move.w	12(a6),d0
	add.w	16(a6),d0
	cmp.w	d0,d4
	bcs	L5
L7:
	movem.l	(a7)+,d3/d4
	unlk	a6
	rts
_plotPixel:
	link	a6,#0
	movem.l	d3/d4,-(a7)
	move.w	14(a6),d3
	move.w	12(a6),d4
	tst.w	d3
	blt	L14
	cmp.w	#640,d3
	bge	L14
	tst.w	d4
	blt	L14
	cmp.w	#400,d4
	bge	L14
	move.l	8(a6),a0
	move.w	d4,d0
	muls	#80,d0
	ext.l	d0
	add.l	d0,a0
	move.w	d3,d0
	asr.w	#3,d0
	ext.l	d0
	add.l	d0,a0
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	or.b	d0,(a0)
L14:
	movem.l	(a7)+,d3/d4
	unlk	a6
	rts
_plotHorizontalLine:
	link	a6,#-10
	movem.l	d3/d4/d5,-(a7)
	move.w	12(a6),d5
	move.l	8(a6),-4(a6)
	tst.w	d5
	blt	L16
	cmp.w	#400,d5
	blt	L15
L16:
	bra	L17
L15:
	moveq	#0,d4
	bra	L19
L18:
	move.w	14(a6),d0
	add.w	d4,d0
	move.w	d0,d3
	blt	L22
	cmp.w	#640,d3
	bge	L22
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.l	-4(a6),a0
	move.w	d5,d0
	muls	#80,d0
	ext.l	d0
	add.l	d0,a0
	move.w	d3,d0
	asr.w	#3,d0
	ext.l	d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L22:
L21:
	addq.w	#1,d4
L19:
	cmp.w	16(a6),d4
	bcs	L18
L20:
L17:
	movem.l	(a7)+,d3/d4/d5
	unlk	a6
	rts
_plotVerticalLine:
	link	a6,#-10
	movem.l	d3/d4/d5,-(a7)
	move.w	14(a6),d3
	move.l	8(a6),-4(a6)
	moveq	#0,d5
	bra	L24
L23:
	move.w	12(a6),d0
	add.w	d5,d0
	move.w	d0,d4
	blt	L27
	cmp.w	#400,d4
	bge	L27
	tst.w	d3
	blt	L27
	cmp.w	#640,d3
	bge	L27
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.l	-4(a6),a0
	move.w	d4,d0
	muls	#80,d0
	ext.l	d0
	add.l	d0,a0
	move.w	d3,d0
	asr.w	#3,d0
	ext.l	d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L27:
L26:
	addq.w	#1,d5
L24:
	cmp.w	16(a6),d5
	bcs	L23
L25:
	movem.l	(a7)+,d3/d4/d5
	unlk	a6
	rts
_plotLine:
	link	a6,#-22
	movem.l	d3/d4/d5/d6/d7/a3/a4/a5,-(a7)
	move.l	8(a6),-4(a6)
	move.w	16(a6),d0
	sub.w	12(a6),d0
	move.w	d0,d5
	move.w	18(a6),d0
	sub.w	14(a6),d0
	move.w	d0,d4
	tst.w	d5
	bge	L28
	move.w	d5,d0
	neg.w	d0
	move.w	d0,d5
	move.w	#-1,a5
	bra	L29
L28:
	move.w	#1,a5
L29:
	tst.w	d4
	bge	L30
	move.w	d4,d0
	neg.w	d0
	move.w	d0,d4
	move.w	#-1,a4
	bra	L31
L30:
	move.w	#1,a4
L31:
	move.w	d4,d0
	sub.w	d5,d0
	move.w	d0,d7
	move.w	12(a6),d6
	move.w	14(a6),d3
	bra	L33
L32:
	tst.w	d6
	blt	L35
	cmp.w	#400,d6
	bge	L35
	tst.w	d3
	blt	L35
	cmp.w	#640,d3
	bge	L35
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.w	d6,d0
	muls	#80,d0
	move.w	d3,d1
	asr.w	#3,d1
	add.w	d1,d0
	move.w	d0,a0
	move.l	-4(a6),d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L35:
	cmp.w	16(a6),d6
	bne	L36
	cmp.w	18(a6),d3
	beq	L34
L36:
	move.w	d7,d0
	add.w	d0,d0
	move.w	d0,a3
	move.w	d5,d0
	neg.w	d0
	cmp.w	d0,a3
	ble	L37
	sub.w	d5,d7
	move.w	a4,d0
	add.w	d0,d3
L37:
	cmp.w	a3,d4
	ble	L38
	add.w	d4,d7
	move.w	a5,d0
	add.w	d0,d6
L38:
L33:
	bra	L32
L34:
	movem.l	(a7)+,d3/d4/d5/d6/d7/a3/a4/a5
	unlk	a6
	rts
_plotRectangle:
	link	a6,#-10
	movem.l	d3/d4,-(a7)
	move.l	8(a6),-4(a6)
	move.w	12(a6),d4
	bra	L40
L39:
	move.w	14(a6),d3
	bra	L44
L43:
	tst.w	d4
	blt	L47
	cmp.w	#400,d4
	bge	L47
	tst.w	d3
	blt	L47
	cmp.w	#640,d3
	bge	L47
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.w	d4,d0
	muls	#80,d0
	move.w	d3,d1
	asr.w	#3,d1
	add.w	d1,d0
	move.w	d0,a0
	move.l	-4(a6),d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L47:
L46:
	addq.w	#1,d3
L44:
	move.w	14(a6),d0
	add.w	18(a6),d0
	cmp.w	d0,d3
	blt	L43
L45:
L42:
	addq.w	#1,d4
L40:
	move.w	12(a6),d0
	add.w	16(a6),d0
	cmp.w	d0,d4
	blt	L39
L41:
	movem.l	(a7)+,d3/d4
	unlk	a6
	rts
_plotSquare:
	link	a6,#-10
	movem.l	d3/d4,-(a7)
	move.l	8(a6),-4(a6)
	move.w	12(a6),d4
	bra	L49
L48:
	move.w	14(a6),d3
	bra	L53
L52:
	tst.w	d4
	blt	L56
	cmp.w	#400,d4
	bge	L56
	tst.w	d3
	blt	L56
	cmp.w	#640,d3
	bge	L56
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.w	d4,d0
	muls	#80,d0
	move.w	d3,d1
	asr.w	#3,d1
	add.w	d1,d0
	move.w	d0,a0
	move.l	-4(a6),d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L56:
L55:
	addq.w	#1,d3
L53:
	move.w	14(a6),d0
	add.w	16(a6),d0
	cmp.w	d0,d3
	blt	L52
L54:
L51:
	addq.w	#1,d4
L49:
	move.w	12(a6),d0
	add.w	16(a6),d0
	cmp.w	d0,d4
	blt	L48
L50:
	movem.l	(a7)+,d3/d4
	unlk	a6
	rts
_plotTriangle:
	link	a6,#-18
	movem.l	d3/d4/d5/d6/d7/a3/a4/a5,-(a7)
	move.w	18(a6),d4
	move.b	21(a6),d5
	move.l	8(a6),-4(a6)
	tst.w	d4
	beq	L58
	tst.w	16(a6)
	bne	L57
L58:
	bra	L59
L57:
	moveq	#0,d3
	bra	L61
L60:
	tst.b	d5
	beq	L65
	cmp.b	#1,d5
	bne	L64
L65:
	moveq	#1,d0
	add.w	d3,d0
	mulu	16(a6),d0
	add.w	d4,d0
	subq.w	#1,d0
	and.l	#65535,d0
	divu	d4,d0
	move.w	d0,a4
	bra	L66
L64:
	move.w	16(a6),d0
	move.w	d4,d1
	sub.w	d3,d1
	mulu	d1,d0
	add.w	d4,d0
	subq.w	#1,d0
	and.l	#65535,d0
	divu	d4,d0
	move.w	d0,a4
L66:
	tst.b	d5
	beq	L68
	cmp.b	#2,d5
	bne	L67
L68:
	move.w	14(a6),a5
	bra	L69
L67:
	move.w	14(a6),d0
	sub.w	a4,d0
	addq.w	#1,d0
	move.w	d0,a5
L69:
	tst.b	d5
	beq	L71
	cmp.b	#1,d5
	bne	L70
L71:
	move.w	12(a6),d0
	add.w	d3,d0
	move.w	d0,d7
	bra	L72
L70:
	move.w	12(a6),d0
	sub.w	d3,d0
	move.w	d0,d7
L72:
	sub.l	a3,a3
	bra	L74
L73:
	move.w	a5,d0
	add.w	a3,d0
	move.w	d0,d6
	tst.w	d7
	blt	L77
	cmp.w	#400,d7
	bge	L77
	tst.w	d6
	blt	L77
	cmp.w	#640,d6
	bge	L77
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d6,d2
	sub.w	d2,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	move.w	d7,d0
	muls	#80,d0
	move.w	d6,d1
	asr.w	#3,d1
	add.w	d1,d0
	move.w	d0,a0
	move.l	-4(a6),d0
	add.l	d0,a0
	move.b	-5(a6),d0
	or.b	d0,(a0)
L77:
L76:
	addq.w	#1,a3
L74:
	cmp.w	a3,a4
	bgt	L73
L75:
L63:
	addq.w	#1,d3
L61:
	cmp.w	d3,d4
	bhi	L60
L62:
L59:
	movem.l	(a7)+,d3/d4/d5/d6/d7/a3/a4/a5
	unlk	a6
	rts
_plot8bitBitmap:
	link	a6,#-16
	movem.l	d3/d4/d5/d6/a3/a4,-(a7)
	move.w	14(a6),d6
	move.w	12(a6),d0
	muls	#80,d0
	ext.l	d0
	add.l	8(a6),d0
	move.w	d6,d1
	asr.w	#3,d1
	ext.l	d1
	add.l	d1,d0
	move.l	d0,a3
	moveq	#7,d0
	and.w	d6,d0
	move.w	d0,d5
	moveq	#8,d0
	sub.w	d5,d0
	move.w	d0,-16(a6)
	move.w	d6,d0
	asr.w	#3,d0
	tst.w	d0
	blt	L79
	cmp.w	#640,d6
	ble	L78
L79:
	bra	L80
L78:
	move.w	12(a6),d3
	bra	L82
L81:
	lea	80(a3),a3
	addq.w	#1,d3
L82:
	tst.w	d3
	blt	L81
L83:
	moveq	#0,d4
	sub.l	a4,a4
	bra	L85
L84:
	tst.w	d3
	blt	L88
	cmp.w	#400,d3
	bge	L88
	move.l	16(a6),a0
	add.l	a4,a0
	clr.w	d0
	move.b	(a0),d0
	asr.w	d5,d0
	or.b	d0,(a3)
	or.b	d4,(a3)
	move.l	16(a6),a0
	add.l	a4,a0
	clr.w	d0
	move.b	(a0),d0
	move.w	-16(a6),d1
	asl.w	d1,d0
	move.b	d0,d4
	lea	80(a3),a3
	bra	L89
L88:
	cmp.w	#400,d3
	bge	L86
L90:
L89:
	addq.w	#1,d3
L87:
	addq.w	#1,a4
L85:
	cmp.w	20(a6),a4
	bcs	L84
L86:
	tst.w	d5
	beq	L91
	cmp.w	#400,d3
	bge	L91
	or.b	d4,(a3)
L91:
L80:
	movem.l	(a7)+,d3/d4/d5/d6/a3/a4
	unlk	a6
	rts
_plot16bitBitmap:
	link	a6,#-16
	movem.l	d3/d4/d5/d6/d7/a3,-(a7)
	move.w	14(a6),d7
	move.w	12(a6),d0
	muls	#40,d0
	ext.l	d0
	add.l	d0,d0
	add.l	8(a6),d0
	move.w	d7,d1
	asr.w	#4,d1
	ext.l	d1
	add.l	d1,d1
	add.l	d1,d0
	move.l	d0,a3
	moveq	#15,d0
	and.w	d7,d0
	move.w	d0,d6
	moveq	#16,d0
	sub.w	d6,d0
	move.w	d0,-16(a6)
	move.w	d7,d0
	asr.w	#4,d0
	tst.w	d0
	blt	L93
	cmp.w	#640,d7
	ble	L92
L93:
	bra	L94
L92:
	move.w	12(a6),d3
	bra	L96
L95:
	lea	80(a3),a3
	addq.w	#1,d3
L96:
	tst.w	d3
	blt	L95
L97:
	moveq	#0,d5
	moveq	#0,d4
	bra	L99
L98:
	tst.w	d3
	blt	L102
	cmp.w	#400,d3
	bge	L102
	move.w	d4,a0
	add.l	a0,a0
	move.l	16(a6),d0
	add.l	d0,a0
	move.w	(a0),d0
	lsr.w	d6,d0
	or.w	d0,(a3)
	or.w	d5,(a3)
	move.w	d4,a0
	add.l	a0,a0
	move.l	16(a6),d0
	add.l	d0,a0
	move.w	(a0),d0
	move.w	-16(a6),d1
	asl.w	d1,d0
	move.w	d0,d5
	lea	80(a3),a3
	bra	L103
L102:
	cmp.w	#400,d3
	bge	L100
L104:
L103:
	addq.w	#1,d3
L101:
	addq.w	#1,d4
L99:
	cmp.w	20(a6),d4
	bcs	L98
L100:
	tst.w	d6
	beq	L105
	cmp.w	#400,d3
	bge	L105
	or.w	d5,(a3)
L105:
L94:
	movem.l	(a7)+,d3/d4/d5/d6/d7/a3
	unlk	a6
	rts
_plot32bitBitmap:
	link	a6,#-12
	movem.l	d3/d4/d5/d6/a3,-(a7)
	move.w	14(a6),d5
	moveq	#31,d0
	and.w	d5,d0
	move.w	d0,d6
	moveq	#32,d0
	sub.w	d6,d0
	move.w	d0,-12(a6)
	tst.w	d5
	blt	L107
	cmp.w	#640,d5
	blt	L106
L107:
	bra	L108
L106:
	move.w	12(a6),d3
	move.l	8(a6),a3
	bra	L110
L109:
	lea	80(a3),a3
	addq.w	#1,d3
L110:
	tst.w	d3
	blt	L109
L111:
	move.w	d3,d0
	muls	#20,d0
	move.w	d5,d1
	asr.w	#5,d1
	add.w	d1,d0
	ext.l	d0
	asl.l	#2,d0
	add.l	d0,a3
	moveq	#0,d4
	bra	L113
L112:
	tst.w	d3
	blt	L116
	cmp.w	#400,d3
	bge	L116
	ext.l	d4
	move.l	d4,d0
	asl.l	#2,d0
	move.l	d0,a0
	move.l	16(a6),d0
	add.l	d0,a0
	move.l	(a0),d0
	lsr.l	d6,d0
	or.l	d0,(a3)
	tst.w	d6
	beq	L117
	move.w	d5,d0
	asr.w	#5,d0
	addq.w	#1,d0
	cmp.w	#20,d0
	bge	L117
	ext.l	d4
	move.l	d4,d0
	asl.l	#2,d0
	move.l	d0,a0
	move.l	16(a6),d0
	add.l	d0,a0
	move.l	(a0),d0
	move.w	-12(a6),d1
	asl.l	d1,d0
	or.l	d0,4(a3)
L117:
	lea	80(a3),a3
	bra	L118
L116:
	cmp.w	#400,d3
	bge	L114
L119:
L118:
	addq.w	#1,d3
L115:
	addq.w	#1,d4
L113:
	cmp.w	20(a6),d4
	bcs	L112
L114:
L108:
	movem.l	(a7)+,d3/d4/d5/d6/a3
	unlk	a6
	rts
_plotCharacter:
	link	a6,#-14
	movem.l	d3/d4/d5/d6/d7,-(a7)
	move.b	17(a6),d7
	cmp.b	#32,d7
	blt	L120
	cmp.b	#126,d7
	bgt	L120
	move.b	d7,d0
	ext.w	d0
	sub.w	#32,d0
	asl.w	#3,d0
	ext.l	d0
	add.l	#_font,d0
	move.l	d0,-4(a6)
	moveq	#0,d5
	bra	L122
L121:
	moveq	#0,d4
	bra	L126
L125:
	move.w	12(a6),d0
	add.w	d5,d0
	move.w	d0,d6
	move.w	14(a6),d0
	add.w	d4,d0
	move.w	d0,d3
	moveq	#1,d0
	moveq	#7,d1
	sub.w	d4,d1
	asl.w	d1,d0
	move.b	d0,-5(a6)
	tst.w	d6
	blt	L129
	cmp.w	#400,d6
	bge	L129
	tst.w	d3
	blt	L129
	cmp.w	#640,d3
	bge	L129
	move.l	-4(a6),a0
	ext.l	d5
	move.b	0(a0,d5.l),d0
	and.b	-5(a6),d0
	beq	L130
	move.w	d6,d0
	muls	#80,d0
	move.w	d3,d1
	asr.w	#3,d1
	add.w	d1,d0
	move.w	d0,a0
	move.l	8(a6),d0
	add.l	d0,a0
	moveq	#1,d0
	moveq	#7,d1
	moveq	#7,d2
	and.w	d3,d2
	sub.w	d2,d1
	asl.w	d1,d0
	or.b	d0,(a0)
L130:
L129:
L128:
	addq.w	#1,d4
L126:
	cmp.w	#8,d4
	blt	L125
L127:
L124:
	addq.w	#1,d5
L122:
	cmp.w	#8,d5
	blt	L121
L123:
L120:
	movem.l	(a7)+,d3/d4/d5/d6/d7
	unlk	a6
	rts
_plotString:
	link	a6,#-4
	movem.l	d3/d4/a3/a4,-(a7)
	move.l	16(a6),a4
	move.w	14(a6),d4
	sub.l	a3,a3
	move.w	d4,d3
	bra	L132
L131:
	cmp.b	#10,0(a4,a3.l)
	bne	L134
	addq.w	#8,12(a6)
	move.w	d4,d3
	bra	L135
L134:
	cmp.b	#13,0(a4,a3.l)
	bne	L136
	move.w	d4,d3
	bra	L137
L136:
	cmp.b	#32,0(a4,a3.l)
	blt	L138
	cmp.b	#126,0(a4,a3.l)
	bgt	L138
	move.b	0(a4,a3.l),d0
	ext.w	d0
	move.w	d0,-(a7)
	move.w	d3,-(a7)
	move.w	12(a6),-(a7)
	move.l	8(a6),-(a7)
	jsr	_plotCharacter
	lea	10(a7),a7
	addq.w	#8,d3
L138:
L137:
L135:
	addq.w	#1,a3
L132:
	tst.b	0(a4,a3.l)
	bne	L131
L133:
	movem.l	-20(a6),d3/d4/a3/a4
	unlk	a6
	rts
	globl	_clearScreen
	globl	_clearRegion
	globl	_plotPixel
	globl	_plotHorizontalLine
	globl	_plotVerticalLine
	globl	_plotLine
	globl	_plotRectangle
	globl	_plotSquare
	globl	_plotTriangle
	globl	_plot8bitBitmap
	globl	_plot16bitBitmap
	globl	_plot32bitBitmap
	globl	_plotCharacter
	globl	_plotString
