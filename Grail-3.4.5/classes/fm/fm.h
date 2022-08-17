//#This comes from Grail-3.3.5; modified by ray and sherry in summer 2010
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	August 1994

/***************************************************************************

  File:  classes/fm/fm.h
  -----

  Description:
  ------------
    This file contains the type defintion for a finite state machine
    template class.  The template parameter specifies the type for the
    instructions on the arcs of the fm.  This declaration provides
    flexibility because it allows any base type or user defined defined type
    to be specified as the input type for the machine.  For example, an
    fm which accepts alphabetic characters as input could be declared by
    fm<char> whereas a machine which accepts integers could be declaraed
    by fm<int>.

    The internal representation and input/output format of finite state
    machines in Grail is somewhat different from the usual.  A machine is
    represented as a set of instructions.  For example, a machine which
    accepts the language ab is specified by:

      (START) |- 0
      0 a 1
      1 b 2
      2 -| (FINAL)

    Each instruction is a triple consisting of a source state, an instruction
    symbol, and the corresponding target state.  The start and final states
    of the machine are indicated by means of special pseudo-instructions,
    whose labels are symbols that can be thought of as end markers on the
    input tape.  The states (START) and (FINAL) are pseudo-states; they
    simply indicate that the other state in the instruction is a start state
    or final state.

    The alphabet of a Grail machine is given implicitly; it is the set of
    symbols which appear in the non-pseudo instructions.  Grail permits
    machines to have multiple start and final states.

    Finite machines inputted to Grail or outputted by its filters will be in
    the above format.  The order of the instructions is arbitrary.  A machine
    with several start and final states will have a pseudo-instruction for
    each one:

      0 -| (FINAL)
      1 b 2
      0 a 1
      (START) |- 0
      (START) |- 1
      2 -| (FINAL)

    The internal representation for an automaton consists of a set (non-pseudo)
    instructions, a set of final states and a set of start states.  Member
    functions are provided which allow the union, concatenation, complement,
    completion, cross product, reversal, subset construction, and minimization
    of automata.  There are also functions to add or remove instructions,
    collect the instructions, start states, or final states and to input
    or output the finite machine.


  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/02/04         Added header and comments

 **************************************************************************/
//#include "../stenum.h" //by UGO 10/20/2006

#ifndef		FM_CLASS_DEFINITION




template <class Label>
class fl;

template <class Label>
class fcm;

template <class Label>
class fm;

template <class Label>
class atstate;

template <class Label>
std::istream& operator >> ( std::istream&, fm<Label>&); //by SH 05/25/2005


template <class Label> class fl;

template <class Label>
class fm
{
        friend
	set<inst<Label> > get_arcs (const fm<Label>& f)
			// returns a copy of the set of arcs in this fm
	  		{ set<inst<Label> > tmp;
	    		tmp = f.arcs;
	    		return tmp;
	   		}

        friend class Generator;
protected:

	int		find_first(const state&) const;
  			// if the set of arcs is sorted, this function can
			//  be used to find the first occurrence of the
			//  given source state in the set of arcs.  Returns
			//  the index of the first arc containing the state
			//  r as its source, or -1 if no such arc is found.


	set<inst<Label> >	arcs;		// set of instructions
	set<state>		start_states;	// set of start states
	set<state>		final_states;	// set of final states

	array<atstate<Label> * > all_states;
		// all_states is an alternate representation of the fm where all arcs
		// are attached to the states.  This allows state x's transitions to be
		// accessed in linear time.  arcs is cleared as this is filled, so
		// unattach will need to be used before the fm can be output.



	bool attached;
		// This value is checked to see whether an fm has its transitions in
		// arcs or all_states.

	array<bool> reg;
		// reg is used in the replace or register function in many filters

// friend functions
//	friend istream&	operator>>(istream&, fm<Label>&);
			// read an fm from the parameter stream.  Returns
			//  a reference to the input stream.
#ifdef _MSC_VER
	#if _MSC_VER<=1200
	friend	std::istream& operator>>(std::istream&, fm<Label>&);		// stream input
	#endif

	#if _MSC_VER>=1300
	friend std::istream& operator >> <Label> ( std::istream&, fm<Label>&);
	#endif
#endif

	#ifndef _MSC_VER
	friend std::istream& operator >> <Label> ( std::istream&, fm<Label>&);
	#endif //by SH 05/20/2005

// public functions
public:

			fm() { attached = false;}
			// default constructor

			fm(const fm<Label>& x) :
			  arcs(x.arcs), start_states(x.start_states),
			  final_states(x.final_states) { attached = false; }
			// copy constructor:  make this fm a copy of the
			//  parameter fm.

			~fm() { unattach(); }
			// unattached must be called to free dynamically allocated
			// memory in all_states

	fm<Label>&	operator=(const fm<Label>&);
			// assignment:  assign this fm to contain the same set
			//  of instructions and start and final states as
			//  the parameter fm.  Returns a reference to this fm.

	int		operator==(const fm<Label>&) const;
			// test for equality:  returns 1 if this fm is equal to
			//  the parameter fm (contains the same set of
			//  instructions and start and final states), and 0
			//  otherwise.

	int		operator!=(const fm<Label>& x) const
			// test for inequality:  returns 1 if this fm is not
			//  equal to the parameter fm (contains a different
			//  set of instructions, start states or final states),
			//  and 0 otherwise.
			{ return *this == x ? 0 : 1; }

	fm<Label>&	operator+=(const fm<Label>&);
                        // fm union:  the instructions, start states and final
                        //  states in the parameter fm are added to those in
                        //  this fm to perform the union.  The function
                        //  returns a reference to this fm; the parameter fm
                        //  is unchanged.

	fm<Label>&	operator+=(fm<Label>*);
                        // fm union:  the instructions, start states and final
                        //  states in the fm pointed to by the parameter
                        //  are added to those in this fm to perform the
                        //  union.  The function returns a reference to this
                        //  fm; the parameter is unchanged.

	fm<Label>&	operator^=(const fm<Label>&);
                        // fm catenation:  This function catenates this
                        //  fm with the parameter fm.  The resulting
                        //  language will contain the all the words in
                        //  the language represented by this fm catenated
                        //  with the words in the language represented by
                        //  the parameter fm.  The function returns a reference
                        //  to this fm.

	fm<Label>&	operator-=(const fm<Label>& a);
                        // This function removes any arcs which are found in
                        //  both this fm and the parameter fm from this fm.
                        //  The parameter fm is unchanged; the function
                        //  returns a reference to this fm.

	inst<Label>&	operator[](int i) const
			// returns the ith instruction in this fm.  The
			//  parameter is unchanged.
			{ return arcs[i]; }

	void		add_instruction(const inst<Label>& i)
			// adds the parameter instruction to the set
                        //  of instructions in this fm.  The parameter
                        //  is unchanged.
			{ arcs += i; }

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

	void		cartesian(const set<state>&, const set<Label>&,
				const set<state>&);
			// This function constructs arcs whose source state,
			//  label and sink states are determined by taking
			//  the cartesian product of the parameter sets.
			//  Any existing arcs in this fm are removed, and
			//  all the arcs which are constructed are added to
			//  this fm.  The parameter sets are unchanged.

	int		canonical_numbering();
			// renumbers the states in a deterministic fm in
			//  the order defined by canonical numbering.
			//  The function returns 1 if the numbering was
			//  successfully completed, and 0 otherwise (which
			//  will be the case if the fm was not deterministic)

	fm<Label>&	clear()
			// clear contents of this fm (clear arcs, start
			//  states and final states).  Returns a reference
			//  to this fm.
			{ arcs.clear(); start_states.clear();
			  final_states.clear(); return *this; }

	void		complement();
			// complement this fm

	void		complete();
			// completes this fm

	void		cross_product(const fm<Label>&, const fm<Label>);
			// computes the cross product of the parameter
			//  fms and stores the result as this fm.

	void            dfaunion(const fm<Label>& a, const fm<Label> b);
                        // makes this fm the union of the two parameter
			//  fms.  Both parameter fms must be deterministic.
			//  If one is not, a message is printed on the
			//  standard error stream and nothing is done.

	fm<Label>&	disjoint_union(const fm<Label>&);
			// computes the union of this fm and the parameter
			//  fm and stores the result in this fm.  Note that
			//  this fm and the parameter fm must have disjoint
			//  sets of instructions, start states and final
			//  states before calling this function.  Returns
			//  a reference to this fm.
	void	disting(const fm<Label>&);
			// computes the distinguishability language of the parameter
			//  fm and stores the result in this fm.
			//   Returns  void.
	void	disting(const fm<Label>&, int n);
			// computes the iterated distinguishability language of the parameter
			//  fm and stores the result in this fm.
			//   Returns  void.

	inline fm<Label>&	disjoint_union(const inst<Label>&);
			// adds the parameter instruction to the set of
			//  instructions in this fm.  The parameter
			//  instruction must not already exist in the set
			//  since no checking is done.  Returns a reference
			//  to this fm.

	fm<Label>&	empty_string_machine();
			// replaces the contents of this fm with a one state
			//  machine which represents the language that
			//  contains only the empty string.  Returns a
			//  reference to this fm.

	int		enumerate(int, set<string<Label> >&);
			// determines the set of words in the language
			//  represented by this fm.  The parameter set will
			//  contain the words; the integer parameter is the
			//  size of the set; the number of words actually
			//  placed in the array is returned.
    
    int        enumerate1(int, set<string<Label> >&);// add Yong: version?
    // determines the set of words in the language
    //  represented by this fm.  The parameter set will
    //  contain the words; the integer parameter is the
    //  size of the set; the number of words actually
    //  placed in the array is returned.
    
	int		enumerate2(int, set<string<Label> >&);
			//enumerate to length n

    int        enumerate3(int, set<string<Label> >&);// add Yong: version?
    
     
    
	set<state>&	finals(set<state>& r) const
			// return a copy of the set of final states in this fm
			{ return r=final_states; }

	fm<Label>  flsubwordclosure(const fl<Label>& constraint);
			//Constructs an fm recognizing the subword closure
			//of a finite language. This requires that all words
			//in the finite language be of the same length

 	void		fltofm(const fl<Label>&);
			// converts the parameter fl to this fm

	void		fltofm_min(const fl<Label>&);
			// converts an fl to this fm by incrementally adding the words
			// in the fl, and minimizing after each word is added.

 	void		flfilter(fl<Label>&) const;
			// removes all the words from the parameter language which
			//  are not accepted by this fm

 	int		fmtofl(fl<Label>&) const;
			// converts the language represented by this fm to a finite
			//  language and stores the result in the parameter fl.
			//  Returns 1 if successful, -1 otherwise.

	set<inst<Label> >&		get_arcs(set<inst<Label> >& a) const
		// This function returns the arcs in an fm.  It is used by the
		// fcm class when copying the information from an fm.
		{ return a = arcs; }

	int		is_complete() const;
			// returns 1 if this fm is complete, 0 otherwise

	int		is_deterministic() const;
			// returns 1 if this fm is deterministic, 0 otherwise

 	int		is_finite() const;
			// returns 1 if the language represented by this fm
			//  is finite, 0 otherwise.

	int		is_universal() const;
			// returns 1 if the universal language over the input
			//  alphabet is accepted by this fm, and 0 otherwise

	set<Label>&	labels(set<Label>&) const;
			// collects the set of labels (i.e. the input
			//  alphabet) used in this fm and stores them in
			//  the parameter set.  Returns a reference to
			//  the set of labels.

	state		max_state() const;
			// returns the highest numbered state in this fm

	int		member_of_language(const string<Label>&, const int)
						const;
                        // returns 1 if the parameter word is accepted by
			//  this fm, 0 otherwise.  The second parameter
			//  should be true if messages showing the
			//  transitions used should be printed to the
			//  standard output, false otherwise.

	fm<Label>&	min_by_partition();
			// minimizes this fm using Hopcroft's partition
			//  algorithm.  Returns a reference to this fm

        fm<Label>&      min_by_rafination();
                        // minimizes this fm using Moore's partition
                        //  rafination algorithm.  Returns a reference to this fm

	int		number_of_final_states() const
			// returns the number of final states in the machine
			{ return final_states.size(); }

	int		number_of_labels() const
			// returns the number of labels used on instructions
			//  in the machine (size of the input alphabet)
			{ set<Label> r; return labels(r).size(); }

	int		number_of_start_states() const
			// returns the number of start states in the machine
			{ return start_states.size(); }

	int		number_of_states() const

			// returns the total number of states in the machine
			{ set<state> r; return states(r).size(); }

	int		number_of_instructions() const
			// returns the number of instructions (transitions)
			//  in the machine
			{ return arcs.size(); }

	int		order();
			// topologically sorts an fm.  This means that all
			// transitions go from a lower numbered state to a
			// higher numbered state.  The fm must be acyclic.

	void		plus();
			// perform the plus ('+') operation on the fm

	void		reachable_fm();
			// reduce the state set in this fm to states which
			//  are reachable from a start state

	void		reachable_states(set<state>&) const;
			// extracts the set states reachable from a start
			//  state in this fm and returns them as the
			//  parameter set

	void		remove(const state&);
			// removes the parameter state from this fm (removes
			//  all transitions to or from the state)

	void		renumber(int);
			// adds the number specified by the parameter onto
			//  the state number of each state in the fm

	void		replace_or_register(int);
			// This function is used by fltofm_min.  It compares a
			// given state to the states in the register to see if
			// it needs to be merged.

	void		reverse();
			// reverse the fm

	fm<Label>&	select(const state&, int, fm<Label>&) const;
			// creates a subfm (third parameter) by selecting
			//  arcs from this fm with a given state (first
			//  parameter) as the source or sink state (depending
			//  on the value of the second parameter which can
			//  be SOURCE, SINK or EITHER).  The function
			//  returns a reference to the new fm.

	fm<Label>&	select(const Label&, fm<Label>&) const;
			// creates a subfm (second parameter) by selecting
			//  arcs from this fm.  Any arcs with r as the label
			//  for the transition are copied from this fm into
			//  the new fm.  Returns a reference to the new fm.

	fm<Label>&	select(const Label&, const state&, int,
					fm<Label>&) const;
			// creates a subfm (fourth parameter) by selecting
			//  arcs from this fm with a given state (second
			//  parameter) as the source or sink state (depending
			//  on the value of the third parameter which can
			//  be SOURCE, SINK or EITHER) and the specified
			//  label (first parameter).  The function returns
			//  a reference to the new fm.

	void		set_finals(const set<state>& s)
			// sets the set of final states to the parameter
			//  set.  Any existing final states will be replaced.
			{ final_states = s; }

	void		set_starts(const set<state>& s)
			// sets the set of start states to the parameter
			//  set.  Any existing start states will be replaced.
			{ start_states = s; }

	void  shuffle(const fm<Label>& a, const fm<Label> b);
		// computes the shuffle of two DFAs

	void  shuffle_quotient(fm<Label> product, fm<Label> divisor);
		// computes a shuffle quotient of a product NFA with a divisor NFA

	fm<Label>&	single(const Label&);
			// replaces the current contents of this fm by one
			//  start state, one final state and a transition
			//  between them on the input letter specified by
			//  the parameter.  Returns a reference to this fm.

	set<state>&	sinks(set<state>&) const;
			// gathers the sink states in the fm and stores them
			//  in the parameter set.  Returns a reference to
			//  the set of states.

	int		size() const
			// Returns the size of the fm (the number of arcs)
			{ return arcs.size(); }

	set<state>&	sources(set<state>&) const;
			// gathers the source states in the fm and stores
			//  them in the parameter set.  Returns a reference
			//  to the set of states.

	fm<Label>&	star();
			// perform the Kleene star ('*') operation on this fm

	set<state>&	starts(set<state>& r) const
			// return a copy of the set of start states in this fm
			{ return r=start_states; }

	void		stats(std::ostream&) const;
			// outputs a line of statistics about
			//  this fm on the parameter output stream.  The data
			//  outputted consists of the number of start states,
			//  the number of final states, the total number of
			//  states, the number of reachable states and the
			//  number of instructions followed by an end of line.

	set<state>&	states(set<state>&) const;
			// retrieves all the states in this fm and stores them
			//  in the parameter set.  The function returns a
			//  reference to the set.

	fm<Label>&	subset();
			// converts this fm to a deterministic fm using the
			//  method of subset construction.  The resulting fm
			//  will not necessarily be complete.  The function
			//  returns a reference to this fm.

	void		unattach();
			// Returns the fm to the default format after attach()
			// is called.  Does nothing if attached is false and
			// sets attached to false when it is executed.

	//added by ray &sherry in 2010 summer
	array<int> 	map;
	void		set_map();//set mapping relationships for each state in
				  //2 storage ways to solve segfault of attach() and others

	array<atstate<Label> * >
			get_all()
			{ return all_states; }

	int		find_max(); // find max string accepted

	int		toFinal(atstate<Label>& ,state& sink); //find the number of shortest steps to final

	int		toFinal(atstate<Label>& );

	void		fmtofcm0(fcm<Label>& );

	array<int>	find_ilevels(); // modified from fcm method

	void		set_attach(bool att)
			{attached=att;}	//used for unusal situation


	void 		setallstates(array<atstate<Label> * >&  allst)
			{all_states=allst;}

	void 		setmap(array<int>& ma)
			{map=ma;}


	fm<Label>&	clear_all()
			{
                        unattach();
			arcs.clear_all();
			start_states.clear_all();
			final_states.clear_all();

			//all_states.clear_all();

                        for(int a=0;a<all_states.size();a++)
                                       delete all_states[a];

                        all_states.clear_all();
			map.clear_all();


			return *this;
			}	//this can solve the seg abort when deconstrcutor are called

	void 		sort_arc_final()
			{arcs.sort();
			final_states.sort();}

	void 		set_arcs(set<inst<Label> >& arc)
			{arcs=arc;}



	bool 		is_sink(atstate<Label>& ats);
			// true if not start not final and goes to nothing or self only



	void		reduce();//reduce a fm

	void 		useful_fm();

	void		nfatodfa(fm<Label>&);// transform a nfa todfa.


	void 		nfatodfca(fcm<Label>& );//combination of nfatodfa and fmtofcm0,
						// with extra debug info for test.
	array<int>	find_levels(); // modified from fcm method



	void		add_start(const state& s)
					{ start_states += s; }
	void		add_final(const state& s)
					{ final_states += s; }


	//2011
	void 		ad_matrix();// show the adjecency info


	void		permutation(std::string str);

	void		fastgap(int  level_to_count);
//------------------------------------------------------------
// 2014
//-------------------------------------------------------------
	void		suffix();
	void		prefix();

	int fmrandenum(string<Label>& lang, int length) const;

};

#define		FM_CLASS_DEFINITION
#endif
