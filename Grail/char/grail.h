/* File grail.h
 Licence: LGPL
 Added in this format by CC to the Grail project on February 1, 2014

*/
/* namespace grail: added by Brandon Stewart, July 2015 */
using namespace grail;

#define MAX_PATH 512

char* Version=(char*)"Grail Version 3.4.5";

void get_one(fm<char>& a, int argc, char** argv, char* my_name);
void get_two(fm<char>& a, fm<char>& b, int argc, char** argv, char* my_name);
void get_one(re<char>& a, int argc, char** argv, char* my_name);
void get_two(re<char>& a, re<char>& b, int argc, char** argv, char* my_name);
void get_one(fl<char>& a, int argc, char** argv, char* my_name);
void get_two(fl<char>& a, fl<char>& b, int argc, char** argv, char* my_name);
void get_two(fl<char>& a, string<char>& b, int argc, char** argv, char* my_name);
void get_one(afa<char>& a, int argc, char** argv, char* my_name);
void get_two(afa<char>& a, afa<char>& b, int argc, char** argv, char* my_name);
void get_afa(afa<char>& a, int argc, char** argv, char* my_name);

// The following two functions were added for cover automata in 3.1
void get_one(fcm<char>& a, int argc, char** argv, char* my_name);
void get_two(fcm<char>& a, fcm<char>& b, int argc, char** argv, char* my_name);

//Displays a short help note if the first argument is '--help'
void print_help(const char* filter_name);

//Displays the version of grail that we're using, if the first argument is '--version'
void print_version(char*);
