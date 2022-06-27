//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	January 1996


/***************************************************************************

  File:  classes/re/re.h
  -----

  Description:
  ------------
    This file contains the declarations of 8 classes which are used to
    represent regular expressions.  re is the class top level class which
    Grail uses when creating and manipulating regular expressions.  A
    regular expression is defined recursively using sub_exp (subexpression).
    A subexpression is one of the following:  empty_set, empty_string,
    symbol_exp, cat_exp, plus_exp or star_exp.  sub_exp is the virtual base
    class for subexpressions; it defines the interface and some default
    behaviour for functions, but its functions are implemented by the
    subclasses.  The following diagram shows the organization of the classes:


     ___________               ___________/---------------------------------
    |           |             |           |-------------------------------- |
    |    re     |<>-----------|  subexp   |------------------------------- ||
    |___________|             |___________|------------------------------ |||
                                    |     \----------------------------- ||||
                                    |                                   |||||
           ________________________/_\_________________________         |||||
          |         |          |          |         |          |        |||||
          |         |          |          |         |          |        |||||
     ___________    |   ______________    |    ____________    |        |||||
    |           |   |  |              |   |   |            |   |        |||||
    | empty_set |   |  | empty_string |   |   | symbol_exp |   |        |||||
    |___________|   |  |______________|   |   |____________|   |        |||||
                    |                     |                    |        |||||
               ___________           ___________          ___________   |||||
              |           |         |           |        |           |  /||||
              |  cat_exp  |<>--     | plus_exp  |<>--    | star_exp  |<> ||||
              |___________|<>- |    |___________|<>- |   |___________|   ||||
                              ||                    ||                   ||||
                              ||                    |\___________________/|||
                              ||                    \_____________________/||
                              |\___________________________________________/|
                              \_____________________________________________/


    All the classes are template classes with one parameter, S.  S specifies
    the type for the symbols in the regular expression.  For example, to
    represent the expression "(a+b)c" one could use the declaration re<char>.
    To represent "([1,2][3,4])*" the declaration might be re<pair>.  Normally,
    re is the only class which will be accessed from outside this file.

    re contains functions to assign, compare, catenate, add, clear, input
    output, and minimize regular expressions.  An expression can also be
    converted to an fm (finite machine) and vice versa.  The subclasses of
    sub_exp contain functions to compare, convert, create, print and
    determine the size of subexpressions.

    In order to implement the comparison functions, the following precedence
    ordering is used for the subexpressions:

      empty_set < empty_string < symbol_exp < plus_exp < cat_exp < star_exp

    Hence, empty_string::operator>(const empty_set<S>&) should return 1,
    since empty string expressions are always greater than empty set
    expressions.  We cannot simply compare the content of subexpression
    pointers, however, since function arguments are interpreted according to
    their apparent type, not their actual type.  Each subexpression therefore
    defines a set of functions of the form compare_xxx_exp where xxx is one
    of cat, plus, star or symbol.  This function determines how a given
    subexpression compares to an xxx expression.  In effect, it uses two
    function calls (the operator and the compare_xxx_exp) to determine the
    actual types of both arguments to the comparison operation.  This
    technique is called double dispatching.

    For instance, suppose there is an re object, re1 which represents
    expression "(a+b)", and re2 which represents "b*".  Suppose the call
    re1 < re2 is made.  This would invoke operator< for re1, which would then
    call re1->p.compare_plus_exp(left for re1, right for re1).  Since re2
    is an instance of star_exp, it could return 1 immediately since every
    star_exp is greater than a plus_exp according to the precedence ordering.
    Actual comparison of the expressions is only necessary in the case when
    the compare_xxx_exp function is called on an object of type xxx.  For
    example if re2 had been "(c+b)" then compare_plus_exp would be comparing
    a plus_exp (itself) to another plus_exp (re1) and thus comparison of the
    left and right conjuncts would be necessary to determine the ordering.

    Comparisons and tests for equality and inequality depend on the surface
    structure of the expression and not the language which is represented by
    the re.  For example, operator== would return false for (a+"")* == a*
    even though the right and left expressions represent the same language.
    However, commutative union expressions are recognized as being equal, and
    thus (a+b) == (b+a) would be true.

    Here are some more examples:

      Test				Result
      ----				------
      {}     <  (a+b)   		True
      (x+y)* <  (x+y)			False
      (a+b)  <  (a+b)			False
      xy+""  == xy+""			True
      ""+xy  == xy+""			True


    star_exp overloads the star operator of subexp and defines it as a no-op.
    This has the effect of ensuring that a 'starred' expression is only
    starred once.

    plus_exp, symbol_exp, cat_exp and star_exp declare a pool so that they
    can manager their own memory for creating and destroying subexpressions.
    More details are given in classes/re/memory.h and classes/pool/pool.h.

    Note that there is a difference between a clear expression and an
    expression which represents the empty set.  A clear expression is the
    result of clear() or the default contents of a new re object.  It does
    not (yet) represent a regular expression.  On the other hand, an
    expression which is the result of make_empty_set() is a regular expression
    which represents the empty set, i.e. {}.

    Template functions for inputting and outputting regular expressions are
    also defined (see classes/re/ostream.src and classes/re/istream.src).
    The function headers are the following:

	template <class S>
	ostream&
	operator<<(ostream& os, const re<S>& r)

	template <class S>
	istream&
	operator>>(istream& is, re<S>& r)


    The class specified for S must have the following operators
    defined:

    Operator:                 Used In Function:
    ---------                 -----------------
    ==                        symbol_exp<S>::compare_symbol_exp
    <                         symbol_exp<S>::compare_symbol_exp
    =                         symbol_exp<S>::operator=
    <<                        symbol_exp<S>::print

    In addition, symbol_exp<S>::subexp_to_fl(fl<S>& a) const declares a
    string<S>, so the following operators are required:

    <                         string.h
    >                         string.h
    ==                        string.h
    !=                        string.h
    =                         string.h
    <<                        string.h
    >>                        string.h


  Revision History:
  -----------------
    The Grail Project               Initial version of source code
    M.Hoeberechts  98/06/08         Added header and comments (adapted from
                                    Programmer's Guide to Grail Version 2.5
                                    by Darrell Raymond)

 ***************************************************************************/

#ifndef		RE_CLASS_DEFINITION


enum token_type
{
	eos_t,			// end of stream
//	error_t, 		// error
	error_t1,		// by SH 05/20/2005
	eset_t, 		// empty set
	estring_t, 		// empty string
	symbol_t, 		// symbol
	plus_t, 		// plus symbol
	star_t, 		// star symbol
	cat_t, 			// catenation symbol
	lparen_t, 		// left parenthesis
	rparen_t 		// right parenthesis
};


template <class S> class subexp;
template <class S> class re;
template <class S> class empty_set;
template <class S> class empty_string;
template <class S> class symbol_exp;
template <class S> class cat_exp;
template <class S> class plus_exp;
template <class S> class star_exp;
template <class S> class fm;
template <class S> class fl;


/****************************************************************************
                                  subexp
 ***************************************************************************/

// The descriptions of the member functions given here also apply to
// empty_set, empty_string, symbol_exp, cat_exp, plus_exp and star_exp.

template <class S>
class subexp
{
//	friend	class 	ostream; //by SH 05/20/2005

private:
	subexp<S>&	operator=(const subexp<S>&) { return *this; }
			// assignment:  assign this subexp to be a copy of
			//  the parameter subexp.

public:
			subexp() { }
			// default constructor

			subexp(const subexp<S>&) { }
			// copy constructor:  initialize this subexp to be a
 			//  copy of the parameter subexp

	virtual 	~subexp() { }
			// destructor

	virtual	int	operator==(const subexp<S>*) const = 0;
			// test for equality:  returns 1 if this subexp is
			//  equal to the parameter subexp and 0 otherwise.

	virtual	int	operator!=(const subexp<S>* s) const
			// test for inequality:  returns 1 if this subexp is
			//  different from the parameter subexp and 0
			//  otherwise.
			{ return this == s ? 0 : 1;}

	virtual	int	operator<(const subexp<S>*) const = 0;
			// less than:  returns 1 if this subexp is less than
			//  the parameter subexp and 0 otherwise.  See header
			//  comments for notes on comparison of expressions.

	virtual	int	operator>(const subexp<S>*) const = 0;
			// greater than:  returns 1 if this subexp is greater
			//  than the parameter subexp and 0 otherwise.  See
			//  header comments for notes on comparison of
			//  expressions.

	virtual subexp<S>* clone() const = 0;
			// allocate a new subexp and copy the contents of this
			//  subexp into the new subexp (deep copy).  Returns
			//  a pointer to the new subexp.

	virtual	int	compare_empty_string() const
			// compare this subexp to the empty string.  Returns
			//  1 if this subexp is greater than the empty string,
			//  0 if they are equal, and -1 if this subexp is
			//  less than the empty string.
			{ return 1; }

	virtual	int	compare_empty_set() const
			// compare this subexp to the empty set.  Returns 1 if
			//  this subexp is greater than the empty set, 0 if
			//  they are equal, and -1 if this subexp is less than
			//  the empty string.
			{ return 1; }

	virtual	int	compare_cat_exp(const subexp<S>*, const subexp<S>*)
					const
			// compare this subexp to the cat_exp which would
			//  result from the catenation of the first and second
			//  parameter.  Returns 1 if this subexp is greater
			//  than the cat_exp, 0 if they are equal and -1 if
			//  this subexp is less than the cat_exp.
			{ return 1; }

	virtual	int	compare_plus_exp(const subexp<S>*, const subexp<S>*)
					const
			// compare this subexp to the plus_exp which would
			//  result from the union of the first and second
			//  parameter.  Returns 1 if this subexp is greater
			//  than the plus_exp, 0 if they are equal and -1 if
			//  this subexp is less than the plus_exp.
			{ return 1; }

	virtual	int	compare_star_exp(const subexp<S>*) const
			// compare this subexp to the star_exp which would
			//  result from the parameter after Kleene star
			//  operation.  Returns 1 if this subexp is greater
			//  than the star_exp, 0 if they are equal and -1 if
			//  this subexp is less than the star_exp.
			{ return 1; }

	virtual	int	compare_symbol_exp(const S&) const
			// compare this subexp to an expression which
			//  represents the parameter symbol.  Returns 1 if
			//  this subexp is greater than the parameter symbol,
			//  0 if they are equal and -1 if this subexp is
			//  less than the parameter symbol.
			{ return 1; }

	virtual int	contains_empty_set() const
			// returns 1 if this subexp contains the empty_set as
			//  one of its subexpressions and 0 otherwise.
			{ return 0; }

	virtual int	contains_empty_string() const
			// returns 1 if this subexp contains the empty_string
			//  as one of its subexpressions and 0 otherwise.
 			{ return 0; }

	virtual void	subexp_to_fm(fm<S>&) const = 0;
			// convert this subexp to a finite machine.  The
			//  parameter fm returns the resulting machine.

	virtual void	subexp_to_fl(fl<S>&) const = 0;
			// convert this subexp to a finite language.  If this
			//  subexp contains a star, the expressions is
			//  converted as if the star were not present (e.g.
			//  the finite machine which is created from "ab*c"
			//  actually represents "abc").  The parameter fl
			//  returns the resulting language.

	virtual int	is_empty_set() const
			// return 1 if this subexp evaluates the empty set,
			//  0 otherwise.
			{ return 0; }

	virtual int	is_empty_string() const
			// return 1 if the language corresponding to this
			//  subexp contains only the empty string, 0 otherwise.
			{ return 0; }

	virtual int	is_finite() const
			// returns 1 if the language represented by this re
			//  is finite (contains a finite number of finite
			//  length words), 0 otherwise.
			{ return 1; }

	virtual subexp<S>*	minimize();
			// minimizes the regular expression represented by
 			//  this re.  Returns a reference to this re.

	virtual	void	print(std::ostream&, int) const
			// prints this subexp on the parameter output stream.
			//  The second parameter is the priority of the
			//  subexp of which this subexp is a part. The
			//  priority is used to determine whether or not
			//  brackets are needed around the expression.  If
			//  this subexp is part of an expression with higher
			//  priority than itself (as determined by the value
			//  of priority:  star = 3, cat = 2, plus = 1,
			//  empty_set, empty_string, symbol_exp = 0) then the
			//  output for this subexp is put in brackets.  For
			//  example, "(a+b)*" will be correctly outputted with
			//  brackets rather than "a+b*".  The output stream
			//  must be valid and open before calling this
			//  function.
			{ }

	virtual int	size() const = 0;
			// returns the number of components in this subexp.
			//  This size does not reflect the size of the
			//  expression when printed, and does not count
			//  brackets.  The total is calculated by adding 1 for
			//  each empty set, empty string, symbol, plus
			//  expression, catenated expression and starred
			//  expression.

	virtual	subexp<S>*	star();
			// perform the star operation on this subexp.  A
			//  reference to this subexp is returned.

};



/****************************************************************************
                                empty_set
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class empty_set : public subexp<S>
{
public:
			empty_set() { }
			empty_set(const empty_set<S>&) { }
			~empty_set() { }
	empty_set<S>&	operator=(const empty_set<S>&)
			{ return *this; }
	int		operator==(const subexp<S>* s) const
			{ return s->compare_empty_set() == 0 ? 1 : 0; }
	int		operator<(const subexp<S>* s) const
			{ return s->compare_empty_set() < 0 ? 1 : 0; }
	int		operator>(const subexp<S>* s) const
			{ return s->compare_empty_set() > 0 ? 1 : 0; }
	subexp<S>*	clone() const
			{ return new empty_set<S>; }
	int		compare_empty_set() const
			{ return 0; }
	int		compare_symbol_exp(const S&) const
			{ return -1; }
	int		compare_empty_string() const
			{ return -1; }
	int		compare_cat_exp(const subexp<S>*,const subexp<S>*)const
			{ return -1; }
	int		compare_plus_exp(const subexp<S>*,const subexp<S>*)
						const
			{ return -1; }
	int		compare_star_exp(const subexp<S>*) const
			{ return -1; }
	int		contains_empty_set() const
			{ return 1; }
	void		subexp_to_fm(fm<S>&) const;
	int		is_empty_set() const
			{ return 1; }
#ifdef	ATT
	void		print(std::ostream& os,int) const;
#endif
#ifndef	ATT
	void		print(std::ostream& os,int) const
			{ os << re<S>::re_eset;	}
#endif
	int		size() const
			{ return 1; }
	void		subexp_to_fl(fl<S>&) const;
};


/****************************************************************************
                                 empty_string
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class empty_string : public subexp<S>
{
public:
			empty_string() { ; }
			empty_string(const empty_string<S>&) { }
			~empty_string() { }
	empty_string<S>&	operator=(const empty_string<S>&)
			{ return *this; }
	int		operator==(const subexp<S>* s) const
			{ return s->compare_empty_string() == 0 ? 1 : 0; }
	int		operator<(const subexp<S>* s) const
			{ return s->compare_empty_string() < 0 ? 1 : 0; }
	int		operator>(const subexp<S>* s) const
			{ return s->compare_empty_string() > 0 ? 1 : 0; }
	subexp<S>*	clone() const
			{ return new empty_string<S>; }
	int		compare_empty_string() const
			{ return 0; }
	int		compare_cat_exp(const subexp<S>*,const subexp<S>*)const
			{ return -1; }
	int		compare_plus_exp(const subexp<S>*,const subexp<S>*)
						const
			{ return -1; }
	int		compare_star_exp(const subexp<S>*) const
			{ return -1; }
	int		compare_symbol_exp(const S&) const
			{ return -1; }
	void		subexp_to_fm(fm<S>&) const;
	int		is_empty_string() const
			{ return 1; }
#ifdef	ATT
	void		print(std::ostream& os,int) const;
#endif

#ifndef	ATT
	void		print(std::ostream& os,int) const
			{ os << re<S>::re_estring; }
#endif
	int		size() const
			{ return 1; }
	void		subexp_to_fl(fl<S>&) const;
};


/****************************************************************************
                                symbol_exp
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class symbol_exp : public subexp<S>
{
#ifndef	ATT
private:
		static pool<symbol_exp<S> >	symbol_pool;
#endif

protected:
		S	content;

public:
			symbol_exp() { ; }
			symbol_exp(const S& s) : content(s) { }
			symbol_exp(const symbol_exp<S>& s) :
				content(s.content) { }
			// ~symbol_exp() {  }
	symbol_exp<S>&	operator=(const symbol_exp<S>&);
	int		operator==(const subexp<S>* s) const
			{ return s->compare_symbol_exp(content) == 0 ? 1 : 0; }
	int		operator<(const subexp<S>* s) const
			{ return s->compare_symbol_exp(content) < 0 ? 1 : 0; }
	int		operator>(const subexp<S>* s) const
			{ return s->compare_symbol_exp(content) > 0 ? 1 : 0; }
	int		compare_cat_exp(const subexp<S>*,const subexp<S>*)const
			{ return -1; }
	int		compare_plus_exp(const subexp<S>*,const subexp<S>*)
						const
			{ return -1; }
	int		compare_star_exp(const subexp<S>*) const
			{ return -1; }
	int		compare_symbol_exp(const S& s) const;
	subexp<S>*	clone() const
			{ symbol_exp<S>* ptr = new symbol_exp<S>(content);
			  return ptr;
			}
	void		subexp_to_fm(fm<S>&) const;
#ifndef	ATT
	void		print(std::ostream& os, int) const
			{ os << content; }
#endif
#ifdef	ATT
	void		print(std::ostream& os, int) const;
#endif
	int		size() const
			{ return 1; }
        void*           operator new(size_t);
        void            operator delete(void* p);
	void		subexp_to_fl(fl<S>&) const;
};



/****************************************************************************
                                  cat_exp
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class cat_exp : public subexp<S>
{
	friend class  subexp<S>;
	friend class  re<S>;

#ifndef	ATT
private:
		static pool<cat_exp<S> >	cat_pool;
#endif
protected:

		subexp<S>*	left;
		subexp<S>*	right;

public:
			cat_exp()  { left = right = 0; }
			cat_exp(const re<S>& l, const re<S>& r)
			{
				left = l.p->clone();
				right = r.p->clone();
			}
			cat_exp(const cat_exp<S>& r)
			{
				left = r.left->clone();
				right = r.right->clone();
			}
			~cat_exp()
			{ delete left; delete right; }
	cat_exp<S>&	operator=(const cat_exp<S>&);
	int		operator==(const subexp<S>* s) const
			{ return s->compare_cat_exp(left, right) == 0 ? 1 : 0;}
	int		operator<(const subexp<S>* s) const
			{ return s->compare_cat_exp(left, right) < 0 ? 1 : 0; }
	int		operator>(const subexp<S>* s) const
			{ return s->compare_cat_exp(left, right) > 0 ? 1 : 0; }
	int		compare_cat_exp(const subexp<S>*,const subexp<S>*)
						const;
	int		compare_plus_exp(const subexp<S>*,const subexp<S>*)
						const
			{ return -1; }
	int		compare_star_exp(const subexp<S>*) const
			{ return -1; }
	subexp<S>*	clone() const
			{ cat_exp<S>* ptr = new cat_exp<S>;
			  ptr->left = left->clone();
			  ptr->right = right->clone();
			  return ptr;
			}
	int		contains_empty_set() const
			{ return left->contains_empty_set()
				|| right->contains_empty_set(); }
	int		contains_empty_string() const
			{ return left->contains_empty_string()
				|| right->contains_empty_string(); }
	void		subexp_to_fm(fm<S>&) const;
	int		is_empty_set() const
			{ return left->is_empty_set()
				|| right->is_empty_set() ? 1 : 0; }
	int		is_empty_string() const
			{ return left->is_empty_string()
				&& right->is_empty_string() ? 1 : 0; }
	int		is_finite() const
			{ return left->is_finite() && right->is_finite()
				? 1 : 0; }
	subexp<S>*	minimize();
	void		print(std::ostream&,int) const;
	int		size() const
			{ return 1 + left->size() + right->size(); }
        void*           operator new(size_t);
        void            operator delete(void* p);
	void		subexp_to_fl(fl<S>&) const;

};



/****************************************************************************
                                  plus_exp
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class plus_exp : public subexp<S>
{
	friend class subexp<S>;
	friend class  re<S>;

#ifndef	ATT
private:
		static pool<plus_exp<S> >	plus_pool;
#endif
protected:

		subexp<S>*	left;
		subexp<S>*	right;

public:
			plus_exp() { left = right = 0; }
			plus_exp(const re<S>& l, const re<S>& r)
			{
				left = l.p->clone();
				right = r.p->clone();
			}

			plus_exp(const plus_exp<S>& s)
			{
				left = s.left->clone();
				right = s.right->clone();
			}

			~plus_exp()
			{ delete left; delete right; }

	plus_exp<S>&	operator=(const plus_exp<S>&);

	int		operator==(const subexp<S>* s) const
			{ return s->compare_plus_exp(left,right) == 0 ? 1 : 0;}
	int		operator<(const subexp<S>* s) const
			{ return s->compare_plus_exp(left,right) < 0 ? 1 : 0; }

	int		operator>(const subexp<S>* s) const
			{ return s->compare_plus_exp(left,right) > 0 ? 1 : 0; }

	int		compare_plus_exp(const subexp<S>*,const subexp<S>*)
						const;
	int		compare_star_exp(const subexp<S>*) const
			{ return -1; }
	subexp<S>*	clone() const
			{ plus_exp<S>* ptr = new plus_exp<S>;
			  ptr->left = left->clone();
			  ptr->right = right->clone();
			  return ptr;
			}
	int		contains_empty_set() const
			{ return left->contains_empty_set()
				|| right->contains_empty_set(); }
	int		contains_empty_string() const
			{ return left->contains_empty_string()
				|| right->contains_empty_string(); }
	void		subexp_to_fm(fm<S>&) const;
	int		is_empty_set() const
			{ return left->is_empty_set() &&
				right->is_empty_set() ? 1 : 0; }
	int		is_empty_string() const
			{ if (left->is_empty_string())
			  { if (right->is_empty_string() ||
			        	right->is_empty_set())
				return 1; else return 0; }
			  if (left->is_empty_set() && right->is_empty_string())
				return 1;
			  return 0;
			}
	int		is_finite() const
			{ return left->is_finite() && right->is_finite()
				? 1 : 0; }
	subexp<S>*	minimize();
	void		print(std::ostream&,int) const;
	int		size() const
			{ return 1 + left->size() + right->size(); }
        void*           operator new(size_t);
        void            operator delete(void* p);
	void		subexp_to_fl(fl<S>&) const;
};



/****************************************************************************
                                 star_exp
 ***************************************************************************/

// see subexp for description of member functions

template <class S>
class star_exp : public subexp<S>
{
	friend class subexp<S>;
	friend class  re<S>;

#ifndef	ATT
private:
		static pool<star_exp<S> >	star_pool;
#endif

protected:
		subexp<S>*	left;

public:
 			star_exp() { left = 0;}
			star_exp(const re<S>& r)
			{ left = r.p->clone(); }
			star_exp(const star_exp<S>& s)
			{ left = s.left->clone(); }
 			~star_exp()
			{ delete left; }
	star_exp<S>&	operator=(const star_exp<S>&);
	int		operator==(const subexp<S>* s) const
			{ if (s == 0) return 0;
			else return s->compare_star_exp(left) == 0 ? 1 : 0; }
	int		operator<(const subexp<S>* s) const
			{ return s->compare_star_exp(left) < 0 ? 1 : 0; }
	int		operator>(const subexp<S>* s) const
			{ return s->compare_star_exp(left) > 0 ? 1 : 0; }
	int		compare_star_exp(const subexp<S>*) const;
	subexp<S>*	clone() const
			{ star_exp<S>* ptr = new star_exp<S>;
			  ptr->left = left->clone();
			  return ptr; }
	int		contains_empty_string() const
			{ return left->contains_empty_string(); }
	int		contains_empty_set() const
			{ return left->contains_empty_set(); }
	void		subexp_to_fm(fm<S>&) const;
	int		is_empty_set() const
			{ return 0; }
	int		is_empty_string() const
			{ return left->is_empty_string() ||
				left->is_empty_set() ? 1 : 0; }
	int		is_finite() const
			{ return left->is_empty_string() ||
				left->is_empty_set() ? 1 : 0; }
#ifdef	ATT
	void		print(std::ostream& os,int) const;
#endif
#ifndef	ATT
	void		print(std::ostream& os,int) const
			{ left->print(os, 3); os << re<S>::re_star; }
#endif
	subexp<S>*	star()
			{ return this; }
	int		size() const
			{ return 1 + left->size(); }
        void*           operator new(size_t);
        void            operator delete(void* p);
	void		subexp_to_fl(fl<S>&) const;
};



/****************************************************************************
                                    re
 ***************************************************************************/

template <class S>
class re;

template <class S>
std::istream& operator >> ( std::istream&, re<S>&);

template <class S>
std::ostream& operator << ( std::ostream&, const re<S>&); //by SH 05/25/2005


template <class S>
class re
{
//	friend class istream;
  //by SH 05/20/2005

public:

	// Symbols and delimitors for regular expressions.  See
	//  (alphabetdirectory)/lexical.h for defintions
	static	char	re_star;
	static	char	re_plus;
	static	char	re_cat;
	static	char	re_lparen;
	static	char	re_rparen;
	static	char*	re_estring;
	static	char*	re_eset;
	static	char	re_left_delimiter;
	static	char	re_right_delimiter;
	static	char	re_left_symbol_delimiter;
	static	char	re_right_symbol_delimiter;

	/*friend
	ostream&	operator<<(ostream&, const re<S>&);

	friend
	istream&	operator>>(istream&, re<S>&);
*/
#ifdef _MSC_VER
	#if _MSC_VER<=1200

	friend
	std::ostream&	operator<<(std::ostream&, const re<S>&);


	friend
	std::istream&	operator>>(std::istream&, re<S>&);

	#endif

	#if  _MSC_VER>=1300

    friend std::ostream& operator << <S> ( std::ostream&, const re<S>&);

    friend std::istream& operator >> <S> ( std::istream&, re<S>&);

	#endif
#endif

	#ifndef _MSC_VER
	friend std::ostream& operator << <S> ( std::ostream&, const re<S>&);

    friend std::istream& operator >> <S> ( std::istream&, re<S>&);
	#endif       //by SH 05/20/2005


	friend		class cat_exp<S>;
	friend		class plus_exp<S>;
	friend		class star_exp<S>;

protected:

	subexp<S>*	p;	// pointer to the recursively defined regular
				//  expression represented by this re.

private:

	int		fill_buffer(std::istream&,char**,char,char);
			// scans the parameter input stream and reads input
			//  delimited by the third and fourth parameters into
			//  the string buffer pointed to by the second
			//  parameter.  Returns the number of characters
			//  read from the stream.

public:
			re() { p = 0; }
			// default constructor:  initialize to clear
			//  expression

			re(const re<S>& r)
			// copy constructor:  initialize this expression to
			//  be a copy of the parameter expression
			{ if (r.is_clear()) p = 0; else p = r.clone();  }

			~re()
			// destructor
			{ delete p; }

	re<S>&		operator=(const re<S>&);
			// assignment:  assign this expression to be a copy
			//  of the parameter expression.  Returns a reference
			//  to this re.

	re<S>&		operator=(const subexp<S>&);
			// assignment:  assign this expression to be a copy
			//  of the parameter subexpression.  Returns a
			//  reference to this re.

	int		operator==(const re<S>& r) const
			// test for equality:  determine if this expression
			//  is equal to the parameter expression.  Equality
			//  is judged by the surface structure of the
			//  expression, not the language represented.  Returns
			//  1 if the expressions are equal, 0 otherwise.
			{ if (p == 0 && r.p == 0) return 1;
				else if (p == 0 || r.p == 0) return 0;
				else return *p == r.p ? 1 : 0; }

	int		operator!=(const re<S>& r) const
			// test for inequality:  determine is this expression
			//  is different from the parameter expression.
			//  Difference is judged by the surface structure of
			//  the expression, not the language represented.
			//  Returns 1 if the expression are different, 0
			//  otherwise.
			{ if (p == 0 && r.p == 0) return 0;
				else if (p == 0 || r.p == 0) return 1;
				else return *p == r.p ? 0 : 1; }

	int		operator<(const re<S>& r) const
			// less than:  returns 1 if this expression is less
			//  than the parameter expression and 0 otherwise.
			//  The comparison depends on the definition of
			//  operator< for S and the surface structure of the
			//  expression.  See remarks in file header.
			{ if (p == 0 && r.p == 0) return 0;
				else if (p == 0) return 1;
				else if (r.p == 0) return 0;
				else return *p < r.p ? 1 : 0; }

	int		operator>(const re<S>& r) const
			// greater than:  returns 1 if this expression is
			//  greater than the parameter expression and 0
			//  otherwise. The comparison depends on the definition
			//  of operator< for S and the surface structure of
			//  the expression.  See remarks in file header.
			{ if (p == 0 && r.p == 0) return 0;
				else if (p == 0) return 0;
				else if (r.p == 0) return 1;
				else return *p > r.p ? 1 : 0; }

	re<S>&		operator^=(const re<S>&);
			// catenates the parameter expression to this
			//  expression and stores the result in this re.
			//  Returns a reference to this re.

	re<S>&		operator^=(re<S>*);
			// catenates the expression pointed to by the
			//  parameter to this expression and stores the result
			//  in this re.  Returns a reference to this re.

	re<S>&		operator+=(const re<S>&);
			// union: make a new expression which is the union
			//  of this re's current contents and the parameter
			//  expression and store the result in this re.
			//  Returns a reference to this re.

	re<S>&		operator+=(re<S>*);
			// union: make a new expression which is the union of
			//  this re's current contents and the expression
			//  pointed to by the parameter and store the result
			//  in re.  Returns a reference to this re.

	re<S>&		cat(subexp<S>*);
			// catenates the subexpression pointed to by the
			//  parameter to this expression and stores the
			//  result in this re.  Returns a reference to this re.

	re<S>&		plus(subexp<S>*);
			// union: make a new expression which is the union of
			//  this re's current contents and the subexpression
			//  pointed to by the parameter and store the result
			//  in re.  Returns a reference to this re.

	void		clear()
			// clear the contents of this re.
			{ delete p; p = 0; }

	subexp<S>*	clone() const
			// returns a pointer to a new subexpression which is
			//  an exact copy of this expression.
			{ return p == 0 ? 0 : p->clone(); }

	int		contains_empty_set() const
			// returns 1 if this re contains the empty as one
			//  of its subexpressions and 0 otherwise.
			{ return p == 0 ? 0 : p->contains_empty_set(); }

	int		contains_empty_string() const
			// returns 1 if this re contains the empty string as
			//  one of its subexpressions and 0 otherwise.
			{ return p == 0 ? 0 : p->contains_empty_string(); }

	void		fltore(fl<S>&);
			// converts the parameter language to a regular
			//  expression and stores the result as this re.

	void		fmtore(fm<S>&);
			// converts the parameter fm to a minimal regular
			//  expression and stores the result as this re.

	int		is_clear() const
			// returns 1 if this expression is clear (does not
			//  contain a regular expression), 0 otherwise.
			{ return p == 0 ? 1 : 0; }

	int		is_empty_set() const
			// returns 1 if this re evaluates to the empty set,
			//  0 otherwise.
			{ return p == 0 ? 0 : p->is_empty_set(); }

	int		is_empty_string() const
			// returns 1 if the language corresponding to this re
			//   contains only the empty word, 0 otherwise.
			{ return p == 0 ? 0 : p->is_empty_string(); }

	int		is_finite() const
			// returns 1 if the language represented by this re
			//  is finite (contains a finite number of finite
			//  length words), 0 otherwise.
			{ return p == 0 ? 0 : p->is_finite(); }

	re<S>&		make_empty_set()
			// delete the current contents of this re and replace
			//  them by an expression which represents the empty
			//  set.  Returns a reference to this re.
			{ delete p; p = new empty_set<S>; return *this; }

	re<S>&		make_empty_string()
			// delete the current contents of this re and replace
			//  them by an expression which represents the empty
			//  string.  Returns a reference to this re.
			{ delete p; p = new empty_string<S>; return *this; }

	re<S>&		make_symbol(const S& s)
			// delete the current content of this re and replace
			//  them by an expression which contains only the
			//  parameter symbol.  Returns a reference to this re.
			{ delete p; p = new symbol_exp<S>(s); return *this; }

	re<S>&		minimize();
			// minimizes the regular expression represented by
 			//  this re.  Returns a reference to this re.

	re<S>*		parse(std::istream&);
			// read a regular expression from the parameter stream.
			//  A regular expression is either a term (see below),
			//  a catenation of two expressions or the union of
			//  two expressions.  Returns a pointer to the
			//  re.

	void		print(std::ostream& os, int) const
			// prints this re the output stream.  The second
			//  parameter can have any arbitrary value.
			{ if (p != 0) p->print(os, 0); }

	void		retofm(fm<S>&) const;
			// converts this regular expression to a finite
			//  machine and stores the result in the parameter fm.

	void		retofl(fl<S>&) const;
			// converts this regular expression to a finite
			//  language.  Note that any regular expression which
			//  includes a Kleene star term cannot be represented
 			//  as a finite language (unless the star is applied
			//  to the empty string).  If this function is called
			//  on such an expression, it will be converted
			//  anyway, but the star will be ignored (for example,
			//  the fm produced for "(a+b)*c" will be equivalent
			//  to "(a+b)c").  After execution, this re will be
			//  unchanged and the parameter fl will hold the new
			//  finite language.

	int		size() const
			// returns the number of components in the regular
			//  expression.  This size does not reflect the size
			//  of the expression when printed, and does not count
			//  brackets.  The total is calculated by adding 1 for
			//  each empty set, empty string, symbol, plus
			//  expression, catenated expression and starred
			//  expression.
			{ return p == 0 ? 0 : p->size(); }

	re<S>&		star();
			// perform the star operation on this regular
			//  expression.  A reference to this re is returned.

	subexp<S>*	term(std::istream&);
			// read a term from the parameter stream and store the
			//  result as a subexpression.  A term is either a
			//  bracketed expression, an empty set, an empty
			//  stream, a symbol or term followed by a star.
			//  Returns a pointer to the subexpression.

	token_type	token(std::istream&);
			// returns the the value of the next token on the
			//  input stream without actually reading the token
			//  from the stream.  It will advance past any
			//  whitespace on the beginning of the stream to
			//  arrive at a token.  If no valid token is found, an
			//  error message is printed to the standard error
			//  stream and error_t is returned.  The stream must
			//  be valid and open before calling this function.
};

#define		RE_CLASS_DEFINITION
#endif
