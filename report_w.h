//These are functions for weekly reports

#include<iostream>
#include"alist_func.h"
#include "hospital.h"
#include "Fibheap.h"
//#include <typeinfo.h>

/*
For display
*/
void reportweekly_Fib(FibHeap& Fib,AList<FibNode*>& List){
	cout<<"These people are still queueing:"<<endl;
	for(int i=1;i<=List.numitems;i++){
		cout << List.getitem(i)->name << " , his profession is " <<List.getitem(i)->profession << " , his age is " << List.getitem(i)->age << "  , his risk status is " << List.getitem(i)->risk << endl;
		cout<< "he registered on date "<<List.getitem(i)->timestamp<<endl;
		cout << "his waiting time is " << (int)List.getitem(i)->waiting<< " days" << endl;
	}
	while(List.numitems!=0) List.remove(1);
}


void reportweekly_Treat(FibHeap& Fib,AList<FibNode*>& List){
	cout<<"These people are treated:"<<endl;
	for(int i=1;i<=List.numitems;i++){
		cout << List.getitem(i)->name << " , his profession is " <<List.getitem(i)->profession << " , his age is " << List.getitem(i)->age << "  , his risk status is " << List.getitem(i)->risk << endl;
		cout<< "he registered on date "<<List.getitem(i)->timestamp<<endl;
		cout << "his waiting time is " << (int)List.getitem(i)->waiting<< " days" << endl;
	}
	while(List.numitems!=0) List.remove(1);
}

void reportweekly_Registered(FibHeap& Fib,AList<FibNode*>& List){
	cout<<"These people are registered:"<<endl;
	for(int i=1;i<=List.numitems;i++){
		cout << List.getitem(i)->name << " , his profession is " <<List.getitem(i)->profession << " , his age is " << List.getitem(i)->age << "  , his risk status is " << List.getitem(i)->risk << endl;
		cout<< "he registered on date "<<List.getitem(i)->timestamp<<endl;
		cout << "his waiting time is " << (int)List.getitem(i)->waiting<< " days" << endl;
	}
	while(List.numitems!=0) List.remove(1);
}


//For Updating Everyday
void reportdaily_Treat(AList<FibNode*>& List2,int j,hospital& h1, hospital& h2, hospital& h3){
	if(j%7!=0){  //this person is not treated on that day
	for(int i=1;i<=h1.numitems;i++){
		List2.append(h1.getitem(i));
	}
	for(int i=1;i<=h2.numitems;i++){
		List2.append(h2.getitem(i));
	}
	for(int i=1;i<=h3.numitems;i++){
		List2.append(h3.getitem(i));
	}
	}
}
void reportdaily_Registered(AList<FibNode*>& List2,hospital& h1, hospital& h2, hospital& h3){
	for(int i=1;i<=h1.numitems;i++){
		List2.append(h1.getitem(i));
	}
	for(int i=1;i<=h2.numitems;i++){
		List2.append(h2.getitem(i));
	}
	for(int i=1;i<=h3.numitems;i++){
		List2.append(h3.getitem(i));
	}
}
