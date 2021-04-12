
//These are basic definitions for hospitals

#ifndef hospital_h
#define hospital_h

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "Fibheap.h"
using std::cout;
using std::cin;



class hospital{
public:
    //Remove an index
    void remove(int index);
    //Clear our hospitals
    void clear(void);
    //settle a patient in hospital
    int append(FibNode* value);
    //Retrieve a specific patient
    FibNode* getitem(int index);
    //check if the hospital is full
    bool full();
    //Constructer
    hospital(int a){
        maxsize=1;           //can be adjusted(easy for test)
        location=a;
        reprarray=new FibNode*[maxsize];
        numitems=0;
    }

    //Basic properties
    int location;// 123
    int maxsize;
    int numitems;
    FibNode** reprarray;
};



FibNode* hospital::getitem(int index)
{
	
    if ((index > 0) && (index <= numitems))
    {
    
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
    }
}

int hospital::append(FibNode* value)
{
    if (full()==1){
        return 0;
    }

    reprarray[numitems] = value;
        
    ++numitems;
    return 1;
}

bool hospital::full(void) {
    if (numitems == maxsize)
        return 1;
    else
        return 0;
}


 void hospital::remove(int index)
{
   
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

 void hospital::clear(void) {
     int i;
     while(numitems!=0 ) {
         remove(1);
     }
}



//This function is made to adjust people in Fibonacci Heap
//into hospitals for treatments
//Return true if there are places available
//False if all full
//or that someone with suppose>0 is minimum

//(we can prove that if this happens, people left in the heap are all with suppose larger than 0)
bool arrange(hospital* h1, hospital* h2,hospital* h3,FibHeap* Fibh) {

	FibNode** temp_pt = new FibNode*;
	*temp_pt=Fibh->min;
	
	
     if(*temp_pt==NULL) return 0;
     int a;

     //see which hospital the person belongs to
     if ((Fibh->min)->address == 1) {
         a = h1->full();
         if (a == 0) { 
             if(Fibh->checkMin()==0) return 0;
             
             h1->append(*temp_pt);
             
			 Fibh->removeMin();
			  
             return 1;
             }
         else if (h2->full()==0) {
		 
             if(Fibh->checkMin()==0) {
			 
			 return 0;
			 }
			
             h2->append(*temp_pt);
            Fibh->removeMin();
             
             return 1;
             
        }
         else if (h3->full()==0) {
         
             if(Fibh->checkMin()==0) return 0;
             h3->append(*temp_pt);
           Fibh->removeMin();
             cout<<h3->getitem(1)->name;
             return 1;
        }
         else
         {
             cout << "all hospitals are full, no more can be added"<<endl;
             return 0;
         }
     }
     else if ((Fibh->min)->address == 2) {
         a = h2->full();
         if (a == 0) { 
             if(Fibh->checkMin()==0) return 0;
             h2->append(Fibh->min);
             Fibh->removeMin();
             return 1;
             }
         else if (h3->full()==0) { 
             if(Fibh->checkMin()==0) return 0;
             h3->append(Fibh->min);
             Fibh->removeMin();
             return 1;
        }
         else if (h1->full()==0) {
             if(Fibh->checkMin()==0) return 0;
             h1->append(Fibh->min);
             Fibh->removeMin();
             return 1;
        }
         else
         {
             cout << "all hospitals are full, no more can be added"<<endl;
             return 0;
         }
     }
     else if ((Fibh->min)->address == 3) {
         a = h3->full();
         if (a == 0) { 
             if(Fibh->checkMin()==0) return 0;
             h3->append(Fibh->min);
             Fibh->removeMin();
             return 1;
             }
         else if (h1->full()==0) { 
             if(Fibh->checkMin()==0) return 0;
             h1->append(Fibh->min);
             return 1;
        }
         else if (h2->full()==0) {
             if(Fibh->checkMin()==0) return 0;
             h2->append(Fibh->min);
             return 1;
        }
         else
         {
             cout << "all hospitals are full, no more can be added"<<endl;
             return 0;
         }
     }
 }


#endif
