//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	February 1995

#ifndef MEALY_INCLUDE_H
#define MEALY_INCLUDE_H

/* Added namespace grail, Brandon Stewart, July 2015 */
namespace grail
{

#include	"mealy.h"
#include	"assign.src"
#ifdef	WATCOM
#include	"ostream.src"
#endif
#include	"dmember.src"
#include	"member.src"
#include	"select.src"

}

#endif
