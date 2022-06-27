//#This comes from 3.1.4-new
#ifndef 		ATSTATE_CLASS_DEFINITION

template <class Label>
class array;

template <class Label>
class inst;

template <class Label>
class atstate
{
private:

	bool is_final;
	array<inst<Label> > transitions;

public:

	atstate()
		{
			is_final = false;
		}

       
	atstate(const atstate<Label>& s)
	{	is_final = s.is_final;
		transitions = s.transitions; }


	bool final() const
		{ return is_final; }

	void set_final(bool x)
		{ is_final = x; }

	int size() const
		{ return transitions.size(); }

	atstate &operator=(const atstate &s)
		{	is_final = s.is_final;
			transitions = s.transitions; return *this; }

	int operator==(const atstate &s) const;

	int operator<(const atstate &s) const;
	int operator>(const atstate &s) const
		{ return s < *this ? 1 : 0; }

	inst<Label> &operator[](int i) const
		{ return transitions[i]; }

	atstate &operator+=(inst<Label> s)
		{ transitions += s; return *this; }

	atstate &remove(int i)
		{ transitions.remove(i); return *this; }

};

#define		ATSTATE_CLASS_DEFINITION
#endif
