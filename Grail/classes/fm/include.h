//#This comes from Grail-3.3.5
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	January 1994


/***************************************************************************

  File:  classes/fm/include.h
  -----

  Description:
  ------------
    This file contains all the include statements required for compiling
    the fm class.

  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/09/09         Added header and comments
	 Jason Smith  7/6/2005				Added new entries for Grail 3.1.2

 ***************************************************************************/

#ifndef FM_INCLUDE_H
#define FM_INCLUDE_H

 #include <vector>
 #include <iostream>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 //#include<iostream.h>
 #include <math.h>
 #include <queue>
 #include <sstream>
 #include "../stenum.h"

 #include <random>
 
/* Added namespace grail, Brandon Stewart, July 2015 */

namespace grail
{

#include	"fm.h"
#include	"assign.src"
#include        "attach.src"
#include	"cartesan.src"
#include	"complete.src"
#include	"compment.src"
#include	"catenate.src"
#include	"cross.src"
#include        "dfaunion.src"
#include	"disjoint.src"
#include	"enum.src"
#include    "enum_copy1.cpp" //added by Yong 2018/07/10/July/2018
#include    "enum_copy3.cpp" //added by Yong 2018/07/24/July/2018
//#include    "enum_copy4.cpp" //added by Yong 2018/07/24/July/2018
#include	"enum2.cpp"
#include	"estring.src"
#include	"eq.src"
#include	"flfilter.src"
#include	"flsubclose.src"
#include	"fltofm.src"
#include        "fltofmmn.src"
#include	"fmtofl.src"
#include	"iscomp.src"
#include	"isdeterm.src"
#include	"isfinite.src"
#include	"istream.src"
#include	"isuniv.src"
#include	"labels.src"
#include	"maxstat.src"
#include	"member.src"
#include	"minbyp.src"
#include	"minbyr.src"
#include	"minuseq.src"
#include	"number.src"
#include        "order.src"
#include	"ostream.src"
#include	"plus.src"
#include	"pluseq.src"
#include	"reach.src"
#include	"reach2.src"
#include	"remove.src"
#include	"renumber.src"
#include	"reverse.src"
#include	"suffix.src"
#include	"disting.src"
#include	"prefix.src"
#include 	"ror.src"
#include	"select.src"
#include	"shuffle.src"
#include	"shuffleq.src"
#include	"single.src"
#include	"sinks.src"
#include	"sources.src"
#include	"star.src"
#include	"stats.src"
#include	"states.src"
#include	"subset.src"
//#include 	"parmin.src" Removed as it is not mandatory; creates compiling problems
#include 	"map.src"//ray 2010 summer
#include        "fmtofcm0.src"

#include 	"useful.src"//ray 2010 summer
#include        "reduce.src"
#include        "nfatodfa.src"
#include        "nfatodfca_forTest.src"
#include 	"findlev.src"
#include 	"ad_matrix.src"
#include 	"permutation.src"

//fast gap algprithm
#include	"fastgap/node.h"
#include	"fastgap/fastgap.src"

    
#include        "fmrandenum.src" // included by Xuejun Du, 2018/06/30/June/2018 

}

#endif
