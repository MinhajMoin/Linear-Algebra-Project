#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "node.h"
#include "Shape.h"

class shapelist // The list containing the drawn shapes. Detailed comments in the correspoinding cpp file
{
public:
    shapelist(){start=NULL; size=0;}
    void append(Shape*);
    int  length();
    Shape* pop();
    int getIndex(Shape*);
    Shape* getShapeAt(int);
    void print();
    void DrawAll(SDL_Renderer*);
    void RemoveAt(int);
    void InsertAt(int,Shape*);
    void push_to_back(Shape*);
    void push_to_front(Shape*);
    node* get_node_at(int);

private:
    node* start;
    int     size;
};
#endif // LIST_H_INCLUDED
