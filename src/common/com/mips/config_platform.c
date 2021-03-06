/*
 *  Copyright (C) 2008 PathScale, LLC.  All Rights Reserved.
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


/* ====================================================================
 * ====================================================================
 *
 * Module: config_platform.c
 * $Revision: 1.4 $
 * $Date: 05/03/02 15:28:07-08:00 $
 * $Author: bos@eng-24.internal.keyresearch.com $
 * $Source: common/com/mips/SCCS/s.config_platform.c $
 *
 * Revision history:
 *  11-May-96 - Original Version
 *
 * Description:
 *
 * Configuration for the various platforms supported by the compiler.
 * This package is used to configure certain platform-specific options
 * like the -Ofast option set and cache configuration for LNO.
 *
 * This is separate from config_targ because it has a very small set
 * of clients, whereas config_targ.h is included in config.h and hence
 * everywhere.
 *
 * NOTE:  There is an outstanding bug, PV 378171, to base this
 * functionality on an external configuration file.
 *
 * ====================================================================
 * ====================================================================
 */

static char *source_file = __FILE__;

#ifdef _KEEP_RCS_ID
static char *rcs_id = "$Source: common/com/mips/SCCS/s.config_platform.c $ $Revision: 1.4 $";
#endif /* _KEEP_RCS_ID */

#include <string.h>
#include "config_platform.h"

PLATFORM Platform = IP0;	/* Target platform */

/* Per-processor settings: */
static PLATFORM_OPTIONS PF_Opts[] =
{
  /* This is the default -- it must be first.  Nickname is used for
   * default warning messages:
   */
  { IP0, "ip??", "mips5kf", PROC_MIPS5KF, "mips5kf" },
  { IP0, "ip??", "twc9a",   PROC_TWC9A,   "twc9a" },

  { IP_END,	"",	"",	PROC_NONE, "End of list" } /* Must be last */
};

PLATFORM_OPTIONS *
Get_Platform_Options ( char *name )
{
  int ix;

  /* Default for no name or empty name: */
  if ( name == NULL || *name == 0 ) {
    return &PF_Opts[0];
  }

  /* Find matching entry in table: */
  for ( ix=1; PF_Opts[ix].id != IP_END; ix++ ) {
    if ( strcasecmp ( name, PF_Opts[ix].name ) == 0 ) {
      return &PF_Opts[ix];
    }
  }

  /* No match -- default it: */
  return &PF_Opts[0];
}
