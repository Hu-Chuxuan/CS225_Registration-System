
#include<time.h>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include<io.h>
#include "local_queue.h"
#include "report_w.h"
using namespace std;

void report_m(int a,int b,int c,int d,int e,int f){
	cout<<"this is monthly report"<<endl;
	cout<<"the number of people who have registered is "<<a<<endl;
	cout<<"the number of people who are waiting is "<<b<<endl;
	cout<<"the number of people waiting in total is "<<c<<endl;
	cout<<"the number of treatment appointments is "<<d<<endl;
	cout<<"the waiting time is "<<e<<endl;
	cout<<"the number of people withdraw is "<<f<<endl;
}


//When waiting time exceeds this, pop out unconditionally
int Deadline=5; 

	
int main(){ 
vector<int>stid(30);
srand((int)time(0));
int countimes;	
int prof;
	int rsk;
	int age;
	int id;
	string name;
	FibHeap Fib;

	AList<FibNode*> List1;
	AList<FibNode*> List2;
	AList<FibNode*> List3;

	int countR=0;////////
    int countWing=0; 
    int countWtt=0;
    int countAPP=0;
    double countWT=0;
    int countWD=0;
	vector<int>numWD(20);
	numWD.clear();
	

for(double i=0;i<10;i+=0.5){
	cout<<endl;
	cout<<"This is day "<<i<<"\n";
	string enter;
	cout<<"type 'c'to continue"<<endl;
	cin>>enter;

	/*
	Stage0: Updates of FibHeap
	*/
	Fib.daily(Fib.min);

	/*
	Stage1: Get Information from files and user inputs
	*/
	int cnt=0;
	vector<fifo> v;
	for(int i=0;i<5;i++){
		fifo q=fifo(20);
		v.push_back(q);
	}
	
	int ID;
	struct _finddata_t fileinfo;
    string in_path = ".\\data1";
	string in_name;
	string curr = in_path + "\\*.txt";
	long handle;
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L)
	{
		cout << "No File!" << endl;
		return 0;
	}
	else
	{
		do{ 
		in_name = in_path + "\\" + fileinfo.name;
		FILE* f;
	 
   f = fopen (in_name.c_str(), "w+");
  
		prof=1+(int)(8.0 * rand()/(RAND_MAX+1.0));
		rsk=(int)(4.0 * rand()/(RAND_MAX+1.0));
		id=1+(int)(20.0 * rand()/(RAND_MAX+1.0));
		age=(int)(7.0 * rand()/(RAND_MAX+1.0));
		name.erase();
	for (int q=0;q<3;q++)
	if (rand()&0x1)
	name+=char( rand()%26+'a');
	else
	name+=char( rand()%10+'0');
	
        fprintf(f, ">>\n%s\n%d\n%d\n%d\n%d\n", name.c_str(),id,prof,age,rsk);
   
   fclose(f);
   f = fopen (in_name.c_str(), "a+");
   countimes=(int)(5.0 * rand()/(RAND_MAX+1.0));
	for(int i=0;i<countimes;i++){
		prof=1+(int)(8.0 * rand()/(RAND_MAX+1.0));
		rsk=(int)(4.0 * rand()/(RAND_MAX+1.0));
		id=1+(int)(20.0 * rand()/(RAND_MAX+1.0));
		stid.push_back(id);
		age=(int)(7.0 * rand()/(RAND_MAX+1.0));
		name.erase();
	for (int q=0;q<3;q++)
	if (rand()&0x1)
	name+=char( rand()%26+'a');
	else
	name+=char( rand()%10+'0');
	
        fprintf(f, ">>\n%s\n%d\n%d\n%d\n%d\n", name.c_str(),id,prof,age,rsk);
   }
   fclose(f);
   }while (!(_findnext(handle, &fileinfo)));
		_findclose(handle);
}
	
	//struct _finddata_t fileinfo;
	 in_path = ".\\data1";
	//string in_name;
	 curr = in_path + "\\*.txt";
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L)
	{
		cout << "No File!" << endl;
		return 0;
	}
	else
	{
		do{
		in_name = in_path + "\\" + fileinfo.name;
		ifstream f;
		f.open(in_name,ios::in);
	if(!f.is_open()){
		return 0;
	}
	string value;
	while(1){
        getline(f,value);
		if(value[0]=='>'){
			patient buf;
			buf.address=cnt+1;
			getline(f,value);
			buf.name=value;
			getline(f,value);
			buf.ID=atoi(value.c_str());
			getline(f,value);
			buf.profession=atoi(value.c_str());
			getline(f,value);
			buf.age=atoi(value.c_str());
			getline(f,value);
			buf.risk=atoi(value.c_str());
            buf.adjust();
            
		    v[cnt].pushback(buf);
        }
		else{
			break;
		}}cnt++;	
		}while (!(_findnext(handle, &fileinfo)));
		_findclose(handle);
	}


	/*
	Stage2: pop from queues
	*/
    for(int i=0;i<cnt;i++){
		fifo tmp=v[i];
		while(!tmp.isempty()){

			patient t=tmp.popfront();
			FibNode* f=new FibNode;
			f->name=t.name;
			f->ID=t.ID;
			f->address=t.address;
			f->age=t.age;
			f->profession=t.profession;
			f->risk=t.risk;
			f->suppose=t.suppose;
			f->waiting=t.waiting;
			f->key=f->priority();
			Fib.insert2(f);
		}
	}
      
	/*
	Stage3: pop into hospitals
	*/
    bool flg=1;
    hospital h1(1);
    hospital h2(2);
    hospital h3(3);
	while(flg){
		flg=arrange(&h1,&h2,&h3,&Fib);
	}
	
	/*
	Stage4: Reports
	*/	
int j;
j=int(i)+1;
//To guarantee reports work well every week, we have to do these everyday:
	reportdaily_Treat(List2,j,h1,h2,h3);
	reportdaily_Registered(List3,h1,h2,h3);

	//Weekly Reports
	/*
	ATTENTION:
	We made by default that weekly reports generate every seven days
	If you want to see it earlier, feel free to adjust the 7 here
	(Note:if you adjusted, you should also adjust it in report_w.h)
	*/
	if(j%7==0){
		Fib.traverse(List1,Fib.min);
		reportweekly_Fib(Fib,List1);
		reportweekly_Treat(Fib,List2);
		reportweekly_Registered(Fib,List3);
	}
	countR+=h1.numitems;//count registered people
	countR+=h2.numitems;
	countR+=h3.numitems;
	countWing=h1.numitems;//count waiting people
	countWing+=h2.numitems;
	countWing+=h3.numitems;
	countWtt=countWing;//count people waiting in total
	countWtt+=Fib.keyNum;
	


	if(j%30==0&&j!=0){
		if(countR==0){
			countWT=0;
		}
		else{countWT=countWT/countR;}
		countAPP=countR-countWing;
		report_m(countR,countWing,countWtt,countAPP,countWT,countWD);
		countR=0;
		countWing=0;
		countWtt=0;
		countWT=0;
		countWD=0;
		
	}
	
	printf("there are %d people in hospital 1\n",h1.numitems);
	printf("There are %d people queueing\n",Fib.keyNum);


    

	/*
	Stage5: clear hospitals
	*/
    h1.clear();
	h2.clear();
	h3.clear();


	
}
    return 0;
}
