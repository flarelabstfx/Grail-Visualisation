#include <iostream>
#include <chrono>
#include <cstdint>
#include <vector>
#include <array>
#include <bitset>
using namespace std;
const uint R = 3;
const uint C = 3;
int i;
int j;
int k;
int row_num;
int col_num;

vector<bitset<R*C> > history; // vector of history
bitset<R*C>          temp;
bitset<R*C>          temp_a;
bitset<R*C>          temp_b;
bitset<R*C>          marked;

vector<bitset<R*C> > targets;
vector<bitset<R*C> > temp_targets;




//read the automata and transfer it to table like this

/**
                | S0| S1| S2|                 |S0 |S1 |
            -----------------                 ------------
 row table:   a | 1 | 2 | 0 |      col table:  a | 1 | 1 |
              b | 0 | 1 | 1 |                  b | 1 | 0 |
 
 
 
                |S0 | S1 | S2|
 matrix :     -----------------
              S0 | 1 | 0 | 0 |
              S1 | 0 | 0 | 0 |
 
 
 **/


void mark_1(bitset<R*C> matrx, int r, int col)
{
    int position = R*(r)+(col);
    
    matrx[position] = 1;
    for (i =0; i< matrx.size()/2; i++)
    {
        bool t = matrx[i];
        matrx[i] = matrx[matrx.size()-1-i];
        matrx[matrx.size()-1-i] =t;
    }// reverse
}// mark 1 on row r, colunmn col

void mark_0(bitset<R*C> matrx,  int r, int col)
{
    int position = R*(r)+(col);
    
    matrx[position] =0;
    
    for (i =0; i< matrx.size()/2; i++)
    {
        bool t = matrx[i];
        matrx[i] = matrx[matrx.size()-1-i];
        matrx[matrx.size()-1-i] =t;
    }// reverse
}// mark 0 on row r, colunmn col


bitset<R*C> transation_a(bitset<R*C> a)
{
    temp =a;
    for (i=0; i < temp.size();i++)
    {
    if(temp[i] ==1)
    {
        row_num = i/R;// pos div total row number.
        col_num = i%C;// pos mod total col number.
        mark_0(temp,row_num,col_num);
        // look for row table
        // mark1(temp,newrow,col_num);
        //look for col table
        //mark1(temp,row_num,newcol);
    }
    
    
}
    
    
    return temp;
}//a transation

bitset<R*C> transation_b(bitset<R*C> b)
{
    temp = b;
    for (i=0; i < temp.size();i++)// go though the matrix
    {
        if(temp[i] ==1)
        {
            row_num = i/R;// pos div total row number.
            col_num = i%C;// pos mod total col number.
            mark_0(temp,row_num,col_num);
            
            // looking for the a table for row.
            //(mark_1(temp,newrow,col_num;);
            
            //looking for table for column
            //mark_1(temp,row_num,newcol).
           
        }
        
    }
    return temp;
}// b transation

bool visited(bitset<R*C> matrx){
    for (i=0; i < history.size();i++)
    {
        if(history[i] == matrx)
        {
            return true;
        }
    }
    
    return false;
}


void start(){
    
    mark_1(temp,0,0);// mark <1,1> as 1.
    targets.push_back(temp); // start transation
    
   }

void test_reachability()
{
    start();
    for (; ;)// generate matrix
    {
        for(i =0; i< targets.size(); i++)// leaf
        {
            //if(!visited (target[i]));
            temp_a = transation_a(targets[i]);
            temp_b = transation_b(targets[i]);
            history.push_back(temp_a);
            history.push_back(temp_b);
            temp_targets.push_back(temp_a);
            temp_targets.push_back(temp_b);

        }
        targets.clear();
        targets = temp_targets;
        temp_targets.clear();// refresh targets list.
        if (targets.size() ==0){break;}
        
    }
}


int main() {
  
    test_reachability();
  
    return 0;
}
