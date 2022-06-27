//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project. 
//	No commercial use permitted without written consent.  
//	February 1995
//This code is LGPL and part of  the Grail project. rewrite by Yong 07/2018 
 
#ifndef	 TUPLE_CLASS_DEFINITION 
 
template <class Input, class Iput, class Output>//yong added 2018/07/17
class tuple
{
	private: 
 
		Input		left; 
		Iput		mid;// Yong added.
        Output      right; // Yong added
 
	public: 
        tuple() { ; ; }
				tuple(const tuple<Input, Iput, Output>& p)
                { left = p.left; mid = p.mid; right = p.right; }
                ~tuple(){ ; ; }
	void			assign(const Input& i, const Iput& o, const Output p)
                    { left = i; mid = o; right = p; }
	tuple<Input,Iput, Output>&	operator=(const tuple<Input,Iput, Output>& l)
    { left = l.left; mid = l.mid; right = l.right; return *this;}
	int			operator==(const tuple<Input, Iput, Output>&) const;
	int			operator!=(const tuple<Input, Iput, Output>& p) const
				{ return *this == p ? 0 : 1; }
    
    
	int			operator<(const tuple<Input, Iput, Output>&) const;
	int			operator>(const tuple<Input, Iput, Output>& p) const
				{ return *this < p ? 0 : 1; } 
	Input			get_left() const
				{ return left; }
    Iput            get_mid() const
                { return mid; }
	Output			get_right() const
				{ return right; } 
}; 
 
#define	TUPLE_CLASS_DEFINITION

#endif 

