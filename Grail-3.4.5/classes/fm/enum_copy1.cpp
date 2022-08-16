//      Complete rewrite of fmenum
//    This code is LGPL and part of  the Grail project.
//    rewrite by Yong Yu, UPEI, 2018.
//


/***************************************************************************
 
 File:  classes/fm/enum_copy1.src
 -----
 
 Description:
 ------------
 This file contains the definition of the following function:
 int fm<Label>::enumerate1(int number, set<string<Label> >& members)
 
 This function is a public member of the template class fm (declared
 in classes/fm/fm.h).
 
 Revision History:
 -----------------
 The Grail Project               Initial version of source code
 M.Hoeberechts  98/09/06         Added header and comments
 Rui Zhu        10/07/10         Main revision
 Yong Yu        18/07/18         Complete rewrite
 ***************************************************************************/




/***************************************************************************
 
 int fm<Label>::enumerate1(int number, set<string<Label> >& members)
 
 Description:
 This function is a public member of the template class fm (declared
 in classes/re/fm.h).  This function determines the set of words in the
 language represented by this fm.  The words are placed in the
 parameter array (unless there are more than 'number' words in which
 case only 'number' are generated and placed in the array).  The
 function returns the number of words placed in the array.
 
 This function can be called in the following way:
 this_fm.enumerate1(max, word_array);
 
 Parameters:
 int number - the size of the word array
 set<string<Label> >& members - the set to store the words
 
 Return Value:
 int - the number of words placed in the array
 
 ***************************************************************************/

template <class Label>
int
fm<Label>::enumerate1(int number, set<string<Label> >& members)
{
   
    int                                          i;
    int                                          j;
    int                                          k;
    list<Label>                                  alphabet; // all the label
    string<Label>                                pre_vious;
    set<Label>                                   temp_regexp; //alphabet
    list<tuple<state, int, string<Label> > >     stuff; // Yong:listt(queue) for holding tuple
    list<tuple<state, int, string<Label> > >     next_dt;// temp list for holding tuple
    tuple<state,int, string<Label> >             test;// Yong
    string<Label>                                rg;// temp language,yong
    int                                          level; // level
     fm<Label>                                   cur1;//fm
      set<state>                                 temp;//for start states
    list<set<state>    >                         dest; //original code.
    
    
    // check to make sure some final states are reachable
    std::cout << "This is fmenum3 \n";
    reachable_states(dest[0]);
    temp.intersect(dest[0], final_states);
    if (temp.size() == 0)
        return 0;
    
    // minimize the machine
    //reachable_fm();
    //reverse();
    //reachable_fm();
    //reverse();
    
    
    // begin with start states
    
    temp = start_states;
    level = 0;
    labels(temp_regexp);
    for (i=0; i<temp_regexp.size(); ++i)
    {
        alphabet += temp_regexp[i];
    }// convert all alphabet to list 2018/07/11
    
    alphabet.sort();// sort the alphabet. 2018/07/11**/
    // We should specifify, document the type of sort we use here
    
  
    
    stuff.clear();
    
    for(i=0; i< temp.size(); i++)
    {
        test.assign(temp[i],level,rg);
        
        stuff += test;
      
    }//for start states. level is set to 0 labels are all epsilon
    
    next_dt.clear();// clear the temp queue holder before going in loop.
   
    pre_vious.clear(); // clear the language before generate any words.
    
    for ( ;; )// develop word fragments until we have enough
     {   level ++; //add 1 to level.
        
        for(i =0; i <alphabet.size();i++)//for each alphabet in the fm.
            {
        
                for(j=0; j < stuff.size(); j++)// set of state in that level need to go though.
                {
                    select(alphabet[i],stuff[j].get_left(),SOURCE,cur1);// select temp[j] as source state, with alphabet i as cur1.
                    
                        if(cur1.size()==0)//if no arc
                            continue;
                    
                            for(k =0; k<cur1.size(); k++) // if there is arc.
                            {
                                rg = (stuff[j].get_right());
                                rg += cur1[k].get_label();//update label
                        
                                test.assign(cur1[k].get_sink(),level,rg);//assign to tuple
                              
                                next_dt += test;// add it in to the temp queue.
                                
                                if(final_states.member(cur1[k].get_sink()) >= 0) //if the sink state is a final state.
                                    {
                                        
                                        if(rg != pre_vious) //if the language is different than previous one.
                                            {
                                                members += rg; //than added it to word list.
                                                pre_vious = rg; // update the previous language to current one.
                                           
                                                if(members.size() >= number){return(members.size());}
                                            }
                                        //if(!members.member(rg) >=0){//if is not in languages set.
                                          //  members += rg;  // added language to members.
                                            //rg.clear();
                                            //if(members.size() >= number){return(members.size());}
                                            //}
                                    }
                                
                        }
                
                }
        
            }
          if(next_dt.size() ==0 ){return(members.size());}//if there are no more sin state.
            stuff.clear();//clear the original queue after go though all alphabet
            stuff = next_dt;// update the original queue with new state, level and label that is in temp queue.
            next_dt.clear();//clear the temp queue. then start again.
        
    }
    
}

