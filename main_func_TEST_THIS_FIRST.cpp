/*
This is the group work from GROUP 27
We basically build a registration system here that completes arrangements within a month(or more)
*/

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
// #include<io.h>
#include "local_queue.h"
#include "report_w.h"
#include "time.h"
using namespace std;

void report_m(int a,int b,int c,int d,int e,int f){
	cout<<"the number of people who have registered is "<<a<<endl;
	cout<<"the number of people who are waiting is "<<b<<endl;
	cout<<"the number of people waiting in total is "<<c<<endl;
	cout<<"the number of treatment appointments is "<<d<<endl;
	cout<<"the waiting time is "<<e<<endl;
	cout<<"the number of people withdraw is "<<f<<endl;
}



	
int main(){ 

	//We first ask the user to type in the date
	//so that we can generate appropriate time stamps
	cout << "Please enter the date(Eg:20201010)";
    long int stamp;
    cin >> stamp;
	FibHeap Fib;             //the Fib we use

	AList<FibNode*> List1;   //Fib
	AList<FibNode*> List2;   //treat
	AList<FibNode*> List3;   //registered
    

	//Counting Parameters for monthly reports
	int countR=0;           
    int countWing=0; 
    int countWtt=0;
    int countAPP=0;
    int countWT=0;
    int countWD=0;
	
	
/*

Count for a Month

ATTENTION:
If you do not want wait for too long for a monthly/weekly report,
feel free to adjust the parameter i below

Or if you want to make it longer, you can simply adjust it

Note: you should also adjust the report part if you aim at seeing the reports

*/

for(double i=0;i<30;i+=0.5){

	//Tell user which day it is
	cout<<"This is date "<< stamp <<endl;
	cout<<"We have gone through "<< i << " days" <<endl;

	//Ask for withdrawals
	cout<<"Any Withdrawals?yes(y)no(n)\n";
	char ans='n';
    cin>>ans;
	while(ans=='y'){
		int identity;
	    cout<<"Who?(type his ID)\n";
	    cin>>identity;
		//This function deals with withdrawals
		Fib.withdraw(identity);
		countWD++;
		cout<<"Anyone Else?yes(y)no(n)\n";
		cin>>ans;
	}

	/*
	Stage0: Updates of FibHeap
	In this function, we update waiting time and the suppose waiting time
	And also with Deadlines(please refer to Fibheap.h for details)
	*/
	Fib.daily(Fib.min);

	/*
	Stage1: Get Information from files and user inputs
	*/
    //Store user inputs in the files
	int cnt=0;
	vector<fifo> v;
	for(int i=0;i<5;i++){
		fifo q=fifo(20);
		v.push_back(q);
	}
	
	int ID;
	
	
	//hospital1.txt
	ofstream oFile;

  int a,b,c,d,e;
   long int birth,contact;

   oFile.open("./data1/queue_for_Hospital1.txt",ios::out|ios::trunc);
   cout<<"queue_for_Hospital1"<<endl;
   while(1){
		char flg;
        cout<<"do you wanna add patient?yes(y)no(n)"<<endl;
        cin>>flg;
        if(flg=='n'){ break;}
		string n;
        cout<<"patient's name"<<endl;
        
        cin>>n;
        cout<<"ID"<<endl;
        cin>>a;
        cout<<"profession"<<endl;
        cin>>c;
        cout<<"age"<<endl; 
        cin>>d;
        cout<<"risk"<<endl; 
        cin>>e;
		cout<<"birthday"<<endl; 
	    cin>>birth;
	    cout<<"contact"<<endl; 
	    cin>>contact;
	    oFile<<">>"<<endl;
   oFile<<n<<endl;
   oFile<<a<<endl;
   oFile<<c<<endl;
   oFile<<d<<endl;
   oFile<<e<<endl;
        
   }oFile.close();
   
   //hospital2.txt
    cout<<"queue_for_Hospital2"<<endl;

   oFile.open("./data1/queue_for_Hospital2.txt",ios::out|ios::trunc);
   while(1){
		char flg;
        cout<<"do you wanna add patient?yes(y)no(n)"<<endl;
        cin>>flg;
        if(flg=='n'){ break;}
		string n;
        cout<<"patient's name"<<endl;
        cin>>n;
        cout<<"ID"<<endl;
        cin>>a;
        cout<<"profession"<<endl;
        cin>>c;
        cout<<"age"<<endl; 
        cin>>d;
        cout<<"risk"<<endl; 
        cin>>e;
		cout<<"birthday"<<endl; 
	    cin>>birth;
	    cout<<"contact"<<endl; 
	    cin>>contact;
	    oFile<<">>"<<endl;
   oFile<<n<<endl;
   oFile<<a<<endl;
   oFile<<c<<endl;
   oFile<<d<<endl;
   oFile<<e<<endl;
        
   }oFile.close();
   
 //hospital3.txt  
  cout<<"queue_for_Hospital3"<<endl;

   oFile.open("./data1/queue_for_Hospital3.txt",ios::out|ios::trunc);
   while(1){
		char flg;
        cout<<"do you wanna add patient?yes(y)no(n)"<<endl;
        cin>>flg;
        if(flg=='n'){ break;}
		string n;
        cout<<"patient's name"<<endl;
        cin>>n;
        cout<<"ID"<<endl;
        cin>>a;
        cout<<"profession"<<endl;
        cin>>c;
        cout<<"age"<<endl; 
        cin>>d;
        cout<<"risk"<<endl; 
        cin>>e;
		cout<<"birthday"<<endl; 
	    cin>>birth;
	    cout<<"contact"<<endl; 
	    cin>>contact;
	    oFile<<">>"<<endl;
   oFile<<n<<endl;
   oFile<<a<<endl;
   oFile<<c<<endl;
   oFile<<d<<endl;
   oFile<<e<<endl;
        
   }oFile.close();
   
ifstream f1("./data1/queue_for_Hospital1.txt", ios::in);

	string value;
	while(1){
        getline(f1,value);
	    
		if(value[0]=='>'){
			patient buf;
			buf.address=cnt+1;
			getline(f1,value);
			buf.name=value;//cout<<"name"<<buf.name<<endl;
			getline(f1,value);
			buf.ID=atoi(value.c_str());
			getline(f1,value);
			buf.profession=atoi(value.c_str())%8;
			getline(f1,value);
			buf.age=atoi(value.c_str())%7;
			getline(f1,value);
			buf.risk=atoi(value.c_str())%4;
            buf.adjust();
            
		    v[cnt].pushback(buf);
        }
		else{
			break;
		}}cnt++;	

ifstream f2("./data1/queue_for_Hospital2.txt", ios::in);

	while(1){
        getline(f2,value);
	    
		if(value[0]=='>'){
			patient buf;
			buf.address=cnt+1;
			getline(f2,value);
			buf.name=value;//cout<<"name"<<buf.name<<endl;
			getline(f2,value);
			buf.ID=atoi(value.c_str());
			getline(f2,value);
			buf.profession=atoi(value.c_str())%8;
			getline(f2,value);
			buf.age=atoi(value.c_str())%7;
			getline(f2,value);
			buf.risk=atoi(value.c_str())%4;
            buf.adjust();
            
		    v[cnt].pushback(buf);
        }
		else{
			break;
		}}cnt++;
ifstream f3("./data1/queue_for_Hospital3.txt", ios::in);
//	if(!f.is_open()){
//		return 0;
//	}
	//string value;
	while(1){
        getline(f3,value);
	    //cout<<cnt<<"="<<value[0]<<endl;
		if(value[0]=='>'){
			patient buf;
			buf.address=cnt+1;
			getline(f3,value);
			buf.name=value;//cout<<"name"<<buf.name<<endl;
			getline(f3,value);
			buf.ID=atoi(value.c_str());
			getline(f3,value);
			buf.profession=atoi(value.c_str())%8;
			getline(f3,value);
			buf.age=atoi(value.c_str())%7;
			getline(f3,value);
			buf.risk=atoi(value.c_str())%4;
            buf.adjust();
            
		    v[cnt].pushback(buf);
        }
		else{
			break;
		}}cnt++;
	/*
	Stage2: pop from queues
	*/
    //We put the information from local queues into our FibHeap
    for(int u=0;u<cnt;u++){
		fifo tmp=v[u];
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
			f->timestamp=stamp;
			Fib.insert(f);
			
		}
	}
      
	/*
	Stage3: pop into hospitals
	*/
    bool flgg=1;
	//We made three hospitals by default
    hospital h1(1);
    hospital h2(2);
    hospital h3(3);
	while(flgg){
		flgg=arrange(&h1,&h2,&h3,&Fib);
	}
    
	//This calculates how many days
	int j=(int)i+1;

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



	//This is for Monthly Reports
	for(int i=0;i<h1.numitems;i++){//count waiting time
		countWT+=(int)h1.getitem(i+1)->waiting;
	}for(int i=0;i<h2.numitems;i++){//count waiting time
		countWT+=(int)h2.getitem(i+1)->waiting;
	}for(int i=0;i<h3.numitems;i++){//count waiting time
		countWT+=(int)h3.getitem(i+1)->waiting;
	}
	countR+=h1.numitems;//count registered people
	countR+=h2.numitems;
	countR+=h3.numitems;
	countWing=h1.numitems;//count waiting people
	countWing+=h2.numitems;
	countWing+=h3.numitems;
	countWtt=countWing;//count people waiting in total
	countWtt+=Fib.keyNum;
	
	
	/*
	ATTENTION:
	Feel free to adjust the modulo here,
	if you want to see the monthly reports sooner
	*/
	if(j%30==0){
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
		
	/*
	Stage5: clear hospitals
	*/
    /*
	ATTENTION:
	We made it by default that treatments are done within one day,
	feel free to add the if conditions below if you want to make treatments longer
	*/
    // if(j%2==0){
    h1.clear();
	h2.clear();
	h3.clear();
	// }

	//This function updates our time stamp at end of day
	//Please refer to time.h for detail
	stamp=date(stamp);


}
    cout<<"This Completes a Month"<<endl;
	cout<<"Thanks For Using our Program"<<endl;
    return 0;
}
