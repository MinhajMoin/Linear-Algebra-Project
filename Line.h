#ifndef LINE_H
#define LINE_H
#include "Shape.h"
#include "SDL.h"
#include <iostream>

using namespace std;


class Line: public Shape
{
    public:
        Line();
        Line(SDL_Rect*,int[3],int);
        void Draw(SDL_Renderer*);
};

#endif // LINE_H
