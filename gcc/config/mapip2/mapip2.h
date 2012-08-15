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
#define FIRST_PSEUDO_REGISTER (32 + 16 + 2)
#define FIRST_FLOAT_REGISTER (32)
#define FLOAT_REGISTER_COUNT (16)
#define FIRST_FAKE_REGISTER (FIRST_FLOAT_REGISTER + FLOAT_REGISTER_COUNT)

/* register allocation order */
/* f8-f15, f0-f7, g0-g13, p0-p3, r0-r1, fr, s0-s7.
	(zr, ra, sp are fixed and may not be allocated by anything.) */
#define REG_ALLOC_ORDER {\
	40,41,42,43,44,45,46,47,\
	32,33,34,35,36,37,38,39,\
	16,17,18,19,20,21,22,23,\
	24,25,26,27,28,29,\
	12,13,14,15,\
	30,31,\
	3,\
	4,5,6,7,8,9,10,11,\
}

#define FIXED_REGISTERS \
{ \
	1, 1, 1, 0, /*special*/\
	0, 0, 0, 0, 0, 0, 0, 0, /*saved*/	\
	0, 0, 0, 0, /*parameters*/\
	0, 0, 0, 0, 0, 0, 0, 0, /*general*/	\
	0, 0, 0, 0, 0, 0, 0, 0, /*general*/	\
	0, 0, 0, 0, 0, 0, 0, 0, /*float*/	\
	0, 0, 0, 0, 0, 0, 0, 0, /*float*/	\
	1, 1, /*fake*/ \
}
#define CALL_USED_REGISTERS	\
{ \
	1, 1, 1, 0, \
	0, 0, 0, 0, 0, 0, 0, 0,	\
	1, 1, 1, 1, \
	1, 1, 1, 1, 1, 1, 1, 1,	\
	1, 1, 1, 1, 1, 1, 1, 1,	\
	0, 0, 0, 0, 0, 0, 0, 0,	/* saved float */ \
	1, 1, 1, 1, 1, 1, 1, 1,	/* unsaved float */ \
	1, 1, \
}

/* register classes */
enum reg_class
{
	NO_REGS,
	SP_REGS, /* stack pointer */
	GENERAL_REGS,
	FLOAT_REGS,
	ALL_REGS,
	LIM_REG_CLASSES
};
#define REG_CLASS_NAMES	\
{ \
	"NO_REGS",\
	"SP_REGS",\
	"GENERAL_REGS",\
	"FLOAT_REGS",\
	"ALL_REGS",\
}

#define REG_CLASS_CONTENTS \
{ \
	{0x00000000, 0x0},\
	{0x00000002, 0x0},\
	{0xFFFFFFFF, 0x30000},\
	{0x00000000, 0x0FFFF},\
	{0xFFFFFFFF, 0x3FFFF},\
}

#define N_REG_CLASSES ((int) LIM_REG_CLASSES)
#define BASE_REG_CLASS GENERAL_REGS
#define REGNO_OK_FOR_BASE_P(num) mapip2_regno_ok_for_base_p(num)
int mapip2_regno_ok_for_base_p(unsigned regnum);
#define REGNO_REG_CLASS(num) mapip2_regno_reg_class(num)
enum reg_class mapip2_regno_reg_class(unsigned regnum);
#define CLASS_MAX_NREGS(CLASS, MODE) mapip2_class_max_nregs(CLASS, MODE)
int mapip2_class_max_nregs(int CLASS, int MODE);
#define REGNO_OK_FOR_INDEX_P(num) 0
#define INDEX_REG_CLASS NO_REGS

/* custom */
#define INT_REGNO_P(num) ((num) < FR0_REGNUM || (num) >= FIRST_FAKE_REGNUM)
#define FLOAT_REGNO_P(num) ((num) >= FR0_REGNUM && (num) <= FR15_REGNUM)

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
#define WINT_TYPE "int"

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
#define SHORT_IMMEDIATES_SIGN_EXTEND
#define TARGET_OBJECT_SUFFIX ".o"

/* frame registers */
#define STACK_POINTER_REGNUM SP_REGNUM
#define HARD_FRAME_POINTER_REGNUM FP_REGNUM
#define FRAME_POINTER_REGNUM 0
/* these two are fake registers, so that FP can be eliminated
   in -fomit-frame-pointer mode. */
#define RETURN_ADDRESS_POINTER_REGNUM RAP_REGNUM
#define ARG_POINTER_REGNUM ARG_REGNUM
/* g13 is the least likely to be used temporary register, so we
   use it for the static chain */
#define STATIC_CHAIN_REGNUM (G0_REGNUM+13)

/* elimination */
#define ELIMINABLE_REGS {\
	{ ARG_POINTER_REGNUM, STACK_POINTER_REGNUM },\
	{ ARG_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM },\
	{ FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM },\
	{ FRAME_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM },\
	{ RETURN_ADDRESS_POINTER_REGNUM, RA_REGNUM },\
	{ RETURN_ADDRESS_POINTER_REGNUM, STACK_POINTER_REGNUM },\
	{ RETURN_ADDRESS_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM },\
}

#define INITIAL_FRAME_POINTER_OFFSET(depth) \
	(depth) = mapip2_initial_frame_pointer_offset()
int mapip2_initial_frame_pointer_offset(void);

#define INITIAL_ELIMINATION_OFFSET(from, to, offset) \
	offset = mapip2_initial_elimination_offset(from, to)
int mapip2_initial_elimination_offset(int from, int to);

/* exception handling */
#define EH_RETURN_DATA_REGNO(N) ((N) < 2 ? (N) + G0_REGNUM : INVALID_REGNUM)

/* register arguments */
#define FUNCTION_ARG_REGNO_P(regno) mapip2_function_arg_regno_p(regno)
int mapip2_function_arg_regno_p(int regno);

typedef struct CUMULATIVE_ARGS {
	unsigned i;	/* int registers used */
	unsigned f;	/* float registers used */
	unsigned s;	/* stack words used */
} CUMULATIVE_ARGS;

#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, FNDECL, N_NAMED_ARGS) \
	mapip2_init_cumulative_args(&(CUM));
void mapip2_init_cumulative_args(CUMULATIVE_ARGS*);

/* values in registers */
#define HARD_REGNO_MODE_OK(regno, mode) mapip2_hard_regno_mode_ok(regno, mode)
int mapip2_hard_regno_mode_ok(int regno, int mode);

#define MODES_TIEABLE_P(mode1, mode2)	mapip2_modes_tieable_p(mode1, mode2)
int mapip2_modes_tieable_p(int mode1, int mode2);

#define HARD_REGNO_NREGS(regno, mode) mapip2_hard_regno_nregs(regno, mode);
int mapip2_hard_regno_nregs(int regno, int mode);

/* trampolines */
#define TRAMPOLINE_SIZE 4

/* frame layout */
#define STACK_GROWS_DOWNWARD 1
#define FRAME_GROWS_DOWNWARD 1
#define STARTING_FRAME_OFFSET 0
#define FIRST_PARM_OFFSET(fundecl) 0
#define INCOMING_RETURN_ADDR_RTX gen_rtx_REG(SImode, RA_REGNUM)
#define DWARF_FRAME_RETURN_COLUMN RA_REGNUM


/* Can't declare ASM_* functions directly;
compiler uses #ifdef to check for availability. */

/* label output */
#define ASM_GENERATE_INTERNAL_LABEL mapip2_asm_generate_internal_label
void mapip2_asm_generate_internal_label PARAMS ((char* buf, const char*  prefix, int num));
#define ASM_OUTPUT_LABELREF mapip2_asm_output_labelref
void mapip2_asm_output_labelref PARAMS ((FILE* stream, const char* name));
#define ASM_WEAKEN_LABEL mapip2_asm_weaken_label
void mapip2_asm_weaken_label PARAMS ((FILE* stream, const char* name));
#define ASM_OUTPUT_WEAK_ALIAS mapip2_asm_output_weak_alias
void mapip2_asm_output_weak_alias PARAMS ((FILE* stream, const char* name, const char* value));

/* disabled because it creates ugly code. */
/* #define SET_ASM_OP ".set\t" */

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
"f0", "f1",  "f2",  "f3", "f4", "f5", "f6", "f7",\
"f8", "f9",  "f10", "f11","f12","f13","f14","f15",\
"rap", "arg",\
}


/* profiling */
#define FUNCTION_PROFILER(FILE, NUM)

/* costs */
#define SLOW_BYTE_ACCESS 1
#define NO_FUNCTION_CSE

/* file framework */
#define ASM_COMMENT_START "//"
#define ASM_APP_ON "//APP\n"
#define ASM_APP_OFF "//NO_APP\n"

/* debugging info */
#if 0
#define DWARF2_DEBUGGING_INFO 1
#define DWARF2_ASM_LINE_DEBUG_INFO 1
#else
#define DBX_DEBUGGING_INFO 1
#endif
#define PREFERRED_DEBUGGING_TYPE DBX_DEBUG
/* Do not break .stabs pseudos into continuations.  */
#define DBX_CONTIN_LENGTH 0
/* This allows us to output an extra stab in the function prologue. */
#define DBX_FUNCTION_FIRST

/* sections */
#define TEXT_SECTION_ASM_OP ".text"
#define DATA_SECTION_ASM_OP ".data"
#define READONLY_DATA_SECTION_ASM_OP ".section .rodata"
#define BSS_SECTION_ASM_OP ".bss"

/* driver */

#define CC1PLUS_SPEC "%{!frtti:-fno-rtti} %{!fexceptions:-fno-exceptions} %{!fthreadsafe-statics:-fno-threadsafe-statics}"


#define GCC_INSN_FLAGS_H	/* enable all default values */
#include "defaults.h"


void mapip2_expand_call (rtx* operands, int returns_value);
void mapip2_expand_prologue(void);
void mapip2_expand_epilogue(void);
int simple_return(void);

void mapip2_indirect_jump(rtx);
void mapip2_tablejump(rtx, rtx);

#endif	/*MAPIP2_H*/
