//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	June 1995


/***************************************************************************

  File:  classes/set/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the set class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/05/30         Added header and comments

 ***************************************************************************/
 #ifndef SET_INCLUDE_H
 #define SET_INCLUDE_H

 #include	<iostream>  //by SH 05/20/2005
 #include	<ctype.h>
 #include	<stdlib.h>


namespace grail
{

#include	"set.h"
#include	"contain.src"
#include	"eq.src"
#include	"list.src"
#include	"lt.src"
#include	"intersct.src"
#include	"member.src"
#include	"minuseq.src"
#include	"ostream.src"
#include	"pluseq.src"

}

#endif
