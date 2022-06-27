/*
This is the implementation of (fast) gap tree in the paper
computing all l-cover auotomata fast by
Artur Jez and Andreas Maletti

Ray and Sherry 2011 Summer 
Supervisor: Dr. Campeanu
*/




#ifndef		NODE_CLASS_DEFINITION

template <class Label> 
class fl;

template <class Label> 
class fcm;

template <class Label>
class fm;


template <class Label>
class atstate;


template <class Label>
class node;


template <class Label>
class node
{
public:

array<node<Label> *> children;

node<Label> * father;

int gap_with_father;

set<state> *  states_set;


node()
{
children =NULL;
father=NULL;
gap_with_father=-1;
states_set=NULL;
}

node(const node<Label>& x)
{
children=x.children;
gap_with_father=x.gap_with_father;
father=x.father;
states_set=x.states_set;
}

~node()
{
children =NULL;
father=NULL;
gap_with_father=-1;
states_set=NULL;
}

void merge(){}


void report()
{
std::cout<<"this node associates with set:"<<std::endl<<"{";
for(int a=0;a<(*states_set).size();a++)
        std::cout<<(*states_set)[a]<<" ";
std::cout<<"}"<<std::endl;

if(father!=NULL)
{
std::cout<<"                    father is "<<"{";
for(int a=0;a<father->states_set->size();a++)
        std::cout<<(*(father->states_set))[a]<<" ";
std::cout<<"}"<<std::endl;
}

std::cout<<"gap is"<<gap_with_father<<std::endl;

}


bool is_node_with_set(const set<state>& s)
{
//std::cout<<"compare to"<<s<<std::endl;

//std::cout<<"this node is "<<*states_set<<std::endl;

if(states_set==NULL)
{
	std::cout<<"incompleted node!!!!"<<std::endl;
	return false;
}
if(s==(*states_set)){       return true;}

return false;
}


};

#define		NODE_CLASS_DEFINITION
#endif
