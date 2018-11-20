#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include "Shape.h"

struct node {
    Shape* val;
    node* next;
    node()
    {
        val=NULL;
        next=NULL;
    }
};


#endif // NODE_H_INCLUDED
