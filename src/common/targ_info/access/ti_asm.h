/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

   Path64 is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   Path64 is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with Path64; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.

   Special thanks goes to SGI for their continued support to open source

*/


/* ====================================================================
 * ====================================================================
 *
 *  Module: ti_asm.h
 *  $Revision$
 *  $Date$
 *  $Author$
 *  $Source$
 *
 *  Synopsis:
 *
 *	Support for assembling and disassembling instructions.
 *
 *  Interface Description:
 *
 *	Constants:
 *
 *	    const INT TI_ASM_DISASM_ABI_REGS
 *
 *		TI_ASM_DisAsm_Inst flag that indicates the abi register
 *		names should be used; otherwise the hardware names are used.
 *
 *	    const INT TI_ASM_DISASM_TRUE_PRED
 *
 *		TI_ASM_DisAsm_Inst flag that indicates that true predicates
 *		should be printed; otherwise true predicates are supporessed.
 *
 *      Exported functions:
 *
 *	    INT TI_ASM_Pack_Inst(
 *		TOP topcode
 *		const INT64 *result
 *		const INT64 *opnd
 *		ISA_PACK_INST *pinst
 *	    )
 *
 *		Assemble an instruction into object code. <topcode> is the 
 *		opcode of the instruction being assembled. <result> is an
 *		array of result values, indexed by result number. <opnd>
 *		is an array of operand values, indexed by operand number.
 *		A <result> or <opnd> value is whatever bit pattern 
 *		represents the operand, e.g. machine register number, 
 *		literal, etc.  <pinst> points to a buffer to receive the
 *		the instruction word(s).
 *
 *		On success, the return value indicates the number of
 *		instruction words written to the buffer pointed to by
 *		<pinst>. On error, the return value will be TI_RC_ERROR,
 *		and the error message copied to TI_errmsg.
 *
 *	    INT TI_ASM_Print_Inst(
 *		TOP topcode
 *		const char **result
 *		const char **opnd
 *		FILE *f
 *	    )
 *
 *		Assemble an instruction into printable assembly code.
 *		<topcode> is the opcode of the instruction being assembled. 
 *		<result> is an array of result values, indexed by result 
 *		number. <opnd> is an array of operand values, indexed by 
 *		operand number. A <result> or <opnd> value is the string 
 *		representation for the particular instruction operand, 
 *		e.g. machine register name, label, etc. The assembled 
 *		instruction is written to file <f>. No carriage control 
 *		is included in the copied string.
 *
 *		On success, the return value is the number of characters 
 *		that were written to the file (excluding the terminating null
 *		character). On error, the return value will be TI_RC_ERROR,
 *		and the error message copied to TI_errmsg.
 *
 *	    INT TI_ASM_DisAsm_Inst(
 *		TOP topcode
 *		INT64 *result
 *		INT64 *opnd
 *		INT64 pc
 *		INT flags
 *		char *bufptr
 *	    )
 *
 *		Disassemble an instruction into printable assembly code.
 *		<topcode> is the opcode of the instruction being disassembled. 
 *		<result> is an array of result values, indexed by result 
 *		number. <opnd> is an array of operand values, indexed by 
 *		operand number. A <result> or <opnd> value is whatever bit 
 *		pattern represents the operand, e.g. machine register number, 
 *		literal, etc. <pc> is the address of bundle containing
 *		the address (used only for formatting of pc-relative labels).
 *		<flags> one or more formatting flags (see TI_ASM_DISASM_xxx).
 *		<bufptr> is a pointer to a buffer to receive the disassembled 
 *		instruction.
 *
 *		On success, the return value is the number of characters 
 *		that were written to the buffer (excluding the terminating null
 *		character). On error, the return value will be TI_RC_ERROR,
 *		and the error message copied to TI_errmsg.
 *
 *	    void TI_ASM_Set_Bundle_Comp(
 *		ISA_BUNDLE           *bundle,
 *		ISA_BUNDLE_PACK_COMP  comp,
 *		UINT64                val
 *	    )
 *
 *		Set the <comp> field of the bundle pointed to by <bundle>
 *		to the value <val>. The contents of the field are overwritten,
 *		i.e. it is not necessary to zero the field (or bundle) first
 *		(quite handy for modifying a bundle field).
 *
 *	    UINT64 TI_ASM_Get_Bundle_Comp(
 *		const ISA_BUNDLE     *bundle,
 *		ISA_BUNDLE_PACK_COMP  comp
 *          )
 *
 *		Get the value of the <comp> field of the bundle pointed to
 *		by <bundle>. If the component is not part of the bundle
 *		on the current architecture, 0 is returned.
 *
 *          void TI_ASM_Set_Bundle_Reloc_Value(
 *              ISA_BUNDLE *bundle,
 *              INT         slot,
 *              UINT64      val
 *          )
 *
 *		Set the relocatable value in the instruction in slot <slot> 
 *		of the bundle pointed to by <bundle> to the value <val>. 
 *		The contents of the instruction/bundle field are overwritten, 
 *		i.e. it is not necessary to zero the field.
 *
 *          UINT64 TI_ASM_Get_Bundle_Reloc_Value(
 *              const ISA_BUNDLE *bundle,
 *              INT               slot
 *          )
 *
 *		Get the value of the relocatable value in the instruction
 *		in slot <slot> of the bundle pointed to by <bundle>.
 *
 *	    TOP TI_ASM_Unpack_Inst(
 *		ISA_PACK_INST *pinst,
 *		ISA_EXEC_UNIT  ex_unit,
 *		INT64         *result, 
 *		INT64         *opnd,
 *		BOOL           xlate_pseudo
 *	    )
 *
 *		Decode and unpack the instruction pointed to by <pinst>
 *		which executes in execution unit <ex_unit>. The decoded 
 *		opcode is returned by function value, and the operands 
 *		and results are returned in the arrays <opnd> and <result>. 
 *		These arrays should be large enough to hold the maximum 
 *		number of operands and results (ISA_OPERAND_max_operands 
 *		and ISA_OPERAND_max_results respectively). If <xlate_pseudo> 
 *		is true and the instruction matches the pattern for a pseudo 
 *		instruction, the topcode and results/operands are translated 
 *		as appropriate.
 *
 * ====================================================================
 * ====================================================================
 */

#ifndef ti_asm_INCLUDED
#define ti_asm_INCLUDED

#include <stdio.h>
#include "topcode.h"
#include "targ_isa_pack.h"
#include "targ_isa_bundle.h"
#include "targ_isa_decode.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KEEP_RCS_ID
static const char ti_asm_rcs_id[] = "$Source$ $Revision$";
#endif /* _KEEP_RCS_ID */

#ifndef defs_INCLUDED
#define defs_INCLUDED
typedef signed int INT;
typedef signed int INT32;
typedef signed long long INT64;
typedef signed char mINT8;
typedef signed short mINT16;
typedef signed int mINT32;
typedef signed long long mINT64;
typedef unsigned int UINT;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef unsigned char mUINT8;
typedef unsigned short mUINT16;
typedef unsigned int mUINT32;
typedef unsigned long long mUINT64;
typedef int BOOL;
typedef unsigned char mBOOL;
#ifndef TRUE
#define TRUE    ((BOOL) 1)
#endif
#ifndef FALSE
#define FALSE   ((BOOL) 0)
#endif
#if defined(_LANGUAGE_C) && !defined(inline)
#define inline static __inline
#endif
#endif

#define TI_ASM_DISASM_ABI_REGS	(0x01)
#define TI_ASM_DISASM_TRUE_PRED	(0x02)

extern INT TI_ASM_Pack_Inst(
  TOP topcode,
  const INT64 *result,
  const INT64 *opnd,
  ISA_PACK_INST *pinst
);

extern INT TI_ASM_Print_Inst(
  TOP topcode,
  const char **result,
  const char **opnd,
  FILE *f
);

extern void TI_ASM_Set_Bundle_Comp(
  ISA_BUNDLE           *bundle,
  ISA_BUNDLE_PACK_COMP  comp,
  UINT64                val
);

extern INT TI_ASM_DisAsm_Inst(
  TOP topcode,
  INT64 *result,
  INT64 *opnd,
  INT64 pc,
  INT flags,
  char *bufptr
);

extern UINT64 TI_ASM_Get_Bundle_Comp(
  const ISA_BUNDLE     *bundle,
  ISA_BUNDLE_PACK_COMP  comp
);

extern void TI_ASM_Set_Bundle_Reloc_Value(
  ISA_BUNDLE *bundle,
  INT         slot,
  UINT64      val
);

extern UINT64 TI_ASM_Get_Bundle_Reloc_Value(
  const ISA_BUNDLE *bundle,
  INT               slot
);

extern TOP TI_ASM_Unpack_Inst(
  const ISA_PACK_INST *inst,
  ISA_EXEC_UNIT        ex_unit,
  INT64               *result, 
  INT64               *opnd,
  BOOL                 xlate_pseudo
);

#ifdef __cplusplus
}
#endif
#endif /* ti_asm_INCLUDED */
