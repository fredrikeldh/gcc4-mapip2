#include "config.h"
#include "system.h"
#include <signal.h>
#include "coretypes.h"
#include "mapip2.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "insn-constants.h"
#include "conditions.h"
#include "insn-attr.h"
#include "recog.h"
#include "toplev.h"
#include "output.h"

#include "basic-block.h"

#include "tree.h"
#include "function.h"
#include "expr.h"
#include "flags.h"
#include "reload.h"
#include "output.h"
#include "tm_p.h"
#include "ggc.h"

#include "target.h"
#include "target-def.h"

/***********************************
*  Test if a reg can be used as a
*		  base register
***********************************/

static int mapip_reg_ok_for_base_p(rtx x, int strict)
{
	if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
		return 0;

	return (strict
		? REGNO_OK_FOR_BASE_P (REGNO (x))
		: (REGNO (x) < FIRST_PSEUDO_REGISTER || REGNO (x) >= FIRST_PSEUDO_REGISTER));
}

/*
* We support only one addressing mode: register + immediate.
*/
#undef TARGET_LEGITIMATE_ADDRESS_P
static bool TARGET_LEGITIMATE_ADDRESS_P(enum machine_mode mode ATTRIBUTE_UNUSED, rtx x, bool strict)
{
	int valid;

	if (CONSTANT_ADDRESS_P (x))
		return 1;

	while (GET_CODE (x) == SUBREG)
		x = SUBREG_REG (x);

	if (GET_CODE (x) == REG && mapip_reg_ok_for_base_p (x, strict))
		return 1;

	valid = 0;
	if (GET_CODE (x) == PLUS)
	{
		register rtx x0 = XEXP (x, 0);
		register rtx x1 = XEXP (x, 1);

		register enum rtx_code c0;
		register enum rtx_code c1;

		while (GET_CODE (x0) == SUBREG)
			x0 = SUBREG_REG (x0);

		c0 = GET_CODE (x0);

		while (GET_CODE (x1) == SUBREG)
			x1 = SUBREG_REG (x1);

		c1 = GET_CODE (x1);

		if (c0 == REG
			&& mapip_reg_ok_for_base_p (x0, strict))
		{
			if (c1 == CONST_INT || CONSTANT_ADDRESS_P (x1))
				valid = 1;
		}

		if (!valid)
		{
		/*  	  fprintf (stderr, "INVALID(%d): ", reload_completed); */
		/*  	  debug_rtx (x); */
		}
	}

  return valid;
}

/* Initialize the GCC target structure.  */

struct gcc_target targetm = TARGET_INITIALIZER;



void ASM_GENERATE_INTERNAL_LABEL(char *buf, const char *prefix, int num)
{
	if (strcmp(prefix, "L") == 0)			/* instruction labels */
	{
		sprintf (buf, "*L%d", num);
		return;
	}

	if (strcmp(prefix, "LTHUNK") == 0)			/* Trap thunk labels */
	{
		sprintf (buf, "*%%%d", num);
		return;
	}

	sprintf (buf, "*%s%d", prefix, num);
}

void ASM_OUTPUT_ALIGN(FILE* stream, int power)
{
	fprintf(stream, ".align %i\n", 1 << power);
}

void ASM_OUTPUT_COMMON(FILE* stream, const char* name, int size, int rounded)
{
	fprintf(stream, ".comm\t");
	assemble_name(stream, name);
	fprintf(stream, ", %d\t// size=%d\n", rounded, size);
}

void ASM_OUTPUT_SKIP(FILE* stream, int nbytes)
{
  fprintf(stream, ".space\t%u\t//(ASM_OUTPUT_SKIP)\n", (nbytes));
}

void ASM_OUTPUT_LOCAL(FILE* stream, const char* name, int size, int rounded)
{
  fprintf(stream, ".lcomm\t");
  assemble_name(stream, name);
  fprintf(stream, ", %d\t// size=%d\n", rounded, size);
}

void default_globalize_label(FILE* stream, const char* name)
{
	fputs(".global\t", stream);
	assemble_name(stream, name);
	putc('\n', stream);
}
