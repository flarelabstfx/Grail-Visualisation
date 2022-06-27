//#This comes from 3.1.4-new; modified by ray and sherry in summer 2010
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	February 1996

/***************************************************************************

 File:  classes/fm/enum.src
 -----

 Description:
 ------------
 This file contains the definition of the following function:
 int fm<Label>::enumerate(int number, set<string<Label> >& members)

 This function is a public member of the template class fm (declared
 in classes/fm/fm.h).

 Revision History:
 -----------------
 The Grail Project               Initial version of source code
 M.Hoeberechts  98/09/06         Added header and comments

 ***************************************************************************/

/***************************************************************************

 int fm<Label>::enumerate(int number, set<string<Label> >& members)

 Description:
 This function is a public member of the template class fm (declared
 in classes/re/fm.h).  This function determines the set of words in the
 language represented by this fm.  The words are placed in the
 parameter array (unless there are more than 'number' words in which
 case only 'number' are generated and placed in the array).  The
 function returns the number of words placed in the array.

 This function can be called in the following way:
 this_fm.enumerate(max, word_array);

 Parameters:
 int number - the size of the word array
 set<string<Label> >& members - the set to store the words

 Return Value:
 int - the number of words placed in the array

 ***************************************************************************/

template<class Label>
int fm<Label>::enumerate2(int length, set<string<Label> >& members)
{
	int i;
	int j;
	int k;
	int m;
	fm<Label> cur;
	string<Label> r;
	set<state> temp;
	list<set<state> > dest;
	list<set<state> > next_dest;
	list<string<Label> > partial;
	list<string<Label> > next_partial;

	// check to make sure some final states are reachable
	reachable_states(dest[0]);
	temp.intersect(dest[0], final_states);
	if (temp.size() == 0)
		return 0;

	// minimize the machine
	reachable_fm();
	reverse();
	reachable_fm();
	reverse();

	// begin with start states
	temp = start_states;
	dest.clear();
	dest += temp;
	r.clear();
	partial += r;

	// develop word fragments until we have enough
	for (;;)
	{
		// extract new members from fragment list
		for (i = 0; i < partial.size(); ++i)
		{
			for (j = 0; j < dest[i].size(); ++j)
				if (final_states.member(dest[i][j]) >= 0)
				{

					if (partial[i].size() > length)
					{
						members.sort_length();
						return (members.size());
					}

					members += partial[i];
					break;
				}
		}

		/*
		 if (members.size() >= number)
		 {members.sort_length();return(members.size());}
		 */
		//if ()

			// develop new fragments
			next_dest.clear();
		next_partial.clear();

		for (j = 0; j < dest.size(); ++j)
		{
			for (i = 0; i < dest[j].size(); ++i)
			{
				if (dest[j].member(dest[j][i]) < 0)
					continue;

				select(dest[j][i], SOURCE, cur);

				// if no arcs, continue
				if (cur.size() == 0)
					continue;

				// else add new fragments
				for (k = 0; k < cur.size(); ++k)
				{
					r = partial[j];
					r += cur[k].get_label();

					// don't add any fragments that
					// are already present
					if ((m = next_partial.member(r)) >= 0)
					{
						next_dest[m] += cur[k].get_sink();
						continue;
					}

					next_partial += r;
					temp = cur[k].get_sink();
					next_dest += temp;
				}
			}
		}

		// reset the wave
		if (next_dest.size() == 0)
		{
			members.sort_length();
			return (members.size());
		} // added by ray ,sort before output

		dest = next_dest;
		partial = next_partial;
	}
}
