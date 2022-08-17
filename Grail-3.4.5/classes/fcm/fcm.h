//#This comes from 3.1.4-new
/******************************************************************************************
 File:  classes/fcm/fcm.h
 -----
 Description:
 ------------
 This file contains the type definition for the cover automata template class.

 It inherits from the fm (finite machine) class since cover automata and finite automata are very
 similar, but most fm functions such as minimization or intersection will not work correctly.

 See the i/o template functions defined in /classes/fcm/istream.src and classes/fcm/ostream.src.  The
 headers are:

      template <class Label>
      istream&
      operator>>(istream& is, fcm<Label>& a)

      template <class Label>
      ostream&
      operator<<(ostream& os, const fcm<Label>& a)


 *****************************************************************************************/
/*****************************************************************************************
 Revision History:
 -----------------
 J. Smith					Initial version
 ******************************************************************************************/

#ifndef FCM_CLASS_DEFINITION

template <class Label>
class fm;

template <class Label>
class fcm : public fm<Label>
{
	protected:
		int maxlen; // Maximum length of a word accepted by this fcm.

		array<atstate<Label> * > all_states;
			// all_states is an alternate representation of the fm where all arcs
			// are attached to the states.  This allows state x's transitions to be
			// accessed in linear time.  arcs is cleared as this is filled, so
			// unattach will need to be used before the fm can be output.

		bool attached;
			// This value is checked to see whether an fm has its transitions in
			// arcs or all_states.

	// The following are headers for the input stream function.  Different compilers require different
	// conventions for their declaration.
#ifdef _MSC_VER
	#if _MSC_VER<=1200
	friend	std::istream& operator>>(std::istream&, fcm<Label>&);
	#endif

	#if _MSC_VER>=1300
	friend std::istream& operator >> <Label> ( std::istream&, fcm<Label>&);
	#endif
#endif

	#ifndef _MSC_VER
	friend std::istream& operator >> <Label> ( std::istream&, fcm<Label>&);
	#endif
 	public:
	using fm<Label>::select;
	public:
		fcm() { attached = false; maxlen = -1; }
			// default constructor

		~fcm() { unattach(); }

		void		attach();
			// Connect states with their transitions.
			// This function does nothing if attached is true
			// and sets attached to true when it is executed.

		array<atstate<Label> * >		attach_inv();
			// This function is identical to attach() except that
			// it creates an inverse transition function.  All
			// transitions to state x are located in all_states[x].
			// This allows constant time access to state x's
			// incoming transitions and is used for merging states.

		void		copyfm(const fm<Label>& a)
			// This function copies all of the information from an
			// fm.  It is used in the converstion algorithms.
		{ a.finals(fcm<Label>::final_states); a.starts(fcm<Label>::start_states);
			a.get_arcs(fcm<Label>::arcs); }

		int 		enumerate(int number, set<string<Label> >& results);
			// All words that are accepted by this fcm are stored
			// in "results" (up to "number" words are stored).

		int 		get_max() const
			// This function returns the maximum length of a word
			// accepted by this fcm.
			{ return maxlen; }

		void		set_max(int i)
			// This function sets the maximum length of a word accepted
			// to "i".
			{ maxlen = i; }

		fcm<Label>&		convert_to_fcm(const fm<Label>&);
			// This function takes in an fm and converts it to a minimal
			// fcm in n-squared time using n-squared space.

		fcm<Label>&		convert_to_fcm2(const fm<Label>&);
			// This function takes in an fm and converts it to a minimal
			// fcm in nlogn time using n (linear) space.

		fm<Label>&		fcmtofm(fm<Label>&); // Added in 3.1.1
			// This function takes converts this fcm to a minimal fm.
			// A reference to the fm is returned.

		fcm<Label>&		fcmmin();
			// This function minimizes the fcm using the same method
			// as described in convert_to_fcm2.

		int		find_max();
			// This function finds the longest word accepted by the
			// automata.  It cannot be used if the automata has cycles,
			// so it is only used during conversion when the fcm is also
			// an acyclic finite automata.

		array<int>		find_levels();
			// This function finds the level of each state in the automata
			// using a breadth-first traversal.

		array<int>		find_ilevels();
			// This function finds the inverse level of each state in the
			// automata using a breadth first travres

		void		fltofcm(const fl<Label>& lang);
			// This function takes a finite language and incrementally
			// builds a minimal fcm accepting the words in the language.

		int 		member_of_language(const string<Label>&, const int);
			// This function returns 1 if the word is accepted by the
			// fcm and 0 if it is not.

		void		unattach();
			// Returns the fm to the default format after attach()
			// is called.  Does nothing if attached is false and
			// sets attached to false when it is executed.

		fcm<Label>&	operator=(const fcm<Label>&);
			// assignment:  assign this fm to contain the same set
			//  of instructions and start and final states as
			//  the parameter fm.  Returns a reference to this fm.

		//2010 SUMMBER BY RUI ZHOU
		fm<Label>& 	fcmtofm0(fm<Label>& );


};

#define		FCM_CLASS_DEFINITION
#endif
