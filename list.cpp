#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;

void shapelist::append(Shape* val) //append a shape into the list
{
    if (start==NULL)
    {
        node* p = new node;
        if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}
        p->val = val;
        start = p;
        size++;
    }
    else{
        //go to list's end
        node* s = start;
        while (s->next) s=s->next;

        node* p = new node;
        if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}
        p->val = val;
        s->next = p;
        size++;
    }
}


int shapelist::length() //return the length of the list
{
    return size;
}

Shape* shapelist::pop() //remove the last shape from the list and return it
{
    Shape* shape = new Shape(*(getShapeAt(length()-1)));
    RemoveAt(length()-1);
    if (length()>0)
    {
        get_node_at(length()-1)->next = NULL;
    }
    return shape;
}



int shapelist::getIndex(Shape* val) //return the index of the given shape
{

    int index = -1;
    node *tmp = start;
    while(tmp){
        index++;
        if(tmp->val->ID ==val->ID)
            break;
        tmp = tmp->next;
    }

    if(tmp) return index;
    else    return -1;
}

Shape* shapelist::getShapeAt(int index) //return the shape pointer at the given index
{

    node *s = start;
    for (int i=0; i<index; i++)
        {s= s->next;}
    return s->val;
}

node* shapelist::get_node_at(int index){ //return the node at given index

    node *s = start;
    for (int i=0; i<index; i++)
        {s= s->next;}
    return s;
}

void shapelist::RemoveAt(int ind) //remove shape pointer at given index
{
        if(ind<0 || ind>=size)
            cerr<<"Invalid index passed  to remove_at()"<<endl;

    node *behind = start;
    if(ind==0)
    {
        start = start->next;
        delete behind;
    }
    else
    {
        //now go to the appropriate location
        node* ahead  = behind->next;
        for (int i=1; i<ind; i++)
        {
            behind = ahead;
            ahead  = ahead->next;
        }
        behind->next = ahead->next;
        delete ahead;
    }
    size--;
}


void shapelist::InsertAt(int ind, Shape* val) //iinsert a shape* at given index
{
//    if(ind<0 || ind>=size)
//        cerr<<"Invalid index passed  to insert()"<<endl<<ind;


    node* p = new node;
    if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}
    p->val = val;


    //By definition if we reach here, start!=NULL

    if(start->next==NULL)
    {
        node* tmp = start;
        start = p;
        start->next = tmp;
    }
    else{
        //now go to the appropriate location
        node* behind = start;
        node* ahead  = start->next;
        for (int i=1; i<ind; i++){
            behind = ahead;
            ahead  = ahead->next;
        }
        behind->next = p;
        p->next = ahead;
    }
    size++;
}


void shapelist::push_to_back(Shape* pushed) //move the shape backwards
{
    int index = getIndex(pushed);

    RemoveAt(index);
    InsertAt(index-1,pushed);
}

void shapelist::push_to_front(Shape* pushed) //move the shape forward
{
    int index = getIndex(pushed);

    RemoveAt(index);
    InsertAt(index+1,pushed);
}
