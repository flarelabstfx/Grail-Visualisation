//#This comes from 3.1.4-new
//	This code copyright (c) by the Grail project.
//	No commercial use permitted without written consent.
//	August 1994


/***************************************************************************

  File:  array.h
  -----

  Description:
  ------------
    This file contains the type definition for a linked list template
    class.  The template class has one parameter, Item, which specifies
    the type of item to store in the list.  The list will grow as
    required to allow an unlimited number of items to be added.

    list is a subclass of array and inherits the following functions from
    the array template class:

	array<Item>&	clear()
                        // clear the contents of this list

 	int		contain(const array<Item>&) const;
                        // returns 1 if all the elements in the parameter
                        //  list are contained in this list, 0 otherwise

	int		is_sorted() const
                        // returns 1 if this list is sorted, 0 otherwise

	static	int	compare(const Item*, const Item*);
                        // returns -1 if the first item is less than the
                        //  second item, 0 if they are equal, and 1
                        //  otherwise

	int		member(const Item&) const;
                        // returns the index of the parameter item if it is
                        //  found in the list, or -1 otherwise

	int		allocated() const
                        // returns the maximum number of elements which this
                        //  list can currently hold

	int		operator==(const array<Item>&) const;
                        // returns 1 if this list contains all the same
                        //  elements as the parameter array, 0 otherwise

	int		operator!=(const array<Item>& l) const
                        // returns 1 if this list contains different elements
                        //  than the parameter list, 0 otherwise

	array<Item>&	operator+=(const array<Item>&);
                        // list union: adds the contents of the parameter
                        //  list to the contents of this list.  The maximum
                        //  size of this list is increased if necessary

 	array<Item>&	operator+=(const Item&);
                        // adds the parameter item to the list.  If the
                        //  list already contains the maximum number of
                        //  elements, its size is doubled before the new
                        //  item is added.

 	array<Item>&	operator-=(const array<Item>&);
                        // array difference: removes any elements which are
                        //  in the parameter list and this list from this
                        //  list.  After this operation, the contents of the
                        //  lists will be disjoint sets of items.

 	array<Item>&	operator-=(const Item&);
                        // removes the parameter item from the list.  If the
                        //  parameter item was not in the list, the list
                        //  contents are unchanged

 	int		operator<(const array<Item>&) const;
                        // returns 1 if the contents of this list are less
                        //  than the contents of the parameter list, 0
                        //  otherwise.  This list is judged to be less than
                        //  if it contains less elements than the parameter
                        //  list or if an element is encountered (in
                        //  sequential order), which is less than the
                        //  corresponding element in the parameter list.

 	int		operator>(const array<Item>& s) const
                        // returns 1 if the contents of this list are greater
                        //  or equal to the contents of the parameter list, 0
                        //  otherwise.  This list is judged to be greater than
                        //  if it contains more elements than the parameter
                        //  list or if an element is encountered in the
                        //  parameter list (in sequential order), which is
                        //  less than the corresponding element in this list.
			{ return s < *this ? 1 : 0; }

 	array<Item>&	remove(int i);
                        // removes the element at index i from this list.

 	void		merge(const array<Item>&);
                        // merges this list with the parameter list.  Both
                        //  lists must be sorted before calling this
                        //  procedure.

	Item&		operator[](int i) const
                        //  returns the ith element of this list.

	int		size() const
                        // returns the number of elements currently contained
                        //  in this list

	void		sort() const;
                        // sorts the elements of this list according to the
                        //  compare function for items.  qsort is used to
                        //  perform the sort.

	void		swap(array<Item>& a)
                        // swaps the contents of this list with the contents
                        //  of the parameter list.

	array<Item>&	unique();
                        // removes any duplicates which are in this list and
                        //  compacts the remaining elements.

	void		unsorted()
                        // sets the status of this list to unsorted regardless
                        //  of the order of the elements.


    Template functions for inputting and outputting arrays (and thus
    lists) are also defined (see classes/array/ostream.src and
    classes/array/istream.src).  The function headers are the following:

	template <class Item>
	ostream&
	operator<<(ostream& os, const array<Item>& s)

	template <class Item>
	istream&
	operator>>(istream& is, array<Item>& s)


    The class specified for Item must have the following operators
    defined:

    Operator:                 Used In Function:
    ---------                 -----------------
    <                         compare, contain, <, member, -+, (sort)
    >                         merge, +=
    ==                        compare, member, -=, unique, (sort)
    !=                        ==, <
    =                         assign, -=, +=, remove, unique
    <<                        operator<<
    >>                        operator>>



  Revision History:
  -----------------
    D.Raymond                       Initial version of source code
    M.Hoeberechts  98/02/04         Added header and comments

 ***************************************************************************/



#ifndef		LIST_CLASS_DEFINITION



#ifdef	ATT
template <class Item> class set;
template <class Item> class array;
template <class Item> class list;
#endif


template <class Item>
class list : public array<Item>
{
	friend	class set<Item>;

public:
	//  constructor/destructor not necessary (array class
	//  takes care of creating and destroying the list)
	// 		list() 		{ ; }
	// 		list(const list<Item>&) { ; }
	// 		~list() 	{  }


	list<Item>&	operator=(const list<Item>& l)
			// assigns this list to contain the same elements
			//  as the parameter list.  If the parameter list
 			//  contains more elements than this list can
			//  currently hold, the size of this list is changed
			//  to match the size of the parameter list.
#ifndef	WATCOM
			{ (array<Item> &) *this = l; return *this; }
#endif
#ifdef	WATCOM
			{ array<Item>::operator=(l); return *this; }
#endif


	list<Item>&	operator=(const Item& l)
			// assigns this list to contain only the parameter
			//  element
#ifndef	WATCOM
			{ (array<Item> &) *this = l; return *this; }
#endif
#ifdef	WATCOM
			{ array<Item>::operator=(l); return *this; }
#endif
};



#define	LIST_CLASS_DEFINITION
#endif
