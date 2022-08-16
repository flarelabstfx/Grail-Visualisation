//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	January 1994


/***************************************************************************

  File:  classes/inst/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the inst class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/06/03         Added header and comments

 ***************************************************************************/

 #ifndef INST_INCLUDE_H
 #define INST_INCLUDE_H

 #include	<strstream>
 
/* Added namespace grail, Brandon Stewart, July 2015 */
namespace grail
{
#include	"inst.h"
#include	"std.h"
#include	"defs.h"
#include	"istream.src"
#include	"lt.src"
#include	"ostream.src"
}

#endif
