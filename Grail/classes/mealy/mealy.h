//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	February 1995


//
//This class implements mealy machines.
//
#ifndef		MEALY_CLASS_DEFINITION

template <class In, class Out>
class mealy : public fm<pair<In, Out> >
{
#ifdef	WATCOM
	friend std::ostream&
	operator<<(std::ostream&, const mealy<In, Out>&);
#endif

	// protected functions

	protected:

	int		find_first(const state&) const;

	// public functions

	public:
	//by UGO 2006/10/19 <edit-start>
using 	fm< pair<In, Out> >::arcs;		// set of instructions
using	fm< pair<In, Out> >::start_states;	// set of start states
using	fm< pair<In, Out> >::final_states;	// set of final states
using	fm< pair<In, Out> >::all_states;
using	fm< pair<In, Out> >::is_deterministic;
 	//by UGO 2006/10/19 <edit-end>
  	public:
			mealy() { ; }
			// mealy(const mealy<In, Out>&) { ; }
			// ~mealy() { ; }
	mealy<In, Out>&	operator=(const mealy<In, Out>& x);
	int		execute(const string<In>&, set<string<Out> >&,
				const int) const;
	int		deterministic_execution(const string<In>&,
				string<Out>&, const int) const;
	mealy<In, Out>&	select(const In&, const state&, int,
				mealy<In, Out>&) const;
};

#define		MEALY_CLASS_DEFINITION
#endif
