#ifndef MAPIP2_H
#define MAPIP2_H

#include "insn-flags.h"

/* undocumented */
#define HAVE_GAS_HIDDEN


/* run-time target */
#define SWITCHABLE_TARGET 0

#define TARGET_CPU_CPP_BUILTINS() \
do \
	{ \
		builtin_define ("MAPIP");	 \
		builtin_define_std ("mapip2"); \
		builtin_assert ("cpu=mapip2"); \
		builtin_assert ("machine=mapip2"); \
	} \
while (0)

/* register basics */
#define FIRST_PSEUDO_REGISTER 32
#define FIXED_REGISTERS \
{ \
  1, 1, 1, 0, \
  0, 0, 0, 0, 0, 0, 0, 0,	\
  0, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 0, 0,	\
  0, 0, 0, 0, 0, 0, 0, 0,	\
}
#define CALL_USED_REGISTERS	\
{ \
  1, 1, 1, 0, \
  0, 0, 0, 0, 0, 0, 0, 0,	\
  1, 1, 1, 1, \
  1, 1, 1, 1, 1, 1, 1, 1,	\
  1, 1, 1, 1, 1, 1, 1, 1,	\
}

/* register classes */
enum reg_class
{
  NO_REGS,
  SP_REGS, /* stack pointer */
  GENERAL_REGS,
  ALL_REGS,
  LIM_REG_CLASSES
};
#define REG_CLASS_NAMES	\
{ \
  "NO_REGS",\
  "SP_REGS",\
  "GENERAL_REGS",\
  "ALL_REGS",\
}

#define REG_CLASS_CONTENTS \
{ \
  {0x00000000},\
  {0x00000002},\
  {0xFFFFFFFF},\
  {0xFFFFFFFF},\
}

#define N_REG_CLASSES ((int) LIM_REG_CLASSES)
#define BASE_REG_CLASS GENERAL_REGS
#define REGNO_OK_FOR_BASE_P(num) ((num) < FIRST_PSEUDO_REGISTER)
#define REGNO_REG_CLASS(num)	(((num) < FIRST_PSEUDO_REGISTER) ? GENERAL_REGS : NO_REGS)
#define CLASS_MAX_NREGS(CLASS, MODE)\
  ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)
#define REGNO_OK_FOR_INDEX_P(num) 0
#define INDEX_REG_CLASS NO_REGS

/* storage layout */
#define BITS_PER_UNIT 8
#define UNITS_PER_WORD 4
#define BITS_PER_WORD (BITS_PER_UNIT*UNITS_PER_WORD)
#define PARM_BOUNDARY BITS_PER_WORD
#define STACK_BOUNDARY BITS_PER_WORD
#define PREFERRED_STACK_BOUNDARY STACK_BOUNDARY
#define BIGGEST_ALIGNMENT BITS_PER_WORD
#define STRICT_ALIGNMENT 1
#define BITS_BIG_ENDIAN 0
#define BYTES_BIG_ENDIAN 0
#define WORDS_BIG_ENDIAN 0
#define FUNCTION_BOUNDARY 8
#define STACK_SAVEAREA_MODE(LEVEL) Pmode
#define PROMOTE_MODE(MODE, UNSIGNEDP, TYPE) \
do { \
	if (GET_MODE_CLASS (MODE) == MODE_INT \
		&& GET_MODE_SIZE (MODE) < 4) { \
		(MODE) = SImode; \
		(UNSIGNEDP) = 1; } \
} while (0)

#define CONSTANT_ALIGNMENT(EXP, ALIGN) \
	((TREE_CODE (EXP) == STRING_CST  || TREE_CODE (EXP) == CONSTRUCTOR) \
	&& (ALIGN) < BITS_PER_WORD ? BITS_PER_WORD : (ALIGN))

#undef DATA_ALIGNMENT
#define DATA_ALIGNMENT(TYPE, ALIGN) \
	((((ALIGN) < BITS_PER_WORD) \
	&& (TREE_CODE (TYPE) == ARRAY_TYPE \
	|| TREE_CODE (TYPE) == UNION_TYPE \
	|| TREE_CODE (TYPE) == RECORD_TYPE)) ? BITS_PER_WORD : (ALIGN))

#define LOCAL_ALIGNMENT DATA_ALIGNMENT


/* type layout */
#define DEFAULT_SIGNED_CHAR 0
#define WCHAR_TYPE_SIZE 16
#define WCHAR_TYPE "short unsigned int"

/* addressing modes */
#define MAX_REGS_PER_ADDRESS 1
#define LEGITIMATE_CONSTANT_P(x) 1

/* misc */
#define Pmode SImode
#define FUNCTION_MODE SImode
#define MOVE_MAX UNITS_PER_WORD
#define TRULY_NOOP_TRUNCATION(oprec, inprec) 1
#define CASE_VECTOR_MODE Pmode
#define HAS_LONG_COND_BRANCH 1
#define HAS_LONG_UNCOND_BRANCH 1
#define WORD_REGISTER_OPERATIONS

/* frame registers */
#define STACK_POINTER_REGNUM SP_REGNUM
#define FRAME_POINTER_REGNUM FP_REGNUM
#define RETURN_ADDRESS_POINTER_REGNUM RA_REGNUM
#define ARG_POINTER_REGNUM FP_REGNUM
/* g13 is the least likely to be used temporary register, so we
   use it for the static chain */
#define STATIC_CHAIN_REGNUM (G0_REGNUM+13)

/* exception handling */
#define EH_RETURN_DATA_REGNO(N) ((N) < 2 ? (N) + G0_REGNUM : INVALID_REGNUM)

/* register arguments */
#define FUNCTION_ARG_REGNO_P(regno) ((regno) >= P0_REGNUM && (regno) <= P3_REGNUM)
typedef int CUMULATIVE_ARGS;
#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, FNDECL, N_NAMED_ARGS) \
	(CUM) = 0

/* values in registers */
#define HARD_REGNO_MODE_OK(REGNO, MODE) 1
#define MODES_TIEABLE_P(MODE1, MODE2)	\
	(GET_MODE_CLASS (MODE1) == GET_MODE_CLASS (MODE2) \
	|| GET_MODE_SIZE (MODE1) == GET_MODE_SIZE (MODE2))
#define HARD_REGNO_NREGS(REGNO, MODE) \
	((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) \
	/ UNITS_PER_WORD)

/* trampolines */
#define TRAMPOLINE_SIZE 4

/* frame layout */
#define STACK_GROWS_DOWNWARD 1
#define STARTING_FRAME_OFFSET 0
#define FIRST_PARM_OFFSET(fundecl) 0
#define INCOMING_RETURN_ADDR_RTX gen_rtx_REG(SImode, RA_REGNUM)
#define DWARF_FRAME_RETURN_COLUMN RA_REGNUM

/* Can't declare ASM_* functions directly;
compiler uses #ifdef to check for availability. */

/* label output */
#define ASM_GENERATE_INTERNAL_LABEL mapip2_asm_generate_internal_label
void mapip2_asm_generate_internal_label PARAMS ((char* buf, const char*  prefix, int num));

/* alignment output */
#define ASM_OUTPUT_ALIGN mapip2_asm_output_align
void mapip2_asm_output_align PARAMS ((FILE* stream, int power));
#define ASM_OUTPUT_SKIP mapip2_asm_output_skip
void mapip2_asm_output_skip PARAMS ((FILE* stream, int nbytes));

/* uninitialized data */
#define ASM_OUTPUT_COMMON mapip2_asm_output_common
void mapip2_asm_output_common PARAMS ((FILE* stream, const char* name, int size, int rounded));
#define ASM_OUTPUT_LOCAL mapip2_asm_output_local
void mapip2_asm_output_local PARAMS ((FILE* stream, const char* name, int size, int rounded));

/* dispatch tables */
#define ASM_OUTPUT_ADDR_DIFF_ELT mapip2_asm_output_addr_diff_elt
void mapip2_asm_output_addr_diff_elt PARAMS ((FILE* stream, rtx body, int value, int rel));
#define ASM_OUTPUT_ADDR_VEC_ELT mapip2_asm_output_addr_vec_elt
void mapip2_asm_output_addr_vec_elt PARAMS ((FILE* stream, int value));

/* instruction output */
#define REGISTER_NAMES \
{ \
"zr", "sp",  "ra",  "fp",\
"s0", "s1",  "s2",  "s3", "s4", "s5", "s6", "s7",\
"p0", "p1",  "p2",  "p3", "g0", "g1", "g2", "g3",\
"g4", "g5",  "g6",  "g7", "g8", "g9", "g10","g11",\
"g12","g13", "r0",  "r1",\
}


/* profiling */
#define FUNCTION_PROFILER(FILE, NUM)

/* costs */
#define SLOW_BYTE_ACCESS 1

/* elimination */
#define INITIAL_FRAME_POINTER_OFFSET(depth) (depth) = 0

/* file framework */
#define ASM_APP_ON "#APP"
#define ASM_APP_OFF "#NO_APP"

/* old constraints */
#define CONST_DOUBLE_OK_FOR_LETTER_P(value, c) 0
#define CONST_OK_FOR_CONSTRAINT_P(value, c, str) 0
#define REG_CLASS_FROM_LETTER(c) NO_REGS
#define EXTRA_ADDRESS_CONSTRAINT(c, str) 0

/* debugging info */
#if 0
#define DWARF2_DEBUGGING_INFO 1
#define DWARF2_ASM_LINE_DEBUG_INFO 1
#else
#define DBX_DEBUGGING_INFO 1
#endif
#define PREFERRED_DEBUGGING_TYPE DBX_DEBUG

/* sections */
#define TEXT_SECTION_ASM_OP ".text"
#define DATA_SECTION_ASM_OP	".data"
#define READONLY_DATA_SECTION_ASM_OP ".rodata"
#define BSS_SECTION_ASM_OP	".bss"


#define GCC_INSN_FLAGS_H	/* enable all default values */
#include "defaults.h"


void mapip2_expand_call (rtx* operands, int returns_value);

#endif	/*MAPIP2_H*/
