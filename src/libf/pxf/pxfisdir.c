/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

   Path64 is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation version 2.1

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


#pragma ident "@(#) libf/pxf/pxfisdir.c	92.1	06/29/99 11:36:06"

#include <liberrno.h>
#include <errno.h>
#include <fortran.h>
#include <sys/stat.h>

/*
 *  PXFISDIR  -- Test for directory file
 *  (section 5.6.1 of Posix 1003.9-1992)
 *
 *  Synopsis:
 *     LOGICAL FUNCTION PXFISDIR(M)
 *     INTEGER M
 *
 *  Function description:
 *  The logical function PXFISDIR checks if a file is a
 *  directory file. The value M should be supplied by
 *  the st_mode component of the stat structure used by
 *  the PXFSTAT routine.
 *
 *  Description of arguments:
 *  M is an input integer variable containing the file mode.
 *
 *  Return values:
 *  If the file is a directory file, PXFISDIR returns
 *  a logical true, otherwise a logical false is returned.
 */

#ifdef _UNICOS
_f_int
PXFISDIR(
#else
_f_int
_PXFISDIR(
#endif
	  _f_int *M
)
{
  return _btol(S_ISDIR((int)*M));
}

#ifndef _UNICOS
_f_int
pxfisdir_(
	  _f_int *M
)
{
  return _PXFISDIR(M);
}
#endif
