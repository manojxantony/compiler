C
C Copyright (C) 2007. PathScale, LLC. All Rights Reserved.
C
C
C
C  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.
C
C  This program is free software; you can redistribute it and/or modify it
C  under the terms of version 2.1 of the GNU Lesser General Public License 
C  as published by the Free Software Foundation.
C
C  This program is distributed in the hope that it would be useful, but
C  WITHOUT ANY WARRANTY; without even the implied warranty of
C  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
C
C  Further, this software is distributed without any warranty that it is
C  free of the rightful claim of any third person regarding infringement 
C  or the like.  Any license provided herein, whether implied or 
C  otherwise, applies only to this software file.  Patent licenses, if
C  any, provided herein do not apply to combinations of this program with 
C  other software, or any other product whatsoever.  
C
C  You should have received a copy of the GNU Lesser General Public 
C  License along with this program; if not, write the Free Software 
C  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
C  USA.
C
C  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
C  Mountain View, CA 94043, or:
C
C  http://www.sgi.com
C
C  For further information regarding this notice, see:
C
C  http://oss.sgi.com/projects/GenInfo/NoticeExplan
C
C



#if defined(BUILD_COMPILER_GNU)
	subroutine underscore_I1I4GEMMX
     $			( m, n, k, alpha, a, inc1a, inc2a, 
     $			b, inc1b, inc2b, beta, c, inc1c, inc2c )
#else /* defined(BUILD_COMPILER_GNU) */
	subroutine _I1I4GEMMX
     $			( m, n, k, alpha, a, inc1a, inc2a, 
     $			b, inc1b, inc2b, beta, c, inc1c, inc2c )
#endif /* defined(BUILD_COMPILER_GNU) */
CDIR$ ID "@(#) libfi/matrix/i1i4gemmx.f	92.0	10/08/98 14:37:14"
	entry I1I4GEMMX_
     $			( m, n, k, alpha, a, inc1a, inc2a, 
     $			b, inc1b, inc2b, beta, c, inc1c, inc2c )
        integer(KIND=4) alpha, beta
C       integer*4       alpha, beta
        integer(KIND=4) temp
C       integer*4       temp
        integer(KIND=1) a( * )
C       integer*1       a( * )
        integer(KIND=4) b( * )
C       integer*4       b( * )
        integer(KIND=4) c( * )
C       integer*4       c( * )

	include 'xgemmx.h'
