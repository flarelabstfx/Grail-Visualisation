//#This comes from 3.1.4-new; modified by ray and sherry in summer 2010
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	June 1995

/***************************************************************************

  File:  classes/array/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the array class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/05/25         Added header and comments

 ***************************************************************************/
 #ifndef ARRAY_INCLUDE_H
 #define ARRAY_INCLUDE_H

 #include	<iostream>


 #include	<ctype.h>
 #include	<stdlib.h>


namespace grail
{


#include	"defs.h"
#include	"array.h"

#include	"assign.src"
#include	"compare.src"
#include	"contain.src"
#include	"eq.src"
#include	"member.src"
#include	"array.src"
#include	"lt.src"
#include	"merge.src"
#include	"minuseq.src"
#include	"pluseq.src"
#include	"remove.src"
#include	"sort.src"
#include	"unique.src"
#include        "fistream.src"
#include        "fostream.src"
#include        "compare_length.src"
#include        "sort_length.src"

}

#endif
