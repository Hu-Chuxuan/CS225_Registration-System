//Definition for patients and
//local queues
#ifndef local_h
#define local_h
#include <iostream>
#include <string>
using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>


vector<int> WithDrawals;

class patient{
public:

    //Retrieved from files
    long int birthday;
    long long int contact;
    string name;
	int ID;
	int address;//123
	int profession;
    int age;
    int risk;

    //Updated daily
    double waiting;
    double suppose;

    //used when registered(pop into a hospital)
    int registration;

    void adjust(){
        //Decide on the suppose waiting time
        vector<int>::iterator it;
        it=find(WithDrawals.begin(),WithDrawals.end(),ID);
        if((risk==0 || risk==1) && it!=WithDrawals.end()) suppose=15;
        else if(risk==2) suppose=30;
        else suppose=0;
    }

};
class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
    patient &operator[](int index);
    int getlength(void);
    bool isempty(void);
    patient back(void);
    patient front(void);
    void pushback(patient value);
    patient popfront(void);
    void display(void);
    
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    patient *reprarray;
    void allocate(void);
    void deallocate(void);
};

#endif