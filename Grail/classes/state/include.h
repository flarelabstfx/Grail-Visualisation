//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	August 1994

/***************************************************************************

  File:  classes/state/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the state class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/06/04         Added header and comments

 ***************************************************************************/

#ifndef STATE_INCLUDE_H
#define STATE_INCLUDE_H

#include	<iostream>


/* Added namespace grail, Brandon Stewart, July 2015 */
namespace grail
{

#include	"state.h"
#include	"istream.src"
#include	"minuseq.src"
#include	"ostream.src"

}


#endif
