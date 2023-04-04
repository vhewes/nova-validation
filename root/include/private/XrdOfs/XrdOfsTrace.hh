#ifndef ___OFS_TRACE_H___
#define ___OFS_TRACE_H___
/******************************************************************************/
/*                                                                            */
/*                        X r d O f s T r a c e . h h                         */
/*                                                                            */
/* (C) 2003 by the Board of Trustees of the Leland Stanford, Jr., University  */
/*                            All Rights Reserved                             */
/*   Produced by Andrew Hanushevsky for Stanford University under contract    */
/*               DE-AC02-76-SFO0515 with the Deprtment of Energy              */
/*                                                                            */
/* This file is part of the XRootD software suite.                            */
/*                                                                            */
/* XRootD is free software: you can redistribute it and/or modify it under    */
/* the terms of the GNU Lesser General Public License as published by the     */
/* Free Software Foundation, either version 3 of the License, or (at your     */
/* option) any later version.                                                 */
/*                                                                            */
/* XRootD is distributed in the hope that it will be useful, but WITHOUT      */
/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public       */
/* License for more details.                                                  */
/*                                                                            */
/* You should have received a copy of the GNU Lesser General Public License   */
/* along with XRootD in a file called COPYING.LESSER (LGPL license) and file  */
/* COPYING (GPL license).  If not, see <http://www.gnu.org/licenses/>.        */
/*                                                                            */
/* The copyright holder's institutional names and contributor's names may not */
/* be used to endorse or promote products derived from this software without  */
/* specific prior written permission of the institution or contributor.       */
/******************************************************************************/

#ifndef NODEBUG

#include "XrdSys/XrdSysHeaders.hh"
#include "XrdSys/XrdSysTrace.hh"
#include "XrdOfs/XrdOfs.hh"

#define GTRACE(act)         OfsTrace.What & TRACE_ ## act

#define TRACES(x) {SYSTRACE(OfsTrace.,tident,epname,0,x)}

#define FTRACE(act, x) \
   if (GTRACE(act)) \
      TRACES(x <<" fn=" << (oh->Name()))

#define XTRACE(act, target, x) \
   if (GTRACE(act)) TRACES(x <<" fn=" <<target)

#define ZTRACE(act, x) if (GTRACE(act)) TRACES(x)

#define DEBUG(x) if (GTRACE(debug)) TRACES(x)

#define EPNAME(x) static const char *epname = x;

#else

#define FTRACE(x, y)
#define GTRACE(x)    0
#define TRACES(x)
#define XTRACE(x, y, a1)
#define YTRACE(x, y, a1, a2, a3, a4, a5)
#define ZTRACE(x, y)
#define DEBUG(x)
#define EPNAME(x)

#endif

// Trace flags
//
#define TRACE_MOST     0x3fcd
#define TRACE_ALL      0xffff
#define TRACE_opendir  0x0001
#define TRACE_readdir  0x0002
#define TRACE_closedir TRACE_opendir
#define TRACE_delay    0x0400
#define TRACE_dir      TRACE_opendir | TRACE_readdir | TRACE_closedir
#define TRACE_open     0x0004
#define TRACE_qscan    0x0008
#define TRACE_close    TRACE_open
#define TRACE_read     0x0010
#define TRACE_redirect 0x0800
#define TRACE_write    0x0020
#define TRACE_IO       TRACE_read | TRACE_write | TRACE_aio
#define TRACE_exists   0x0040
#define TRACE_chmod    TRACE_exists
#define TRACE_getmode  TRACE_exists
#define TRACE_getsize  TRACE_exists
#define TRACE_remove   0x0080
#define TRACE_rename   TRACE_remove
#define TRACE_sync     0x0100
#define TRACE_truncate 0x0200
#define TRACE_fsctl    0x0400
#define TRACE_getstats 0x0800
#define TRACE_mkdir    0x1000
#define TRACE_stat     0x2000
#define TRACE_aio      0x4000
#define TRACE_debug    0x008000
#define TRACE_chkpnt   0x010000

#endif
