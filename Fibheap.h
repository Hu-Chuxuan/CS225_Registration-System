

/*
Fibonacci Heap:
This is the Fibonacci Heap class and its function we implemented
for our centralized queue
*/
#ifndef Fibheap_h
#define Fibheap_h
#include<cmath>
#include<algorithm>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
//#include<io.h>
#include "patient.h"
#include <math.h>
#include "alist_func.h"
using namespace std;


 
class FibNode : public patient {
      public:
        int key;          // priority
        int degree;          
        FibNode *left;    
        FibNode *right;    
        FibNode *child;    // first child node
        FibNode *parent;    
        bool marked;  

        int priority();   //for calculating priority key
        long int timestamp; //timestamp for each person
  
        //Constructer
        FibNode() {
            degree = 0;
            marked = false;
            left   = this;
            right  = this;
            parent = NULL;
            child  = NULL;
         }
};

//For calculating priority
int FibNode::priority(){

    //Start from 0 each time
    int ret=0;

    //Those of high risks will never be treated unless there are no people waiting
    if(risk==3) ret+=100000;

    //Those with suppose greater than 0 will never be popped before those can be popped immediately
    //and it will also be judeged, if larger than 0, no pops
    if(suppose>0){
        ret+=1000;
    }

    //priority calculations within order
    ret+=waiting+age*10+profession*100;
    return ret;
} 


//Centralized queue
class FibHeap {
    public:
        int keyNum;         //Node numbers
        int maxDegree;      
        FibNode *min;    
        FibNode **cons;    //for consolidates

        /*
        When waiting time exceeds this, pop out unconditionally
        Can be adjusted by requirements
        */
        int Deadline;
 
        FibHeap();
        ~FibHeap();

        //get the minimum pointer
        FibNode* getmin();

         //For Updates everyday
        void daily(FibNode* root); 

        //For Withdrawals
        void withdraw(int ID);
 
         // For adding to centralized
        void insert(FibNode *node); 
        void insert2(FibNode* node);
        void addNode(FibNode *node, FibNode *root);

        //for reports
        void traverse(AList<FibNode*>& List, FibNode* root);

        // For popping the minimum into hospitals
        void removeMin();
        bool checkMin();
        void removeNode(FibNode *node);
        FibNode* extractMin();
        void consolidate();
        void link(FibNode* node, FibNode* root);
        void makeCons();

        //For updates
        void update(int identity, int newval,int item);
        void decrease(FibNode *node, int newkey,int item);
        void increase(FibNode *node, int newkey,int item);   
        void update(FibNode *node, int newkey,int item);   
        FibNode* search(FibNode *root, int identity);
        FibNode* search(int identity);

        //Helper functions
        bool contains(int identity);
        void cut(FibNode *node, FibNode *parent);
        void cascadingCut(FibNode *node);
        void renewDegree(FibNode *parent, int degree);
};

void FibHeap:: traverse(AList<FibNode*>& List, FibNode* root){
    if(root==NULL) return;

    List.append(root);

    FibNode* t=root;
    do
    {
        traverse(List,t->child); 
        t = t->right;
     } while (t != root);
}

//Constructor
FibHeap::FibHeap()
{
     keyNum = 0;
     maxDegree = 0;
     min = NULL;
     cons = NULL;

     //can be adjusted
     Deadline=5;
}


FibHeap::~FibHeap() 
{
}

//From Locals to Centralized
void FibHeap::addNode(FibNode *node, FibNode *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

void FibHeap::insert(FibNode *node)
{
    //If the person to be inserted if already in FibHeap
    //We ask if the user want to update this person's information
    if(contains(node->ID)){
        char flg;
        cout<<"This person is already there!\n";
        cout<<"Do you want to update his information?y(yes)n(no)\n";
        cin>>flg;
        if(flg=='n') return;
        cout<<"Which item you want to update his information?profession(0)risk(1)\n";
        int choice;
        cin>>choice;
        cout<<"To what?\n";
        int newkey;
        cin>>newkey;
        update(node,newkey,choice);
        return;
    }
     if (keyNum == 0) min = node;
     else{
         addNode(node, min);
         if (node->key < min->key)
             min = node;
        }
     keyNum++;
}


//From Centralized to Hospitals
void FibHeap::removeNode(FibNode *node)
{
     node->left->right = node->right;
     node->right->left = node->left;
}

bool FibHeap::checkMin()
{
	FibNode* m = min;
	if (min==NULL){
         return 0;
     }

if(m->suppose>0) return 0;
return 1;
}

void FibHeap::removeMin()
{
     if (min==NULL){
         return;
     }
 
    FibNode* child=NULL;
    FibNode* m = min;

    while (m->child != NULL)
    {
         child = m->child;
         removeNode(child);
         if (child->right == child)
             m->child = NULL;
         else
             m->child = child->right;
 
         addNode(child, min);
         child->parent = NULL;
    } 

    removeNode(m);

    if(m->right == m) {
         min = NULL;
    }
    else{
         min = m->right;
         consolidate();
    }

    keyNum--;
  
}

void FibHeap::link(FibNode* node, FibNode* root)
{
     removeNode(node);
     if (root->child == NULL)
         root->child = node;
     else
         addNode(node, root->child); 
     node->parent = root;
     root->degree++;
     node->marked = false;
}
  
//make rooms for consolidates
void FibHeap::makeCons()
{
     int old = maxDegree;
 

     maxDegree = (log(keyNum)/log(2.0)) + 1;
     if (old >= maxDegree)
         return ;

     cons = (FibNode **)realloc(cons, sizeof(FibHeap*) * (maxDegree + 1));
}
void FibHeap::consolidate()
{
     int i;
     int d;
     int D;
     FibNode* x;
     FibNode* y;
     FibNode* tmp;
 
     makeCons();
     D = maxDegree + 1;
 
     for (i = 0; i < D; i++)
         cons[i] = NULL;
  
 
     while (min != NULL){
        x = extractMin();              
        d = x->degree;              
        while (cons[d] != NULL){
            y = cons[d];           
            if (x->key > y->key){        
                 swap(x, y);
            }
            link(y, x);
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    
    min = NULL;
  
    for(i=0; i<D; i++)
     {
         if (cons[i] != NULL)
         {
             if (min == NULL)
                 min = cons[i];
             else
             {
                 addNode(cons[i], min);
                 if ((cons[i])->key < min->key)
                     min = cons[i];
             }
         }
     }
 }


//Updates

FibNode* FibHeap::search(FibNode *root, int identity)
{
    FibNode *t = root;
    FibNode *p = NULL;
    if (root==NULL)
         return root;
    do
    {
         if (t->ID == identity)
         {
             p = t;
             break;
         } 
         else
         {
             if ((p = search(t->child, identity)) != NULL) 
                 break;
         }    
         t = t->right;
     } while (t != root);
     return p;
}

FibNode* FibHeap::search(int identity)
{
     if (min==NULL)
         return NULL;
 
     return search(min, identity);
}
bool FibHeap::contains(int identity)
{
     return search(identity)!=NULL ? true: false;
}

void FibHeap::decrease(FibNode *node, int newkey,int item){
    //item 0 means we do PROFESSION adjustments
    FibNode* parent; 
    if (min==NULL ||node==NULL) return ;

    if(item==0) node->profession = newkey;
    else{
        node->risk=newkey;
        if(node->risk==0 || node->risk==1) node->suppose=0;
        else if(node->risk==2) node->suppose=30;
    }

    node->key=node->priority();
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    if (node->key < min->key) min = node;
    return;
}
void FibHeap::cut(FibNode *node, FibNode *parent)
{
     removeNode(node);
     renewDegree(parent, node->degree);

     if (node == node->right) 
         parent->child = NULL;
     else 
         parent->child = node->right;
 
     node->parent = NULL;
     node->left = node->right = node;
     node->marked = false;

     addNode(node, min);
}

void FibHeap::cascadingCut(FibNode *node) 
{
     FibNode *parent = node->parent;
     if (parent != NULL)
     {
         if (node->marked == false) 
             node->marked = true;
         else
         {
             cut(node, parent);
             cascadingCut(parent);
         }
     }
}

void FibHeap::renewDegree(FibNode *parent, int degree)
{
     parent->degree -= degree;
     if (parent-> parent != NULL)
         renewDegree(parent->parent, degree);
}

void FibHeap::increase(FibNode *node, int newkey, int item)
{
     FibNode *child, *parent, *right;
 
     if (min==NULL ||node==NULL) 
         return ; 


     while (node->child != NULL)
     {
         child = node->child;
         removeNode(child);               
         if (child->right == child)
             node->child = NULL;
         else
             node->child = child->right;
 
         addNode(child, min);     
         child->parent = NULL;
     }
    node->degree = 0;
    if(item==0) node->profession = newkey;
    else{
        node->risk=newkey;
        if(node->risk==0 || node->risk==1) node->suppose=0;
        else if(node->risk==2) node->suppose=30;
    }
    node->key=node->priority();

    parent = node->parent;
    if(parent != NULL)
    {
         cut(node, parent);
         cascadingCut(parent);
    }
     else if(min == node)
     {
         right = node->right;
         while(right != node)
         {
             if(node->key > right->key)
                 min = right;
             right = right->right;
         }
     }
}


void FibHeap::update(FibNode *node, int newkey,int item){
    if(item==0 && newkey < node->profession)
         decrease(node, newkey,item);
    else if(item==0 && newkey > node->profession)
         increase(node, newkey,item);
    else if(item==1&&newkey > node->risk)
        increase(node, newkey,item);   
    else
        decrease(node,newkey,item);
}  

void FibHeap::update(int identity, int newval,int item)
{
     FibNode *node;
 
     node = search(identity);
     if (node!=NULL)
         update(node, newval,item);
}


void FibHeap::withdraw(int identity){
    FibNode* removal=search(identity);
    if(removal==NULL){
        return;
    }
    WithDrawals.push_back(identity);
    removal->left->right = removal->right;
    removal->right->left = removal->left;
    keyNum--;
}


//Daily Updates
void FibHeap::daily(FibNode* root){
    if(root==NULL) return;

    root->suppose-=0.5;
    root->waiting+=0.5;
    if(root->waiting>=Deadline){
        root->key=0;
    }else{
        root->key=root->priority();
    }

    FibNode* t=root;
    do
    {
        daily(t->child); 
        t = t->right;
     } while (t != root);

}

FibNode* FibHeap::extractMin()
{
     FibNode *p = min;
 
     if (p == p->right)
         min = NULL;
     else
     {
         removeNode(p);
         min = p->right;
     }
     p->left = p->right = p;
 
     return p;
}


FibNode* FibHeap:: getmin(){
    return min;
};

void FibHeap::insert2(FibNode *node)
{

    if(contains(node->ID)){
        char flg;
        cout<<"This person is already there! we update it\n";
        
        update(node,node->profession,0);
        update(node,node->risk,1);
        return;
    }
     if (keyNum == 0) min = node;
     else{
         addNode(node, min);
        
         if (node->key < min->key)
             min = node;
        }
     keyNum++;
}


#endif


