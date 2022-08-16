//#This comes from 3.1.4-new
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<iostream.h>


template <class dataType>class mNode
{
 public:
 dataType data;
 mNode *next; // pointer to next element in the list
 mNode *prev;
};

template <class dataType>class mList
{
public:
 mNode<dataType> *base;  // base node of the list
			 // does not contain any data
			 // only serves as a start marker
 mNode<dataType> *latest; //reference to recently modefied or accessed list item
 mNode<dataType> *endFlag;//end marker of list

 long latest_index;
                 	//current size of the list
			 //this is a expandable number
public:
long size;
	//contructor
	mList();
	//destructor
	~mList();

long memory_used();
			 //overload the "=" operator to use this linked list
			 //as if it is a simple array . here we are hiding the implementation from user
dataType &operator[](int index);  //only operator that is visible to user
};

//implimentation of the member functions start here
template <class dataType> mList<dataType>::mList()
{

	   size=0;
	   base = new mNode<dataType>;
	   latest =  new mNode<dataType>;
	   endFlag = new mNode<dataType>;
	   //std::cout<<"base"<<base;
	   if(base==NULL)
		std::cout<<"memry Error";

	   base->next=NULL;
	   base->prev=NULL;
		latest->next=NULL;
		latest->prev=NULL;
	  // base->data=-1;
}
template <class dataType> mList<dataType>::~mList()
{
		//DEBUG0
		//	std::cout<<"freeing up memory of "<<this;
		// free all the memory allocated for the object
		//start
		long i;
		mNode<dataType> *temp;   // serves as location pointer in the list while looping
		mNode<dataType> *temp2;
		temp=base;
		//serch for that element from begining
		 for(i=0;i<=size;i++)
		 {
	//		 std::cout<<"deallocation i="<<i<<"\t";
			 temp2=temp;
			temp=temp->next;
			 delete temp2;

		 }
		 //are we at the end of the list ? did we properly deallocated every thing of the list
		 //if so last node's next will be next
		 if(temp!=NULL)
			std::cout<<"OH error with memory free ";
}


template <class dataType> long mList<dataType>::memory_used()
			//function for calculating memory used by our dynamic array object in total (this instance only)
{
	return (size+3)*sizeof(dataType)+2*sizeof(long);
}



template <class dataType> dataType &mList<dataType>::operator[](int index)
			 //overload the "=" operator to use this linked list
			 //as if it is a simple array . here we are hiding the implementation from user

{
	   mNode<dataType> *temp;   // serves as location pointer in the list while looping
	   mNode<dataType> *temp2;  //very unstable buffer for memory allcation for each
			 //if index is < size okay we are aking for a existing element in the liked list
	   temp= new mNode<dataType>;

	   if(index<size)
	   {
			 long distance_from_start=index;
			 long distance_from_end=abs(size-1-index);
			 long distance_from_latest=abs(latest_index-index);
			 long i=0;

			 if(  (distance_from_start<=distance_from_end)  && (distance_from_start<=distance_from_latest) )
			 {	//normal sequential search from start
					 temp=base->next;
					//serch for that element from begining
					for(i=0;i<index;i++)
					 temp=temp->next;

			 }else if((distance_from_latest<=distance_from_start)  && (distance_from_latest<=distance_from_end) )
			 {	 //is latest operation's  index is nearest to our search index?
				 if((index-latest_index)>=0)
				 {
					temp=latest;
					//serch for that element from index of latest operation
					 for(i=latest_index;i<index;i++)
					 temp=temp->next;
				 }
				 else
				 {
				 	temp=latest;
				  //serch for that element back ward from latest index
					 for(i=latest_index;i>index;i--)
					 temp=temp->prev;
				  }

			 }else
			 {
				// it is closer to the end point
				// do a backward search from end
				temp=endFlag;
				for(i=size-1;i>index;i--)
					 temp=temp->prev;
			 }
			 //return a reference to the element
			 latest=temp;
			 latest_index=index;
			 return temp->data;
	   }
	  else //if index is greater than size
	  {

		  if(size>0)
			 temp=endFlag;

		  else
		  {	 temp=base;
				//initalize latest operation index
			latest_index=0;
		  }
			//okay its a over flow ! expand the memory
			//use previous operation index as start point to reduce sequential search time
			 for(long j=size;j<index+1;j++)
			 {
					 //get new node
					 temp2=new mNode<dataType>;
					 //append that to existing list
					 temp2->prev=temp;
					 temp->next=temp2;
					 temp2->next=NULL;

					 temp=temp2;
					if(size==0 && j==0)
						latest=temp;
			 }
			 size=index+1;
			 //store index to last element for future access
					 endFlag=temp2;
					 endFlag->prev=temp2->prev;
					 endFlag->next=NULL;
			 //return the reference to last element
			  return temp->data;
	  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                        specialized implementation for mNode for a string array                     ////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <> class mNode <char *>
{
 public:
 char * data;
 mNode *next; // pointer to next element in the list
 mNode *prev;
 //we are using constructors and destructors because we are using dynamic memory allocation in this instead of
 //simple data types as in generic case
 mNode()
 {	data= (char *) malloc(10*sizeof(char));  }
 ~mNode()
 { 	free(data); }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															NOTE																////
//	add any more specialized implementations for node if you need special functionality like above one ; usually classes
//	structures will work fine with out special implementation.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///        Dummy main() for testing . commented to avoid linker errors use only when not included in other files         ///////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*main()
{
	mList<char *> m;
	mList <int > n;
	int scrap =-1;
	std::cout<<std::endl;
	std::cout<<"Allocating ....."<<std::endl;
	printf("Element %6d",scrap);
	long SZE=100000;
	for(long i=0;i<SZE;i++)
	{

		printf("\b\b\b\b\b\b");
		printf("%6d",i);

		strcpy(m[i],"uday");
		n[i]=i;

	}

	std::cout<<std::endl<<"Printing....."<<std::endl;

    for(i=0;i<SZE;i++)
	{
		printf("\b\b\b\b\b\b\b\b\b\b\b");
		printf("%6d %s",n[i],m[i]);
		//getch();
		//std::cout<<n[i]<<")"<<m[i]<<"\t";
	}

	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<"memory used= "<<n.memory_used()<<" BYTES.";
	std::cout<<std::endl;
	std::cout<<std::endl;
	return 0;
}
*/
