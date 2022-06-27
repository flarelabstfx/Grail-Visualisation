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
 int fm<Label>::enumerate3(int number, set<string<Label> >& members)
 
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
 
 int fm<Label>::enumerate3(int number, set<string<Label> >& members)
 
 Description:
 This function is a public member of the template class fm (declared
 in classes/re/fm.h).  This function determines the set of words in the
 language represented by this fm.  The words are placed in the
 parameter array (unless there are more than 'number' words in which
 case only 'number' are generated and placed in the array).  The
 function returns the number of words placed in the array.
 
 This function can be called in the following way:
 this_fm.enumerate3(max, word_array);
 
 Parameters:
 int number - the size of the word array
 set<string<Label> >& members - the set to store the words
 
 Return Value:
 int - the number of words placed in the array
 
 ***************************************************************************/

template <class Label>
int
fm<Label>::enumerate3(int number, set<string<Label> >& members)
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
    //set<state>                                   temp1;
    list<set<state>    >                         dest; //original code.
    list<pair<string<Label>, state> >            s_hold;
    fm<Label>                                   curr;//fm
     fm<Label>                                   cur;//fm
    pair<string<Label>, state>                  sss;
    state                                       Big_start;
   
    set<state>                                  current;
    set<state>                                  st_hold;
    inst<Label>                                 temp_ins;
            // check to make sure some final states are reachable
    std::cout << "This is fmenum3 \n";
    reachable_states(dest[0]);
    temp.intersect(dest[0], final_states);// reachable and final
    if (temp.size() == 0)
        return 0;
    
  
    
    
    // begin with start states
    Big_start= max_state();
    Big_start += (1);// max state increacse 1
    temp.clear();
    temp += start_states;
    
    for(i=0; i<temp.size();i++)// all start states
    {
        select (temp[i],SOURCE,cur); // start state as source
        for (j=0; j<cur.size();j++)
        {
            temp_ins.assign(Big_start,cur[j].get_label(),cur[j].get_sink());//make transation with new label and sink state
            add_instruction(temp_ins);// add instruction to fm.
        }
    }
    
    
    
    
    level = 0; // start with 0.
    labels(temp_regexp);
    
    for (i=0; i<temp_regexp.size(); ++i)
    {
        alphabet += temp_regexp[i];
    }// convert all alphabet to list 2018/07/11
    
    alphabet.sort();// sort the alphabet. 2018/07/11**/
    // We should specifify, document the type of sort we use here (quick sort)
    
   
    stuff.clear();
    
    test.assign(Big_start,level,rg);// assign the start state to tuple
        
    stuff += test; //added it to the list
    
    next_dt.clear();// clear the temp queue holder before going in loop.
   
    pre_vious.clear(); // clear the language before generate any words.
    rg.clear();
    
    for ( ;; )// develop word fragments until we have enough
     {   level ++; //add 1 to level.
        
        for(i =0; i <alphabet.size();i++)//for each alphabet in the fm.
            {
        
                for(j=0; j < stuff.size(); j++)// set of state in that level need to go though.
                {
                    select(alphabet[i],stuff[j].get_left(),SOURCE,curr);// select temp[j] as source state, with alphabet i as cur1.
                    
                        if(curr.size()==0)//if no arc
                            continue;
                    
                            for(k =0; k<curr.size(); k++) // if there is arc.
                            {
                                rg = (stuff[j].get_right());
                                rg += curr[k].get_label();//update label
                        
                                test.assign(curr[k].get_sink(),level,rg);//assign to tuple
                              
                                next_dt += test;// add it in to the temp queue.
                                
                                if(final_states.member(curr[k].get_sink()) >= 0) //if the sink state is a final state.
                                    {
                                        
                                        if(rg != pre_vious) //if the language is different than previous one.
                                            {
                                                members += rg; //than added it to word list.
                                                pre_vious = rg; // update the previous language to current one.
                                           
                                                if(members.size() >= number){return(members.size());}
                                            }
                                       
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

