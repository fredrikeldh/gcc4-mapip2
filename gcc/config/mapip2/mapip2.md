(define_predicate "call_operand"
  (match_code "mem")
{
  return (GET_CODE (op) == MEM
	  && (GET_CODE (XEXP (op, 0)) == SYMBOL_REF
			|| GET_CODE (XEXP (op, 0)) == REG));
})

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

(define_insn "movhi"
	[(set (match_operand:HI 0 "nonimmediate_operand" "")
		(match_operand:HI 1 "general_operand" ""))]
	""
	"ld.h %0,%1")

(define_insn "movqi"
	[(set (match_operand:QI 0 "nonimmediate_operand" "")
		(match_operand:QI 1 "general_operand" ""))]
	""
	"ld.b %0,%1")

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "jp %0")

(define_insn "indirect_jump"
	[(set (pc) (match_operand:SI 0 "register_operand" "r"))]
	""
	"jp %0")

(define_insn "tablejump"
	[(set (pc)
		(match_operand:SI 0 "register_operand" "r"))
		(use (label_ref (match_operand 1 "" "")))]
	""
	"jp %0 ;%1")

(define_insn "cbranchsi4"
	[(set (pc)
		(if_then_else (match_operator 0 "ordered_comparison_operator"
		[(match_operand:SI 1 "register_operand" "")
			(match_operand:SI 2 "general_operand" "g")])
		(label_ref (match_operand 3 "" ""))
		(pc)))]
	""
	"jc %C0,%1,%2,%3")

(define_insn "nop"
	[(const_int 0)]
	"1"
	"")

(define_insn "call"
	[(call (match_operand:SI 0 "memory_operand" "m")
		(match_operand:SI 1 "general_operand" "g"))]
	""
	"call %0")

(define_insn "call_value"
	[(set (match_operand 0 "" "=g")
		(call (match_operand:SI 1 "memory_operand" "m")
			(match_operand:SI 2 "general_operand" "g")))]
  ""
  "call %1")

(define_insn "return"
	[(return)
		(clobber (reg:SI RA_REGNUM))]
	""
	"ret")

(define_insn "store_regs"
	[(match_operand:SI 0 "register_operand" "")
		(match_operand:SI 1 "register_operand" "")
		(const_int 1)]
	""
	"push %0,%1")

(define_insn "restore_regs"
	[(match_operand:SI 0 "register_operand" "")
		(match_operand:SI 1 "register_operand" "")
		(const_int 2)]
	""
	"pop %0,%1")

(define_insn "negsi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
		(neg:SI (match_operand:SI 1 "register_operand" "r")))]
	""
	"neg %0,%1")


; todo: whitespace cleanup
(define_insn "addsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(plus:SI (match_operand:SI 1 "general_operand" "%0,0")
		 (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
   add  %0,%2
   add  %0,%2")

(define_insn "subsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(minus:SI (match_operand:SI 1 "register_operand" "0,0")
		  (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
   sub  %0,%2
   sub  %0,%2")

;; multiply
(define_insn "mulsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(mult:SI (match_operand:SI 1 "register_operand" "0,0")
		 (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
   mul  %0,%2
   mul  %0,%2")

;; divide (signed)
(define_insn "divsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(div:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  div  %0,%2
  div  %0,%2"
)

;; divide (unsigned)
(define_insn "udivsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(udiv:SI (match_operand:SI 1 "register_operand" "0,0")
		 (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  divu %0,%2
  divu %0,%2")

;; and
(define_insn "andsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(and:SI (match_operand:SI 1 "register_operand" "%0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  and  %0,%2
  and  %0,%2")

;; or
(define_insn "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(ior:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "nonmemory_operand" "r,i")))]
  ""
  "@
  or   %0,%2
  or   %0,%2")

;; xor
(define_insn "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(xor:SI (match_operand:SI 1 "register_operand" "%0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  xor  %0,%2
  xor  %0,%2")

;; Shift left
(define_insn "ashlsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(ashift:SI (match_operand:SI 1 "register_operand" "0,0")
		   (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  sll  %0,%2
  sll  %0,%2")

;; Arithmetic shift right
(define_insn "ashrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(ashiftrt:SI (match_operand:SI 1 "register_operand" "0,0")
		     (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  sra  %0,%2
  sra  %0,%2")

;; Logical shift right
(define_insn "lshrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(lshiftrt:SI (match_operand:SI 1 "register_operand" "0,0")
		     (match_operand:SI 2 "general_operand" "r,i")))]
  ""
  "@
  srl  %0,%2
  srl  %0,%2")
