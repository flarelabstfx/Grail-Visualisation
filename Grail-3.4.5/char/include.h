//#This comes from Grail-3.3.5
/*
 #include	<stdlib.h>
 #include	<iostream.h>
 #include	<fstream.h>
 #include	<strstream.h>
 #include	<string.h>
 #include	<ctype.h>
 */
#include    <stdio.h>
#include	<stdlib.h>
#include     <iostream>


#include	<fstream>

//by ray for special debug
#include       <strstream>
#include	<string.h>
#include	<ctype.h>  //by SH 05/20/2005
#include	<stdlib.h>



/* added/modified by Brandon Stewart, July 2015 
 
  Base classes moved to backbone folder.
*/ 

#include      "../backbone/bits/include.h"
#include      "../backbone/array/include.h"
#include      "../backbone/set/include.h"
#include      "../backbone/pool/include.h"
#include      "../backbone/list/include.h"
#include      "../backbone/pair/include.h"
#include      "../backbone/tuple/include.h"//yong 2018/07/18


#include      "../classes/atstate/include.h" // Added in 3.1.2
//#include      "../classes/bits/include.h"
#include      "../classes/state/include.h"
//#include      "../classes/array/include.h"
//#include      "../classes/set/include.h"
//#include      "../classes/pool/include.h"
//#include      "../classes/list/include.h"
#include      "../classes/string/include.h"
//#include      "../classes/pair/include.h"
#include      "../classes/inst/include.h"
#include      "../classes/re/include.h"
#include      "../classes/fcm/include.h" // Added in 3.1
#include      "../classes/fm/include.h"
#include      "../classes/fl/include.h"
#include      "../classes/mealy/include.h"
#include      "../classes/afa/dnf/include.h"
#include      "../classes/afa/include.h"


/* Added namespace grail, Brandon Stewart, July 2015 */

namespace grail
{

template<>
  char string<char>::separator = '\0';
template<>
  char string<int>::separator = ' ';
template<>
  char string<unsigned int>::separator = ' ';
template<>
  char string<long>::separator = ' ';
template<>
  char string<unsigned long>::separator = ' ';
template<>
  char string<float>::separator = ' ';
template<>
  char string<double>::separator = ' ';

#ifdef          WATCOM
#include      "dosnames.h"
#endif

#ifndef         WATCOM
#include      "names.h"
#endif

typedef void
(*PF)(); // pointer to function

extern PF
set_new_handler(PF);

void
new_error()
{
  std::cerr << "new failed\n";
  exit(-1);
}

}
