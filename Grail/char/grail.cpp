//#This comes from Grail-3.3.5
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	January 1996
// Update February 1 2014 CC
// Update August 19 2013 CC


// Added in version 3.3.4,changed by ray
// May 1 2012 Ray

// updated July 2015, Brandon Stewart
// updated by Yong Yu, August 2018

int debug = 0;
char* nfatodfca_name = (char*)""; //for special debug

#include        "include.h"
#include	"lexical.h"
#include	"grail.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char** argv)
{
 int i;

// debug info can be set for different level, currently we have:
// level 1: core level
// level 9: show everything
//handle debug mode-core debug info
  if (argc > 1 && strcmp(argv[1], "-d") == 0)
    {
      std::cout << "---[ Debug Mode On ( show core debug info) ]---" 
      << std::endl;
      debug = 1;
      for (int a = 1; a < argc; a++)
        argv[a] = argv[a + 1];
      argc--;
    }

  //handle debug mode - full debug info
  if (argc > 1 && strcmp(argv[1], "-da") == 0)
    {
      std::cout << "---[ Debug Mode On ( show all debug info) ]---" 
      << std::endl;
      debug = 9;
      for (int a = 1; a < argc; a++)
        argv[a] = argv[a + 1];
      argc--;
    }

  // special tests for nfatodfca
  if (argc > 1 && strcmp(argv[1], "-dnc") == 0)
    {
      std::cout << "[ Special debug for nfatodfca is Activated ]" 
      << std::endl;
      debug = -1;
      nfatodfca_name = argv[2];
      for (int a = 1; a < argc; a++)
        argv[a] = argv[a + 1];
      argc--;
    }

// get my name argv[0];
  for (i = strlen(argv[0]); i > 0; --i)
    if ((argv[0][i] == '/') || (argv[0][i] == '\\'))
      {
        ++i;
        break;
      }
  char *my_name = new char[strlen(argv[0] + i)];
  strcpy(my_name,argv[0] + i);
//std::cout<<"["<<my_name<<"]\n";

  char *my_path;
  my_path = new char[MAX_PATH];

//Linux/Unix  is in grail/binaries/UNIXTYPE/char.out
//
// Windows/DOS names are in grail/bin/file.exe
// only grail root is preserved

#ifdef WIN32
  GetModuleFileName( NULL, my_path, MAX_PATH );
#else
#ifdef WIN64
  GetModuleFileName( NULL, my_path, MAX_PATH );
#else
  size_t count = readlink( "/proc/self/exe", my_path, MAX_PATH );
  for (i = strlen(my_path); i > 0; --i)
    if ((my_path[i] == '/') || (my_path[i] == '\\'))
      {
        break;
      }
my_path[i]='\0';
#endif
#endif

for (i = strlen(my_path); i > 0; --i)
    if ((my_path[i] == '/') || (my_path[i] == '\\'))
      {
        break;
      }
my_path[i]='\0';
for (i = strlen(my_path); i > 0; --i)
    if ((my_path[i] == '/') || (my_path[i] == '\\'))
      {
        break;
      }
my_path[i]='\0';

// std::cout<<"["<<my_path<<"]\n";


//added by CC in Version 3.3.4, Jan 14 2008.
// The whole code for finding arguments should
// be rewritten from scratch.

  if (argc == 2)
    {
      //Added in 3.3.3  Aug. 8th, 2007
      //If the first argument is "--help", then print out
      // help using 'print_help()', and exit
      if (strcmp(argv[1], "--help") == 0)
        {
          print_help(my_name);
          return 0;
        }

      //Added in 3.3.3 Aug. 9th, 2007
      //Prints out the version if "--version" is the first argument
      if (strcmp(argv[1], "--version") == 0)
        {
          print_version(my_path);
          return 0;
        }

    }

  // do the operation that I'm named
  if (strcmp(my_name, fcmenum) == 0) // Added in 3.1
    {
      int i = 100;
      set<string<char> > results;

      // extract number, if present

      if (argc > 1 && strcmp(argv[1], "-n") == 0)
        {
          if (argc < 3)
            {
              std::cerr << "usage: " << my_name << " [-n size] fm\n";
              return 1;
            }

          i = atoi(argv[2]);
          argv[1] = argv[3];
          argc -= 2;
        }
      fcm<char> a;
      get_one(a, argc, argv, my_name);

      int j = a.enumerate(i, results);
       
        
      // print number of requested results or total set, whichever
      // is smaller

      if (j < i)
        i = j;

      for (j = 0; j < i; ++j)
        std::cout << results[j] << "\n";

      return 0;
    }

  if (strcmp(my_name, fcmexec) == 0) // Added in 3.1
    {
      int i = 0;
      string<char> str;
      std::fstream fio;
      std::istrstream ist(argv[argc - 1]);
      fcm<char> a;

      // handle arguments

      switch (argc)
        {
      case 4:
        if (strcmp(argv[1], "-d") != 0)
          {
            std::cerr << "usage: " << my_name << " [-d] fm string\n";
            return 1;
          }

        i = 1;
        fio.open(argv[2], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[2] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();

        ist >> str;
        break;

      case 3: // automaton is arriving on stdin

        if (strcmp(argv[1], "-d") == 0)
          {
            ist >> str;
            i = 1;
            std::cin >> a;
            break;
          }

        fio.open(argv[1], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();

        ist >> str;
        break;
      case 2:
        ist >> str;
        std::cin >> a;
        break;

      default:
        std::cerr << "usage: " << my_name << " [-d] fm string\n";
        return 1;
        }

      if (a.member_of_language(str, i))
        std::cout << "accepted\n";
      else
        std::cout << "not accepted\n";
      return 0;

    }

  if (strcmp(my_name, fcmmin) == 0)
    {
      fcm<char> c;
      get_one(c, argc, argv, my_name);
      if (debug)
        {
          std::cout << "in grail.cpp,fcmmin , input is : " << std::endl;
          std::cout << c << std::endl;
        }
      std::cout << c.fcmmin();
      return 0;

    }

  if (strcmp(my_name, fcmtofm) == 0)
    {
      fcm<char> c;
      fm<char> a;
      get_one(c, argc, argv, my_name);
      std::cout << c.fcmtofm(a);
      return 0;

    }

  if (strcmp(my_name, inputTest) == 0)
    {

      fm<char> a;
      get_one(a, argc, argv, my_name);
      std::cout << a.size();
      return 0;

    }

  if (strcmp(my_name, fcmtofm0) == 0)
    {
      fcm<char> c;
      fm<char> a;
      get_one(c, argc, argv, my_name);
      std::cout << c.fcmtofm0(a);
      return 0;

    }
/* Moved
  if (strcmp(my_name, fmcment) == 0)
    {
     fm<char> a;
     get_one(a, argc, argv, my_name);
     a.complement();
     std::cout << a;
     return 0;
    }
*/

  if (strcmp(my_name, fcmcomp) == 0)
    {
      fcm<char> c;
      get_one(c, argc, argv, my_name);

      c.fm<char>::complete();
      std::cout << c;
      return 0;

    }

  if (strcmp(my_name, fmcomp) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.complete();
      a.unattach();
      std::cout << a;
      return 0;
    }



  if (strcmp(my_name, fmreduce) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.reduce();
      std::cout << a;
      return 0;
    }
  if (strcmp(my_name, fmadmatrix) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      //std::cout << a;
      a.ad_matrix();

      return 0;
    }

  if (strcmp(my_name, fmpermutation) == 0)
    {
      fm<char> a, b;

      std::fstream f_arg;

      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
      b = fm<char>(a);

      std::ifstream ifs(argv[2]);
      std::string temp;

      while (getline(ifs, temp))
        {
          a.permutation(temp);
          std::cout << a;

          a = fm<char>(b);

        }

      return 0;
    }

  if (strcmp(my_name, fmuseful) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.useful_fm();
      std::cout << a;
      return 0;
    }
  if (strcmp(my_name, fmcment) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.complement();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmcat) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a ^= b;
      std::cout << a;
      return 0;
    }

if (strcmp(my_name, fmcatsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a ^= b;
      a.subset();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }
if (strcmp(my_name, fmcatrsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a ^= b;
      a.subset();
      a.reduce();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }

if (strcmp(my_name, fmcatmsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a ^= b;
      a.subset();
      a.reduce();
      a.min_by_partition();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }



  if (strcmp(my_name, fmcross) == 0)
    {
      fm<char> a;
      fm<char> b;
      fm<char> c;
      get_two(a, b, argc, argv, my_name);
      c.cross_product(a, b);
      std::cout << c;
      return 0;
    }

  if (strcmp(my_name, fmfastgap) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      i = atoi(argv[1]);

      a.fastgap(i);

      return 0;
    }

  if (strcmp(my_name, fmenum) == 0)
    {
      int i = 100;
      set<string<char> > results;

      // extract number, if present

      if (argc > 1 && strcmp(argv[1], "-n") == 0)
        {
          if (argc < 3)
            {
              std::cerr << "usage: " << my_name << " [-n size] fm\n";
              return 1;
            }

          i = atoi(argv[2]);
          argv[1] = argv[3];
          argc -= 2;
        }
      fm<char> a;
      get_one(a, argc, argv, my_name);
        
      int j = a.enumerate(i, results);
      
        
      // print number of requested results or total set, whichever
      // is smaller

      if (j < i)
        i = j;

      for (j = 0; j < i; ++j)
        std::cout << results[j] << "\n";

      return 0;
    }
  if (strcmp(my_name, fmenum1) == 0)// Yong added in 2017/07/11
    {
      int i = 100;
      set<string<char> > results;

      // extract number, if present

      if (argc > 1 && strcmp(argv[1], "-l") == 0)
        {
          if (argc < 3)
            {
              std::cerr << "usage: " << my_name << " [-l size] fm\n";
              return 1;
            }

          i = atoi(argv[2]);
          argv[1] = argv[3];
          argc -= 2;
        }
      fm<char> a;
      get_one(a, argc, argv, my_name);

        int j = a.enumerate1(i, results);// Yong: added in

      // print number of requested results or total set, whichever
      // is smaller

      for (j = 0; j < results.size(); ++j)
        std::cout << results[j] << "\n";

      return 0;
    }
    
    if (strcmp(my_name, fmenum2) == 0)
    {
        int i = 100;
        set<string<char> > results;
        
        // extract number, if present
        
        if (argc > 1 && strcmp(argv[1], "-l") == 0)
        {
            if (argc < 3)
            {
                std::cerr << "usage: " << my_name << " [-l size] fm\n";
                return 1;
            }
            
            i = atoi(argv[2]);
            argv[1] = argv[3];
            argc -= 2;
        }
        fm<char> a;
        get_one(a, argc, argv, my_name);
        
        int j = a.enumerate2(i, results);
        
        // print number of requested results or total set, whichever
        // is smaller
        
        for (j = 0; j < results.size(); ++j)
        std::cout << results[j] << "\n";
        
        return 0;
    }
    if (strcmp(my_name, fmenum3) == 0)// Yong added in 2017/07/11
    {
        int i = 100;
        set<string<char> > results;
        
        // extract number, if present
        
        if (argc > 1 && strcmp(argv[1], "-l") == 0)
        {
            if (argc < 3)
            {
                std::cerr << "usage: " << my_name << " [-l size] fm\n";
                return 1;
            }
            
            i = atoi(argv[2]);
            argv[1] = argv[3];
            argc -= 2;
        }
        fm<char> a;
        get_one(a, argc, argv, my_name);
        
        int j = a.enumerate3(i, results);// Yong: added in
        
        // print number of requested results or total set, whichever
        // is smaller
        
        for (j = 0; j < results.size(); ++j)
            std::cout << results[j] << "\n";
        
        return 0;
    }
    
    

  if (strcmp(my_name, fmexec) == 0)
    {
      int i = 0;
      string<char> str;
      std::fstream fio;
      std::istrstream ist(argv[argc - 1]);
      fm<char> a;
      int size;

      // handle arguments

      switch (argc)
        {
      case 4:
        if (strcmp(argv[1], "-d") != 0)
          {
            std::cerr << "usage: " << my_name << " [-d] fm string\n";
            return 1;
          }

        i = 1;
        fio.open(argv[2], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[2] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();
        size = strlen(argv[3]);
        str = str.assign(argv[3], size);

//				ist >> str;
        break;

      case 3: // automaton is arriving on stdin

        if (strcmp(argv[1], "-d") == 0)
          {
            ist >> str;
            i = 1;
            std::cin >> a;
            break;
          }

        fio.open(argv[1], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();
        size = strlen(argv[2]);
        str = str.assign(argv[2], size);
//				ist >> str;
        break;
      case 2:
        size = strlen(argv[1]);
        str = str.assign(argv[1], size);
//				ist >> str;
        std::cin >> a;
        break;

      default:
        std::cerr << "usage: " << my_name << " [-d] fm string\n";
        return 1;
        }
      if (a.member_of_language(str, i))
        std::cout << "accepted\n";
      else
        std::cout << "not accepted\n";
      return 0;

    }

  if (strcmp(my_name, fmmin) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (!a.is_deterministic())
        {
          std::cerr << "can't minimize nfm\n";
          return 1;
        }
      a.min_by_partition();
      std::cout << a;
      return 0;
    }
  /*if (strcmp(my_name, parmin) == 0)
    {
      _su_parFm su;
      su.parmin(argv[1]);
      return 0;
    }
    // Removed as it creates compiling problems
  */
  if (strcmp(my_name, fmminrev) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.reverse();
      a.reachable_fm(); //Added 3.3.2, 2007 Marcus and Brodie
      //we need reachable_fm() since subset() doesn't affect
      // a deterministic fm
      a.subset();
      a.reverse();
      a.reachable_fm();
      a.subset();
      std::cout << a;
      return 0;
    }
    if (strcmp(my_name, fmmindis) == 0)
      {
       fm<char> a;
       get_one(a, argc, argv, my_name);
       if (!a.is_deterministic())
         {
          std::cerr << "can't minimize nfm\n";
          return 1;
         }
       a.min_by_rafination();
       std::cout << a;
       return 0;
   }

  if (strcmp(my_name, fmorder) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.order();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmplus) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.plus();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmrenum) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (!a.canonical_numbering())
        {
          std::cerr << my_name << ": can't renumber nfm\n";
          return 1;
        }

      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmreverse) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.reverse();
      std::cout << a;
      return 0;
    }
    //Added in 2014 version 3.4.3
  if (strcmp(my_name, fmsuff) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.suffix();
      std::cout << a;
      return 0;
    }
if (strcmp(my_name, fmpref) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.prefix();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmdis) == 0)
    {
      fm<char> a;
      fm<char> result;
      int n=1;
      get_one(a, argc, argv, my_name);
      //std::cout<<argc<<std::endl;
      if (argc>2)
        {
          n=atoi(argv[2]);
          if (n>=1) a.disting(a,n);
        }
        else
      result.disting(a);
      //std::cout<<n<<std::endl;
      result.unattach();
      std::cout << result;
      return 0;
    }


  if (strcmp(my_name, fmreach) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.reachable_fm();
      std::cout << a;
      return 0;
    }

  //Added 3.3.2, August 2007. BC and MT
  if (strcmp(my_name, fmshuffle) == 0)
    {
      //Input state machines
      fm<char> a;
      fm<char> b;

      //Output state machine
      fm<char> c;

      //Read in input
      get_two(a, b, argc, argv, my_name);

      //Shuffle!
      c.shuffle(a, b);
      std::cout << c;
      return 0;
    }

  //Added 3.3.2, August 2007. BC and MT
  if (strcmp(my_name, fmshuffleq) == 0)
    {
      //Input state machines
      fm<char> product;
      fm<char> divisor;

      //Output state machine
      fm<char> quotient;

      //Read in input
      get_two(product, divisor, argc, argv, my_name);

      //Shuffle!
      quotient.shuffle_quotient(product, divisor);
      std::cout << quotient;
      return 0;
    }

  if (strcmp(my_name, fmstats) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.stats(std::cout);
      return 0;
    }
  if (strcmp(my_name, nfatodfa) == 0)
    {
      fm<char> a, b;
      get_one(a, argc, argv, my_name);
      a.nfatodfa(b);
      std::cout << b;
      return 0;
    }
  if (strcmp(my_name, nfatodfca) == 0)
    {
      fm<char> a;
      fcm<char> b;
      get_one(a, argc, argv, my_name);
      a.nfatodfca(b);
      std::cout << b;
      if (debug == -1) // output to file
        {
          char* tempname;
          tempname = new char[strlen(nfatodfca_name) + 30];
          strcpy(tempname, nfatodfca_name);
          std::ofstream myfile;
          myfile.open(strcat(tempname, "_result_Nfatodfca"));
          myfile << b;
          std::cout << "The result ouput into " << tempname << std::endl;

        }

      return 0;
    }

  if (strcmp(my_name, fmstar) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.star();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fmtofcm) == 0) // Added in 3.1
    {
      fm<char> a;
      fcm<char> b;
      get_one(a, argc, argv, my_name);
      if (!a.is_finite())
        {
          std::cerr << "Language is not finite\n";
          return 0;
        }
      if (a.is_deterministic())
        {
         std::cout << b.convert_to_fcm(a);
        }
       else
        {
	 std::cerr<<"can't convert  NFA to DFCA with this command, use nfmtofcm instead\n";
        }
      return 0;
    }
if (strcmp(my_name, nfmtofcm) == 0) // Added in 3.4.2c
    {
      fm<char> a;
      fcm<char> b;
      get_one(a, argc, argv, my_name);
      if (!a.is_finite())
        {
          std::cerr << "Language is not finite\n";
          return 0;
        }
      a.subset();
      a.complete();
      std::cout << b.convert_to_fcm(a);
      return 0;
    }


  if (strcmp(my_name, fmtofcm0) == 0)
    {
      fm<char> a;
      fcm<char> b;
      get_one(a, argc, argv, my_name);
      if (!a.is_finite())
        {
          std::cerr << "Language is not finite\n";
          return 0;
        }

      a.fmtofcm0(b);
      std::cout << b;
      return 0;
    }

  if (strcmp(my_name, fmtofcm2) == 0) // Added in 3.1
    {
      fm<char> a;
      fcm<char> b;
      get_one(a, argc, argv, my_name);
      if (!a.is_finite())
        {
          std::cerr << "Language is not finite\n";
          return 0;
        }
      std::cout << b.convert_to_fcm2(a);
      return 0;
    }

  if (strcmp(my_name, fmtofl) == 0)
    {
      fl<char> l;
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (!a.is_finite())
        {
          std::cerr << my_name << ": The language is not finite\n";
          return 1;
        }
      a.fmtofl(l);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, fmtore) == 0)
    {
      re<char> r;

      fm<char> a;
      get_one(a, argc, argv, my_name);
      r.fmtore(a);
      std::cout << r << "\n";
      return 0;
    }

  if (strcmp(my_name, fmunion) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a += b;
      std::cout << a;
      return 0;
    }
  if (strcmp(my_name, fmunionsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a += b;
      a.subset();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }
  if (strcmp(my_name, fmunionrsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a += b;
      a.subset();
      a.reduce();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }
  if (strcmp(my_name, fmunionmsize) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);
      a += b;
      a.subset();
      a.reduce();
      a.min_by_partition();
      std::cout << a.number_of_states() << std::endl;
      return 0;
    }



  if (strcmp(my_name, dfaunion) == 0)
    {
      fm<char> a;
      fm<char> b;
      fm<char> c;
      get_two(a, b, argc, argv, my_name);
      c.dfaunion(a, b);
      std::cout << c;
      return 0;
    }

  if (strcmp(my_name, fmdeterm) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      a.subset();
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, flappend) == 0)
    {
      fl<char> l;
      string<char> s;
      get_two(l, s, argc, argv, my_name);
      l.append(s);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, flexec) == 0)
    {
      string<char> str;
      std::fstream fio;
      std::istrstream ist(argv[argc - 1]);
      fl<char> l;

      // handle arguments
      switch (argc)
        {
      case 3:
        fio.open(argv[1], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> l;
        fio.close();

        ist >> str;
        break;
      case 2:
        ist >> str;
        std::cin >> l;
        break;

      default:
        std::cerr << "usage: " << my_name << " fl string\n";
        return 1;
        }

      if (l.member_of_language(str))
        {
          std::cout << "accepted\n";
          return 0;
        }
      std::cout << "not accepted\n";
      return 0;
    }

  if (strcmp(my_name, flfilter) == 0)
    {
      fl<char> l;
      fm<char> a;
      std::fstream fio;

      // handle arguments
      switch (argc)
        {
      case 3:
        fio.open(argv[1], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> l;
        fio.close();

        fio.open(argv[2], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();
        break;
      case 2:
        fio.open(argv[1], std::ios::in);
        if (!fio)
          {
            std::cerr << my_name << ": can't open " << argv[1] << "\n";
            return 1;
          }
        ;
        fio >> a;
        fio.close();

        std::cin >> l;
        break;

      default:
        std::cerr << "usage: " << my_name << " fl fm\n";
        return 1;
        }
      a.flfilter(l);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, fllq) == 0)
    {
      fl<char> l;
      string<char> s;
      get_two(l, s, argc, argv, my_name);
      l.left_quotient(s);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, flprepend) == 0)
    {
      fl<char> l;
      string<char> s;
      get_two(l, s, argc, argv, my_name);
      l.prepend(s);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, flprod) == 0)
    {
      fl<char> l;
      fl<char> m;
      get_two(l, m, argc, argv, my_name);
      l *= m;
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, flreverse) == 0)
    {
      fl<char> l;
      get_one(l, argc, argv, my_name);
      l.reverse();
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, flrq) == 0)
    {
      fl<char> l;
      string<char> s;
      get_two(l, s, argc, argv, my_name);
      l.right_quotient(s);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, fltofcm) == 0) // Added in 3.1
    {
      fl<char> l;
      fcm<char> a;
      get_one(l, argc, argv, my_name);
      a.fltofcm(l);
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, inttofl) == 0) // Added 2011 summer Ray
    {
      fl<char> l;

      if (argc == 2) // by default use binary alphabets
        {
          int length = strlen(argv[1]);

          char num[length];

          for (int a = 0; a < length; a++)
            {
              char temp = argv[1][a];

              num[a] = atoi(&temp);

            }

          l.inttofl(2, num, length);
          return 0;
        }
      //if specified the aplbets size
      int length = strlen(argv[1]);

      char num[length];

      for (int a = 0; a < length; a++)
        {
          char temp = argv[1][a];
          num[a] = atoi(&temp);

        }

      l.inttofl(atoi(argv[2]), num, length);
      return 0;
    }

  if (strcmp(my_name, fltoint) == 0) // Added in 3.1
    {
      fl<char> l;

      if (argc == 2)
        {
          get_one(l, argc, argv, my_name);
          l.fltoint(0);
          return 0;
        }
      else
        {
          argc = 2;
          get_one(l, argc, argv, my_name);
          l.fltoint(atoi(argv[2]));
          return 0;
        }
    }
  if (strcmp(my_name, flsimset) == 0) // Added in 3.1
    {
      fl<char> l;

      get_one(l, argc, argv, my_name);

      l.flsimset();
      return 0;
    }

  if (strcmp(my_name, fleqset) == 0) // Added in 3.1
    {
      fl<char> l;

      get_one(l, argc, argv, my_name);

      l.fleqset();
      return 0;
    }

  if (strcmp(my_name, fltofm) == 0)
    {
      fl<char> l;
      fm<char> a;
      get_one(l, argc, argv, my_name);
      a.fltofm(l);
      std::cout << a;
      return 0;
    }
  if (strcmp(my_name, flsubclose) == 0)
    {
      fl<char> l;
      fm<char> a;
      get_one(l, argc, argv, my_name);
      a.flsubwordclosure(l);
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fltofmmn) == 0) // Added in 3.1.2
    {
      fl<char> l;
      fm<char> a;
      get_one(l, argc, argv, my_name);
      a.fltofm_min(l);
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, fltore) == 0)
    {
      fl<char> l;
      re<char> r;
      get_one(l, argc, argv, my_name);
      r.fltore(l);
      std::cout << r << std::endl;
      return 0;
    }

  if (strcmp(my_name, flunion) == 0)
    {
      fl<char> l;
      fl<char> m;
      get_two(l, m, argc, argv, my_name);
      l += m;
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, iscomp) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (a.is_complete())
        {
          std::cout << "complete\n";
          return 0;
        }
      std::cout << "not complete\n";
      return 1;
    }

  if (strcmp(my_name, isdeterm) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (a.is_deterministic())
        {
          std::cout << "deterministic\n";
          return 0;
        }
      std::cout << "nondeterministic\n";
      return 1;
    }

  if (strcmp(my_name, isomorph) == 0)
    {
      fm<char> a;
      fm<char> b;
      get_two(a, b, argc, argv, my_name);

      a.canonical_numbering();
      b.canonical_numbering();

      if (a == b)
        {
          std::cout << "isomorphic\n";
          return 0;
        }

      std::cout << "nonisomorphic\n";
      return 1;
    }

  if (strcmp(my_name, isuniv) == 0)
    {
      fm<char> a;
      get_one(a, argc, argv, my_name);
      if (a.is_universal())
        {
          std::cout << "universal\n";
          return 0;
        }
      std::cout << "nonuniversal\n";
      return 1;
    }

  if (strcmp(my_name, recat) == 0)
    {
      re<char> r1;
      re<char> r2;
      get_two(r1, r2, argc, argv, my_name);
      r1 ^= r2;
      std::cout << r1 << "\n";
      return 0;
    }

  if (strcmp(my_name, remin) == 0)
    {
      re<char> r1;
      get_one(r1, argc, argv, my_name);
      std::cout << r1 << "\n";
      return 0;
    }

  if (strcmp(my_name, reunion) == 0)
    {
      re<char> r1;
      re<char> r2;
      get_two(r1, r2, argc, argv, my_name);
      r1 += r2;
      std::cout << r1 << "\n";
      return 0;
    }

  if (strcmp(my_name, restar) == 0)
    {
      re<char> r1;
      get_one(r1, argc, argv, my_name);
      r1.star();
      std::cout << r1 << "\n";
      return 0;
    }

  if (strcmp(my_name, retofl) == 0)
    {
      fl<char> l;
      re<char> r;
      get_one(r, argc, argv, my_name);
      if (!r.is_finite())
        {
          std::cerr << my_name << ": The language is not  finite.\n";
          return 1;
        }
      r.retofl(l);
      std::cout << l;
      return 0;
    }

  if (strcmp(my_name, retofm) == 0)
    {
      re<char> r1;
      fm<char> a;
      get_one(r1, argc, argv, my_name);
      r1.retofm(a);
      std::cout << a;
      return 0;
    }

  if (strcmp(my_name, isnull) == 0)
    {
      re<char> r1;
      get_one(r1, argc, argv, my_name);
      if (r1.is_empty_string())
        std::cout << "is empty string\n";
      else
        std::cout << "is not empty string\n";
      return 0;
    }

  if (strcmp(my_name, isempty) == 0)
    {
      re<char> r1;
      get_one(r1, argc, argv, my_name);
      if (r1.is_empty_set())
        std::cout << "is empty set\n";
      else
        std::cout << "is not empty set\n";
      return 0;
    }

  if (strcmp(my_name, fmisempty) == 0)
    {
      //fm is empty, by Ray 2012
      //simply test if any final state is reachable

      fm<char> nfa;
      get_one(nfa, argc, argv, my_name);

      set<state> reach_states;
      nfa.reachable_states(reach_states);
      set<state> finals;
      nfa.finals(finals);

      set<state> inter;
      inter.intersect(reach_states, finals);

      if (inter.size() == 0)
        {
          std::cout << "This machine has empty language." << std::endl;
        }
      else
        {
          std::cout << "This machine has non-empty language." << std::endl;
        }

      return 0;

    }

  if (strcmp(my_name, fmtoafa) == 0)
    {

      fm<char> finm;
      get_one(finm, argc, argv, my_name);

      afa<char> autom;
      autom.fmtoafa(finm);

      std::cout << autom; //output the afa to the file

      return 0;

    }

  if (strcmp(my_name, afatofm) == 0)
    {
      afa<char> autom;

      get_one(autom, argc, argv, my_name);
      fm<char> finm;
      finm = autom.afatofm(); //transfer the afa to the equivalent fm
      std::cout << finm;

      return 0;

    }

  if (strcmp(my_name, afaexec) == 0)
    {
      afa<char> autom;

      get_afa(autom, argc, argv, my_name);

      if (argc == 2)
        {
          int size = strlen(argv[1]);
          string<char> input;
          input = input.assign(argv[1], size);
          int k;
          k = autom.accept(input);
          if (k == 1)
            std::cout << "input was accepted" << std::endl;
          else
            std::cout << "input was not accepted" << std::endl;
        }

      if (argc == 3)
        {
          int size = strlen(argv[2]);
          string<char> input;
          input = input.assign(argv[2], size);
          int k;
          k = autom.accept(input);
          if (k == 1)
            std::cout << "input was accepted" << std::endl;
          else
            std::cout << "input was not accepted" << std::endl;
        }

      return 0;
    }

  if (strcmp(my_name, afacomp) == 0)
    {
      afa<char> autom;

      get_one(autom, argc, argv, my_name);

      afa<char> comafa;
      comafa = autom.complement();

      std::cout << comafa;

      return 0;

    }

  if (strcmp(my_name, afaunion) == 0)
    {
      afa<char> autom1, autom2;
      get_two(autom1, autom2, argc, argv, my_name);

      afa<char> uafa;
      uafa = autom1.afaunion(autom2);
      std::cout << uafa;

      return 0;
    }

  if (strcmp(my_name, afainter) == 0)
    {
      afa<char> autom1, autom2;
      get_two(autom1, autom2, argc, argv, my_name);

      afa<char> interafa;
      interafa = autom1.intersection(autom2);
      std::cout << interafa;

      return 0;
    }

  if (strcmp(my_name, litafa) == 0)
    {
      afa<char> autom;
      get_one(autom, argc, argv, my_name);

      autom.print(std::cout);

      return 0;
    }

  if (strcmp(my_name, fmsize) == 0)
    {
      fm<char> autom;
      get_one(autom, argc, argv, my_name);
      std::cout << autom.number_of_states() << std::endl;
      return 0;
    }

  if (strcmp(my_name, afasize) == 0)
    {
      afa<char> autom;
      get_one(autom, argc, argv, my_name);
      std::cout << autom.number_of_states() << std::endl;
      return 0;
    }

  if (strcmp(my_name, afareverse) == 0)
    {
      afa<char> autom;
      get_one(autom, argc, argv, my_name);

      afa<char> rafa;

      rafa = autom.reverse();
      std::cout << rafa;
      return 0;
    }

  if (strcmp(my_name, afastar) == 0)
    {
      afa<char> autom;
      get_one(autom, argc, argv, my_name);

      afa<char> safa;
      safa = autom.opstar();
      std::cout << safa;
      return 0;
    }

  if (strcmp(my_name, afacaten) == 0)
    {
      afa<char> autom1, autom2;
      get_two(autom1, autom2, argc, argv, my_name);

      afa<char> catafa;
      catafa = autom1.afacat(autom2);
      std::cout << catafa;

      return 0;
    } 

    if (strcmp(my_name, fmrandenum) == 0)
   {
       string<char> l;
       fm<char> a;
       std::cin >> a;
       std::string s = argv[1];
       std::istringstream ss;
       ss.str(s);
       int length;
       ss >> length;
       a.fmrandenum(l, length);
       
       std::cout << l << std::endl;
       
       return 0;
   }

  std::cerr << my_name << ": no such grail function" << std::endl;
  return 1;
}
;

void get_two(fm<char>& a, fm<char>& b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> b;
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    // we should be able to reuse f_arg, but for some reason
    // it doesn't work under Watcom 9.5

    g_arg.open(argv[2], std::ios::in);
    if (!g_arg)
      {
        std::cerr << my_name << ": can't open " << argv[2] << "\n";
        exit(1);
      }
    ;

    g_arg >> b;
    break;

  default:
    std::cerr << my_name << ": requires two fm's\n";
    exit(1);
    }
}

void get_one(fm<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if (argc > 2)
    {
      std::cerr << "usage: " << my_name << " fm\n";
      exit(1);
    }

  if (argc == 2)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}
;

void get_two(re<char>& a, re<char>&b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> b;
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    // we should be able to reuse f_arg, but for some reason
    // it doesn't work under Watcom 9.5

    g_arg.open(argv[2], std::ios::in);
    if (!g_arg)
      {
        std::cerr << my_name << ": can't open " << argv[2] << "\n";
        exit(1);
      }
    ;

    g_arg >> b;
    break;

  default:
    std::cerr << my_name << ": requires two re's\n";
    exit(1);
    }
}

void get_one(re<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if (argc > 2)
    {
      std::cerr << "usage: " << my_name << " re\n";
      exit(1);
    }

  if (argc == 2)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}
;

void get_two(fl<char>& a, fl<char>&b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> b;
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    // we should be able to reuse f_arg, but for some reason
    // it doesn't work under Watcom 9.5

    g_arg.open(argv[2], std::ios::in);
    if (!g_arg)
      {
        std::cerr << my_name << ": can't open " << argv[2] << "\n";
        exit(1);
      }
    ;

    g_arg >> b;
    break;

  default:
    std::cerr << my_name << ": requires two fl's\n";
    exit(1);
    }
}

void
get_one(fl<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if (argc > 2)
    {
      std::cerr << "usage: " << my_name << " fl\n";
      exit(1);
    }

  if (argc == 2)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}

void
get_two(fl<char>& a, string<char>&b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;
  std::istrstream ist(argv[argc - 1]);

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> a;
    ist >> b;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    ist >> b;
    break;

  default:
    std::cerr << my_name << ": requires an fl and a string\n";
    exit(1);
    }
}

void
get_one(afa<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if (argc > 2)
    {
      std::cerr << "usage: " << my_name << "afa\n";
      exit(1);
    }

  if (argc == 2)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}

void
get_two(afa<char>& a, afa<char>& b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> b;
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    // we should be able to reuse f_arg, but for some reason
    // it doesn't work under Watcom 9.5

    g_arg.open(argv[2], std::ios::in);
    if (!g_arg)
      {
        std::cerr << my_name << ": can't open " << argv[2] << "\n";
        exit(1);
      }
    ;

    g_arg >> b;
    break;

  default:
    std::cerr << "requires two afa's\n";
    exit(1);
    }
}

void
get_afa(afa<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if ((argc > 3) || (argc < 2))
    {
      std::cerr << my_name << " need 2 or 3 arguments" << std::endl;
      exit(1);
    }

  if (argc == 3)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << " can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}

// The following two functions were added for cover automata in 3.1
void get_two(fcm<char>& a, fcm<char>& b, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;
  std::fstream g_arg;

  // handle arguments

  switch (argc)
    {
  case 2:
    std::cin >> b;
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    break;

  case 3:
    f_arg.open(argv[1], std::ios::in);
    if (!f_arg)
      {
        std::cerr << my_name << ": can't open " << argv[1] << "\n";
        exit(1);
      }
    ;
    f_arg >> a;
    f_arg.close();

    // we should be able to reuse f_arg, but for some reason
    // it doesn't work under Watcom 9.5

    g_arg.open(argv[2], std::ios::in);
    if (!g_arg)
      {
        std::cerr << my_name << ": can't open " << argv[2] << "\n";
        exit(1);
      }
    ;

    g_arg >> b;
    break;

  default:
    std::cerr << my_name << ": requires two fm's\n";
    exit(1);
    }
}

void get_one(fcm<char>& a, int argc, char** argv, char* my_name)
{
  std::fstream f_arg;

  if (argc > 2)
    {
      std::cerr << "usage: " << my_name << " fm\n";
      exit(1);
    }

  if (argc == 2)
    {
      f_arg.open(argv[1], std::ios::in);
      if (!f_arg)
        {
          std::cerr << my_name << ": can't open " << argv[1] << "\n";
          exit(1);
        };
      f_arg >> a;
    }
  else
    std::cin >> a;
}
;

//Added in 3.3.3  Aug. 8th, 2007
//If the first argument is "--help", then print out
// help using 'print_help()', and exit
void print_help(const char* my_name)
{

  if (strcmp(my_name, fcmenum) == 0)
    {
      std::cout << "usage: " << my_name << " [-n size] fm\n";
      return;
    }

  if (strcmp(my_name, fcmexec) == 0) // Added in 3.1
    {
      std::cout << "usage: " << my_name << " [-d] fm string\n";
      return;
    }

  if (strcmp(my_name, fcmmin) == 0)
    {
      std::cout
          << "Minimizes a fcm.  This must be a grail file beginning with the size\
				 of the fcm. (i.e. l=4)";
      return;
    }

  if (strcmp(my_name, fcmtofm) == 0)
    {
      std::cout << "Converts an fcm to fm";
      return;
    }
}


void print_version(char* my_path)
{
  std::cout<<Version<<"\n";
}
