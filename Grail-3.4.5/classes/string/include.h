//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	January 1994


/***************************************************************************

  File:  classes/string/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the string class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/06/03         Added header and comments

 ***************************************************************************/
#ifndef STRING_INCLUDE_H
#define STRING_INCLUDE_H

 #include	<iostream> //by SH 05/20/2005
 #include <fstream>
 #include	<string.h>
 #include	<ctype.h>
 
 
 
/* Added namespace grail, Brandon Stewart, July 2015 */

namespace grail
{

#include	"string.h"
#include	"istream.src"
#include	"lt.src"
#include	"ostream.src"
#include	"reverse.src"
#include	"string.src"
#include	"strcmp.src"

}

#endif
