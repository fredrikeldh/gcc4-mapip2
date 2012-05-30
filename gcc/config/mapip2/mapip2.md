(define_constants
	[(ZERO_REGNUM 0)
	(SP_REGNUM		1)
	(RA_REGNUM		2)
	(FP_REGNUM		3)
	(S0_REGNUM		4)
	(S1_REGNUM		5)
	(S2_REGNUM		6)
	(S3_REGNUM		7)
	(S4_REGNUM		8)
	(S5_REGNUM		9)
	(S6_REGNUM		10)
	(S7_REGNUM		11)
	(LAST_SAVED_REGNUM	11)
	(P0_REGNUM		12)
	(P1_REGNUM		13)
	(P2_REGNUM		14)
	(P3_REGNUM		15)
	(G0_REGNUM		16)
	(G1_REGNUM		17)
	(G2_REGNUM		18)
	(G3_REGNUM		19)
	(G4_REGNUM		20)
	(G5_REGNUM		21)
	(G6_REGNUM		22)
	(G7_REGNUM		23)
	(G8_REGNUM		24)
	(G9_REGNUM		25)
	(G10_REGNUM		26)
	(G11_REGNUM		27)
	(G12_REGNUM		28)
	(G13_REGNUM		29)
	(R0_REGNUM		30)
	(R1_REGNUM		31)
	(LAST_HARD_REGNUM	31)
	(RAP_REGNUM		32)
	(ARG_REGNUM		33)
	(CC_REGNUM		34)])

(define_insn "movsi"
	[(set (match_operand:SI 0 "nonimmediate_operand" "")
		(match_operand:SI 1 "general_operand" ""))]
	""
	"ld %0,%1")

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "jp %l0")

(define_insn "indirect_jump"
	[(set (pc) (match_operand:SI 0 "register_operand" "r"))]
	""
	"jp %0")

(define_insn "cbranchsi4"
	[(set (pc)
		(if_then_else (match_operator 0 "ordered_comparison_operator"
		[(match_operand:SI 1 "register_operand" "")
			(match_operand:SI 2 "register_operand" "")])
		(label_ref (match_operand 3 "" ""))
		(pc)))]
	""
	"jc %C0,%1,%2,%3")

(define_insn "nop"
	[(const_int 0)]
	"1"
	"")
