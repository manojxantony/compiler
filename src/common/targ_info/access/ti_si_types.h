/*
 * Copyright (C) 2007 PathScale, LLC.  All Rights Reserved.
 */
/*
 * Copyright 2003, 2004, 2005, 2006 PathScale, Inc.  All Rights Reserved.
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


/* See ti_si.h for detailed interface description.  */

#ifndef TI_SI_TYPES_H_INCLUDED
#define TI_SI_TYPES_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
typedef enum topcode TOPCODE;
#include <topcode.h>

#define TI_SI_CONST const
/****************************************************************************
 ****************************************************************************/

typedef struct {
  mUINT64 dw[2];
} SI_BAD_II_SET;

enum { SI_BAD_II_SET_MAX=127 };

/****************************************************************************
 ****************************************************************************/

typedef UINT SI_RESOURCE_ID;

typedef struct {
  const char* name;
  SI_RESOURCE_ID id;
  mUINT8 avail_per_cycle;
  mUINT8 word_index;
  mUINT8 bit_index;
} SI_RESOURCE;

/****************************************************************************
 ****************************************************************************/

typedef mUINT64 SI_RESOURCE_ID_SET;


/****************************************************************************
 ****************************************************************************/

/* SI_RRW -- A resource reservation word */
typedef mUINT64 SI_RRW;

/****************************************************************************
 ****************************************************************************/

typedef struct {
  const char* name;
  mINT32 skew;
  mINT32 avail_per_cycle;
} SI_ISSUE_SLOT;

/****************************************************************************
 ****************************************************************************/

typedef TI_SI_CONST struct {
  const SI_RESOURCE* resource;
  mINT32 total_used;
} SI_RESOURCE_TOTAL;

/****************************************************************************
 ****************************************************************************/

typedef TI_SI_CONST SI_RRW* SI_RR;

/****************************************************************************
 ****************************************************************************/
typedef UINT SI_ID;

typedef struct {
  const char* name;
  SI_ID id;
  TI_SI_CONST mUINT8 *operand_access_times;
  TI_SI_CONST mUINT8 *result_available_times;
  mINT32 load_access_time;
  mINT32 last_issue_cycle;
  mINT32 store_available_time;
  SI_RR rr;
  TI_SI_CONST SI_RESOURCE_ID_SET *resources_used;
  mUINT32 ii_info_size;
  TI_SI_CONST SI_RR *ii_rr;
  TI_SI_CONST SI_RESOURCE_ID_SET * TI_SI_CONST *ii_resources_used;
  SI_BAD_II_SET bad_iis;
  mINT32 valid_issue_slot_count;
  TI_SI_CONST SI_ISSUE_SLOT * TI_SI_CONST *valid_issue_slots;
  mINT32 resource_total_vector_size;
  SI_RESOURCE_TOTAL *resource_total_vector;
  mUINT8 write_write_interlock;
} SI;

/****************************************************************************
 ****************************************************************************/

typedef struct {
  const SI * const *top_si;
  const SI * const *ID_si;
  int ID_count;
  const SI_ISSUE_SLOT * const *issue_slots;
  int issue_slot_count;
  const SI_RESOURCE * const *resources;
  int resource_count;
  SI_RRW RRW_initializer;
  SI_RRW RRW_overuse_mask;
  const char *target_name;
} SI_SUMMARY;

/****************************************************************************
 ****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif
