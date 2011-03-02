/*
 * Copyright 2004, 2005, 2006, 2008 PathScale Inc.  All Rights Reserved.
 */

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

#ifndef intrn_info_INCLUDED
#define intrn_info_INCLUDED "intrn_info.h"

#include "defs.h"
#include "wintrinsic.h"
#ifdef TARG_ST
#include "mtypes.h" //For TYPE_ID
#include "errors.h" // For FmtAssert
#endif
/* Enumeration of mnemonic names for the return types of intrinsic
 * functions and operators.  
 */
typedef enum INTRN_RETKIND {
  IRETURN_UNKNOWN,           /* Indeterminate type */
  IRETURN_V,                 /* MTYPE_V */
  IRETURN_I1,                /* MTYPE_I1 */
  IRETURN_I2,                /* MTYPE_I2 */
  IRETURN_I4,                /* MTYPE_I4 */
  IRETURN_I8,                /* MTYPE_I8 */
  IRETURN_U1,                /* MTYPE_U1 */
  IRETURN_U2,                /* MTYPE_U2 */
  IRETURN_U4,                /* MTYPE_U4 */
  IRETURN_U8,                /* MTYPE_U8 */
  IRETURN_F4,                /* MTYPE_F4 */
  IRETURN_F8,                /* MTYPE_F8 */
  IRETURN_FQ,                /* MTYPE_FQ */
  IRETURN_F16,               /* MTYPE_F16 */
  IRETURN_C4,                /* MTYPE_C4 */
  IRETURN_C8,                /* MTYPE_C8 */
  IRETURN_CQ,                /* MTYPE_CQ */
  IRETURN_C16,               /* MTYPE_C16 */
  IRETURN_PV,                /* Pointer to MTYPE_V */
  IRETURN_PU1,               /* Pointer to MTYPE_U1 */
  IRETURN_DA1,               /* Dereference argument 1 */
  IRETURN_SZT,               /* size_t */
  IRETURN_PC,                /* pointer to char */
  IRETURN_F10,               /* MTYPE_F10 */
#ifdef TARG_ST
  IRETURN_DYNAMIC,           /* dynamically added mtype */
  IRETURN_PPU2,         /* return type of ctype_b_loc() */
  IRETURN_PPI4,         /* return type of ctype_toupper_loc() and ctype_tolower_loc() */
#endif
#ifdef TARG_X8664
  IRETURN_V16I2,	     /* MTYPE_V16I2 */
  IRETURN_V16I4,	     /* MTYPE_V16I4 */
  IRETURN_V16F4,	     /* MTYPE_V16F4 */
  IRETURN_V16F8,	     /* MTYPE_V16F8 */
  IRETURN_V16C8,	     /* MTYPE_V16C8 */
  IRETURN_M8I1,		     /* MTYPE_M8I1 */
  IRETURN_M8I2,		     /* MTYPE_M8I2 */
  IRETURN_M8I4,		     /* MTYPE_M8I4 */
  IRETURN_V16I8,	     /* MTYPE_V16I8 */
  IRETURN_V16I1,	     /* MTYPE_V16I1 */
  IRETURN_V32I8,
  IRETURN_V32F8,
#endif
} INTRN_RETKIND;
#define INTRN_RETKIND_LAST IRETURN_F10

// some defines to make parameters more readable
#define BYVAL		TRUE
#define NOT_BYVAL	FALSE
#define PURE		TRUE
#define NOT_PURE	FALSE
#define NO_SIDEEFFECTS	TRUE
#define SIDEEFFECTS	FALSE
#define NEVER_RETURN	TRUE
#define DOES_RETURN	FALSE
#define ACTUAL		TRUE
#define NOT_ACTUAL	FALSE
#define CGINTRINSIC	TRUE
#define NOT_CGINTRINSIC	FALSE
#ifdef TARG_ST
typedef enum {
   INTRN_UNDEF = 0,      /* Invalid value   -- only for debugging purpose.        */
   INTRN_OUT      ,      /* Out argument    -- C++ style (reference) par. passing */
   INTRN_IN       ,      /* In argument     -- par. passed by value               */
   INTRN_INOUT    ,      /* In/out argument -- C++ style (reference) par. passing */
} INTRN_INOUT_TYPE;

//TB: Add some proto info for multiple results
//Support for multiple results
struct proto_intrn_info
{
  // Proto Info
  unsigned char     argument_count;
  TYPE_ID 	    *arg_type;     /* Number of items in table: arg_count */
  INTRN_INOUT_TYPE *arg_inout;    /* Number of items in table: arg_count */
  //Internal info
  TYPE_ID return_type; //Resulting MTYPE for multiple res intrinsic
  unsigned char     arg_out_count;
  unsigned char     arg_in_count;
};
typedef struct proto_intrn_info proto_intrn_info_t;
#ifdef TARG_ST
//TB: Add some proto info for multiple results
// Use to get parameter information on the gcc tree, to know if a
// parameter is an input, an output or an inout parameter.
// This array is internal to the WHIRL translator.
BE_EXPORTED extern proto_intrn_info_t *Proto_Intrn_Info_Array;
#endif

#endif

// the info we store for each intrinsic
typedef struct intrn_info_t {
 mBOOL		is_by_val;
 mBOOL		is_pure;
 mBOOL		has_no_side_effects;
 mBOOL		never_returns;
 mBOOL		is_actual;
 mBOOL		is_cg_intrinsic;
 INTRN_RETKIND	return_kind;
 const char	*c_name;
 const char	*specific_name;
 const char	*runtime_name;
} intrn_info_t;
#ifdef TARG_ST
//TB: dynamic intrinsics support
BE_EXPORTED extern const intrn_info_t intrn_info_static[INTRINSIC_STATIC_COUNT+1];
BE_EXPORTED extern intrn_info_t *intrn_info;
// Use to get parameter information on the gcc tree, to know if a
// parameter is an input, an output or an inout parameter.
// This array is internal to the WHIRL translator.
inline proto_intrn_info_t *INTRN_proto_info(const INTRINSIC i) {
  FmtAssert(i > INTRINSIC_STATIC_COUNT,
	    ("Intrinsic proto info only available for extension intrinsic."));
  return &(Proto_Intrn_Info_Array[i - INTRINSIC_STATIC_COUNT - 1]);
}
#else
extern const intrn_info_t intrn_info[INTRINSIC_LAST+1];
#endif

inline BOOL INTRN_by_value (const INTRINSIC i)
{
  return intrn_info[i].is_by_val;
}

inline BOOL INTRN_is_pure (const INTRINSIC i)
{
  return intrn_info[i].is_pure;
}

inline BOOL INTRN_has_no_side_effects (const INTRINSIC i)
{
  return intrn_info[i].has_no_side_effects;
}

inline BOOL INTRN_never_returns (const INTRINSIC i)
{
  return intrn_info[i].never_returns;
}

inline BOOL INTRN_is_actual (const INTRINSIC i)
{
  return intrn_info[i].is_actual;
}

inline BOOL INTRN_cg_intrinsic (const INTRINSIC i)
{
  return intrn_info[i].is_cg_intrinsic;
}

inline INTRN_RETKIND INTRN_return_kind (const INTRINSIC i)
{
  return intrn_info[i].return_kind;
}

inline const char * INTRN_c_name (const INTRINSIC i)
{
  return intrn_info[i].c_name;
}

inline const char * INTRN_specific_name (const INTRINSIC i)
{
  return intrn_info[i].specific_name;
}

inline const char * INTRN_rt_name (const INTRINSIC i)
{
  return intrn_info[i].runtime_name;
}

#ifdef TARG_ST
BE_EXPORTED BOOL is_intrinsic_rt_name(const char *) ;


/** 
 * Function returns whether intrinsic can be implemented via
 * a runtime function call.
 * 
 * @param i 
 * 
 * @return 
 */
inline BOOL INTRN_runtime_exists(const INTRINSIC i)
{
  return (INTRN_rt_name(i)!=NULL);
}

//TB: Multiple result builtin support.

// Returm true if the param number
//num is an input or an inout param
inline BOOL INTRN_is_in_param(int num, proto_intrn_info_t  *built_info)
{
  //Out param come first, then inout and then out
  FmtAssert (num < built_info->argument_count,
	     ("Prototype mismatch for builtins: too many parameters"));

  return (built_info->arg_inout[num] == INTRN_IN || built_info->arg_inout[num] == INTRN_INOUT);
}

//Answer TRUE when at least one parameter is passed by reference for this intrinsics
inline BOOL INTRN_is_by_reference(proto_intrn_info_t  *built_info)
{
 return (built_info->arg_out_count >= 1);
}

// Return true if the param number
// num is an out or an inout param
inline BOOL INTRN_is_out_param(int num, proto_intrn_info_t  *built_info){
  //Out param come first, then inout and then out
  FmtAssert (num < built_info->argument_count,
	     ("Prototype mismatch for builtins: too many parameters"));

  return (built_info->arg_inout[num] == INTRN_OUT || built_info->arg_inout[num] == INTRN_INOUT);
}

inline BOOL INTRN_is_inout_param(int num, proto_intrn_info_t  *built_info){
  //Out param come first, then inout and then out
  FmtAssert (num < built_info->argument_count,
	     ("Prototype mismatch for builtins: too many parameters"));
  return (built_info->arg_inout[num] == INTRN_INOUT);
}

//Return the cumulated number of inout and out parameters
inline int INTRN_number_of_out_param(proto_intrn_info_t  *built_info){
  return (built_info->arg_out_count);
}

//Return the cumulated number of inout and in parameters
inline int INTRN_number_of_in_param(proto_intrn_info_t  *built_info){
  return (built_info->arg_in_count);
}

//Return the buitin return type.
inline TYPE_ID INTRN_return_type(proto_intrn_info_t  *built_info){
  return built_info->return_type;
}
#endif
#ifdef TARG_ST
//[TB] To map info for extension intrinsic from dll to return kind
BE_EXPORTED INTRN_RETKIND INTRN_return_kind_for_mtype (const TYPE_ID mtype);
BE_EXPORTED TYPE_ID INTRN_mtype_for_return_kind(const INTRN_RETKIND kind);

#endif //TARG_ST

#endif
