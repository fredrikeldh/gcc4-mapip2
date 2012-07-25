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
	(FR0_REGNUM   32)
	(FR8_REGNUM   40)
	(FR15_REGNUM  47)
	(LAST_HARD_REGNUM	47)
	(FIRST_FAKE_REGNUM 48)
	(RAP_REGNUM		48)
	(ARG_REGNUM		49)
	(CC_REGNUM		50)])


(define_predicate "call_operand"
  (match_code "mem")
{
  return (GET_CODE (op) == MEM
	  && (GET_CODE (XEXP (op, 0)) == SYMBOL_REF
			|| GET_CODE (XEXP (op, 0)) == REG));
})

(define_predicate "const0_operand"
	(and (match_code "const_int")
	(match_test "op == CONST0_RTX (mode)")))

(define_predicate "reg_or_0_operand"
	(ior (match_operand 0 "register_operand")
	(match_operand 0 "const0_operand")))

(define_register_constraint "f" "FLOAT_REGS"
	"Mapip2 float registers")

(define_register_constraint "A" "ALL_REGS"
	"Mapip2 all registers")


; put this first so movsi doesn't get insn_code 0, which appears to trigger an internal gcc bug.
(define_insn "nop"
	[(const_int 0)]
	"1"
	"")

(define_insn "movsi"
	[(set (match_operand:SI 0 "nonimmediate_operand" "=r,r,r,m")
	(match_operand:SI 1 "general_operand" "r,i,m,r"))]
	""
	"@
	ld %0,%z1
	ld %0,%z1
	ld %0,[%1]
	ld [%0],%z1")

(define_insn "movhi"
	[(set (match_operand:HI 0 "nonimmediate_operand" "=r,r,r,m")
	(match_operand:HI 1 "general_operand" "r,i,m,r"))]
	""
	"@
	ld %0,%z1
	ld %0,%z1
	ld.h %0,[%1]
	ld.h [%0],%z1")

(define_insn "movqi"
	[(set (match_operand:QI 0 "nonimmediate_operand" "=r,r,r,m")
		(match_operand:QI 1 "general_operand" "r,i,m,r"))]
	""
	"@
	ld %0,%z1
	ld %0,%z1
	ld.b %0,[%1]
	ld.b [%0],%z1")

(define_insn "movdi"
	[(set (match_operand:DI 0 "nonimmediate_operand" "=r,r,r,m")
		(match_operand:DI 1 "general_operand" "r,i,m,r"))]
	""
	"@
	ld.d %0,%z1
	ld.d %0,%z1
	ld.d %0,[%1]
	ld.d [%0],%z1")

(define_insn "movsf"
	[(set (match_operand:SF 0 "nonimmediate_operand" "=A,A,f,m,A,m")
		(match_operand:SF 1 "general_operand" "A,F,m,f,m,A"))]
	""
	"@
	ld %0,%z1
	ld %0,%z1
	ld.s %0,[%1]
	ld.s [%0],%z1
	ld %0,[%1]
	ld [%0],%z1")

(define_insn "movdf"
	[(set (match_operand:DF 0 "nonimmediate_operand" "=f,A,A,A,m")
		(match_operand:DF 1 "general_operand" "f,A,F,m,A"))]
	""
	"@
	ld %0,%z1
	ld.d %0,%z1
	ld.d %0,%z1
	ld.d %0,[%1]
	ld.d [%0],%z1")

(define_insn "truncdfsf2"
	[(set (match_operand:SF 0 "register_operand" "=A")
		(float_truncate:SF (match_operand:DF 1 "register_operand" "f")))]
	""
	"ld %0,%z1")

(define_insn "extendsfdf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(float_extend:DF (match_operand:SF 1 "register_operand" "A")))]
	""
	"ld %0,%z1")

(define_insn "floatsidf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(float:DF (match_operand:SI 1 "register_operand" "r")))]
	""
	"float.s %0,%z1")

(define_insn "floatdidf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(float:DF (match_operand:DI 1 "register_operand" "r")))]
	""
	"float.d %0,%z1")

(define_insn "floatunsidf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unsigned_float:DF (match_operand:SI 1 "register_operand" "r")))]
	""
	"floatun.s %0,%z1")

(define_insn "floatundidf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unsigned_float:DF (match_operand:DI 1 "register_operand" "r")))]
	""
	"floatun.d %0,%z1")


(define_insn "fix_truncsidf2"
	[(set (match_operand:SI 0 "register_operand" "=r")
		(fix:SI (match_operand:DF 1 "register_operand" "f")))]
	""
	"fix_trunc.s %0,%1")

(define_insn "fix_truncdidf2"
	[(set (match_operand:DI 0 "register_operand" "=r")
		(fix:DI (match_operand:DF 1 "register_operand" "f")))]
	""
	"fix_trunc.d %0,%1")

(define_insn "fixuns_truncsidf2"
	[(set (match_operand:SI 0 "register_operand" "=r")
		(unsigned_fix:SI (match_operand:DF 1 "register_operand" "f")))]
	""
	"fixun_trunc.s %0,%1")

(define_insn "fixuns_truncdidf2"
	[(set (match_operand:DI 0 "register_operand" "=r")
		(unsigned_fix:DI (match_operand:DF 1 "register_operand" "f")))]
	""
	"fixun_trunc.d %0,%1")

(define_insn "sqrtdf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(sqrt:DF (match_operand:DF 1 "register_operand" "f")))]
	""
	"fsqrt %0,%1")

(define_insn "sindf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "f")] 1))]
	""
	"fsin %0,%1")

(define_insn "cosdf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "f")] 2))]
	""
	"fcos %0,%1")

(define_insn "expdf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "f")] 3))]
	""
	"fexp %0,%1")

(define_insn "logdf2"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "f")] 4))]
	""
	"flog %0,%1")

(define_insn "powdf3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "register_operand" "f")] 5))]
	""
	"fpow %0,%2")

(define_insn "atan2df3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(unspec:DF [(match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "register_operand" "f")] 6))]
	""
	"fatan2 %0,%2")


(define_insn "zero_extendqisi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
	(zero_extend:SI (match_operand:QI 1 "register_operand" "0")))]
	""
	"and %0,#0xff  // zero extend")

(define_insn "zero_extendhisi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
	(zero_extend:SI (match_operand:HI 1 "register_operand" "0")))]
	""
	"and %0,#0xffff // zero extend")

(define_insn "extendhisi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
	(sign_extend:SI (match_operand:HI 1 "register_operand" "r")))]
	""
	"xh %0,%1")

(define_insn "extendqisi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
	(sign_extend:SI (match_operand:QI 1 "register_operand" "r")))]
	""
	"xb %0,%1")

(define_insn "truncsiqi2"
	[(set (match_operand:QI 0 "register_operand" "=r")
		(truncate:QI (match_operand:SI 1 "general_operand" "0")))]
	""
	"and %0,#0xff  // truncate")

(define_insn "truncsihi2"
	[(set (match_operand:HI 0 "register_operand" "=r")
		(truncate:HI (match_operand:SI 1 "general_operand" "0")))]
	""
	"and %0,#0xffff // truncate")

(define_insn "trunchiqi2"
	[(set (match_operand:QI 0 "register_operand" "=r")
		(truncate:QI (match_operand:HI 1 "general_operand" "0")))]
	""
	"and %0,#0xff  // truncate")


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
	"jp %0	//%1")

; fixme: allow constant zero
(define_insn "cbranchsi4"
	[(set (pc)
		(if_then_else (match_operator 0 "ordered_comparison_operator"
		[(match_operand:SI 1 "reg_or_0_operand" "r")
			(match_operand:SI 2 "reg_or_0_operand" "r")])
		(label_ref (match_operand 3 "" ""))
		(pc)))]
	""
	"jc %C0 %Z1,%Z2,%3")

(define_insn "cbranchdf4"
	[(set (pc)
		(if_then_else (match_operator 0 "ordered_comparison_operator"
		[(match_operand:DF 1 "register_operand" "f")
			(match_operand:DF 2 "register_operand" "f")])
		(label_ref (match_operand 3 "" ""))
		(pc)))]
	""
	"fjc %C0 %Z1,%Z2,%3")

(define_insn "call"
	[(call (match_operand:SI 0 "memory_operand" "m")
		(match_operand:SI 1 "general_operand" "g"))
	(clobber (reg:SI RA_REGNUM))]
	""
	"call %0	//%1")

(define_insn "call_value"
	[(set (match_operand 0 "" "=A")
		(call (match_operand:SI 1 "memory_operand" "m")
			(match_operand:SI 2 "general_operand" "g")))
	(clobber (reg:SI RA_REGNUM))]
	""
	"call %1	//%2, %0")

(define_insn "return"
	[(use (reg:SI RA_REGNUM))
	(return)]
	"reload_completed && !profile_flag && simple_return ()"
	"ret")

(define_insn "return_internal"
	[(use (reg:SI RA_REGNUM))
	(return)]
	""
	"ret")

(define_expand "prologue"
	[(const_int 1)]
	""
	"
{
	mapip2_expand_prologue();
	DONE;
}")

(define_expand "epilogue"
	[(const_int 2)]
	""
	"
{
	mapip2_expand_epilogue();
	DONE;
}")

(define_insn "store_regs"
	[(set (reg:SI SP_REGNUM)
		(minus:SI (reg:SI SP_REGNUM)
			(minus:SI (match_operand:SI 1 "register_operand" "")
				(match_operand:SI 0 "register_operand" "")
			)
		)
	)]
	""
	"push %0,%1")

(define_insn "restore_regs"
	[(set (reg:SI SP_REGNUM)
		(plus:SI (reg:SI SP_REGNUM)
			(minus:SI (match_operand:SI 1 "register_operand" "")
				(match_operand:SI 0 "register_operand" "")
			)
		)
	)]
	""
	"pop %0,%1")


(define_insn "negsi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
		(neg:SI (match_operand:SI 1 "reg_or_0_operand" "r")))]
	""
	"neg %0,%z1")

(define_insn "one_cmplsi2"
	[(set (match_operand:SI 0 "register_operand" "=r")
		(not:SI (match_operand:SI 1 "reg_or_0_operand" "r")))]
	""
	"not %0,%z1")



(define_insn "adddf3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(plus:DF (match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "register_operand" "f")))]
	""
	"fadd %0,%z2")

(define_insn "subdf3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(minus:DF (match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "register_operand" "f")))]
	""
	"fsub %0,%z2")

;; multiply
(define_insn "muldf3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(mult:DF (match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "register_operand" "f")))]
	""
	"fmul %0,%z2")

;; divide
(define_insn "divdf3"
	[(set (match_operand:DF 0 "register_operand" "=f")
		(div:DF (match_operand:DF 1 "register_operand" "0")
		(match_operand:DF 2 "general_operand" "f")))]
	""
	"fdiv %0,%2")


(define_insn "addsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(plus:SI (match_operand:SI 1 "general_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	add %0,%z2
	add %0,%z2")

(define_insn "subsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(minus:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	sub %0,%z2
	sub %0,%z2")

;; multiply
(define_insn "mulsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(mult:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	mul %0,%z2
	mul %0,%z2")

;; divide (signed)
(define_insn "divsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(div:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	div %0,%2
	div %0,%2")

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
	and %0,%z2
	and %0,%z2")

;; or
(define_insn "iorsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(ior:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "nonmemory_operand" "r,i")))]
	""
	"@
	or %0,%z2
	or %0,%z2")

;; xor
(define_insn "xorsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(xor:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	xor %0,%z2
	xor %0,%z2")

;; Shift left
(define_insn "ashlsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(ashift:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	sll %0,%2
	sll %0,%2")

;; Arithmetic shift right
(define_insn "ashrsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(ashiftrt:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	sra %0,%2
	sra %0,%2")

;; Logical shift right
(define_insn "lshrsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
		(lshiftrt:SI (match_operand:SI 1 "register_operand" "0,0")
		(match_operand:SI 2 "general_operand" "r,i")))]
	""
	"@
	srl %0,%2
	srl %0,%2")
