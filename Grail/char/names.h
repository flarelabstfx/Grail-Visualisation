//#This comes from Grail-3.3.5
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent. 
//	January 1996



/*
 * Last Modified by CC to add new filters.
 * 
 */ 

const char* fcmenum		=       "fcmenum"; // Added in 3.1
const char* fcmexec		=	"fcmexec"; // Added in 3.1
const char* fcmmin		=	"fcmmin"; // Added in 3.1.3
const char* fcmtofm		=	"fcmtofm"; // Added in 3.1.1

const char* fcmtofm0		=	"fcmtofm0"; // Added in 2010 summer
const	char*	fmcomp		= 	"fmcomp";
const	char*	fmcment		= 	"fmcment";
const	char*	fmcat		= 	"fmcat";
const	char*	fmcatsize	= 	"fmcatsize";// Added in 3.4.2
const	char*	fmcatrsize	= 	"fmcatrsize";;// Added in 3.4.2
const	char*	fmcatmsize	= 	"fmcatmsize";;// Added in 3.4.2a
const	char*	fmcross		= 	"fmcross";
const	char*	fmenum		= 	"fmenum";
const    char*  fmenum1     =   "fmenum1"; //added in version yong
const	char*	fmenum2		= 	"fmenum2"; // added in version yong
const   char*   fmenum3     =   "fmenum3"; // added in version yong
const	char*	fmexec		= 	"fmexec";
const	char*	fmmin		= 	"fmmin";
const	char*	parmin		= 	"parmin"; //added in 3.1.3 
const	char*	fmminrev	= 	"fmminrev";
const   char*   fmmindis        =       "fmmindis"; //Added in 3.3.5
const	char*	fmorder	        = 	"fmorder"; // Added in 3.1.2
const	char*	fmplus		= 	"fmplus";
const	char*	fmrenum		= 	"fmrenum";
const	char*	fmreverse	= 	"fmrevers";
const	char*	fmsuff		= 	"fmsuff"; //Added in 3.4.3
const	char*	fmpref		= 	"fmpref"; //Added in 3.4.3
const	char*	fmdis		= 	"fmdis"; //Added in 3.4.3
const	char*	fmreach		= 	"fmreach";
const	char*	fmshuffle	= 	"fmshuffle";
const	char*	fmshuffleq	= 	"fmshuffleq";
const	char*	fmstar		= 	"fmstar";
const	char*	fmstats		= 	"fmstats";
const   char*	fmtofcm		=	"fmtofcm";      // Added in 3.1
const   char*	nfmtofcm	=	"nfmtofcm";     // Added in 3.4.2c
const	char*	fmtofcm2	=	"fmtofcm2";     // Added in 3.1
const	char*	fmtofcm0	=	"fmtofcm0"; 	// Added in 2010 summer
const	char*	fmreduce	=	"fmreduce"; 	// Added in 2010 summer
const	char*	fmuseful	=	"fmuseful"; 	// Added in 2010 summer
const	char*	nfatodfa	=	"nfatodfa"; 	// Added in 2010 summer
const	char*	nfatodfca	=	"nfatodfca"; 	// Added in 2010 summer
const	char*	fmadmatrix	=	"fmadmatrix"; 	// Added in 2010 summer
const	char*	fmpermutation	=	"fmpermutation"; 	// Added in 2010 summer
const	char*	fcmcomp	        =	"fcmcomp";              //2011
const	char*	flsimset	=	"flsimset";             //2011
const	char*	fleqset	        =	"fleqset";              //2011
const	char*	fmfastgap	=	"fmfastgap"; 	// Added in 2011 summer
const	char*	inttofl	        =	"inttofl"; 	// Added in 2011 summer
const	char*	fltoint	        =	"fltoint"; 	// Added in 2011 summer
const	char*	inputTest	=	"inputTest"; 	// Added in 2011 summer

const	char*	fmtore		= 	"fmtore";
const	char*   fmtofl          =       "fmtofl";
const	char*	fmunion		= 	"fmunion";
const	char*	fmunionsize	= 	"fmunionsize"; //Added in 3.4.2
const	char*	fmunionrsize	= 	"fmunionrsize"; //Added in 3.4.2
const	char*	fmunionmsize	= 	"fmunionmsize"; //Added in 3.4.2a

const   char*   dfaunion        =       "dfaunion";
const	char*	fmdeterm	= 	"fmdeterm";
const	char*   flappend        =       "flappend";
const	char*   flexec          =       "flexec";
const	char*   flfilter        =       "flfilter";
const	char*   fllq            =       "fllq";
const	char*   flprepend       =       "flprepen";
const	char*   flprod          =       "flprod";
const	char*   flreverse       =       "flrevers";
const	char*   flrq            =       "flrq";
const	char*   flsubclose      =       "flsubclose";
const	char*   fltore          =       "fltore";
const	char*   fltofm          =       "fltofm";
const	char*   fltofmmn        =       "fltofmmn";    // Added in 3.1.2
const   char*   fltofcm		=	"fltofcm";     // Added in 3.1
const	char*   flunion         =       "flunion";
const	char*	iscomp		= 	"iscomp";
const	char*	isdeterm	= 	"isdeterm";
const	char*	isomorph	= 	"isomorph";
const	char*	isuniv		= 	"isuniv";
const   char*   fmsize          =       "fmsize";

const	char*	recat		= 	"recat";
const	char*	remin		= 	"remin";
const	char*	reunion		= 	"reunion";
const	char*	restar		= 	"restar";
const	char*	retofm		= 	"retofm";
const	char*	retofl		= 	"retofl";
const	char*	isnull		= 	"isnull";
const	char*	isempty		= 	"isempty";
const	char*	fmisempty	= 	"fmisempty";
const   char*   afatofm         =       "afatofm";
const   char*   fmtoafa         =       "fmtoafa";
const   char*   afaexec         =       "afaexec";
const   char*   afacomp         =       "afacomp";
const   char*   afaunion        =       "afaunion";
const   char*   afainter        =       "afainter";
const   char*   litafa          =       "litafa";
const   char*   afasize         =       "afasize";
const   char*   afareverse      =       "afareverse";
const   char*   afastar         =       "afastar";
const   char*   afacaten        =       "afacaten";

const   char*   fmrandenum        =       "fmrandenum";


