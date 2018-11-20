#pragma once
#include"SDL.h"
#include <iostream>
#include "Shape.h"

/** Rect class **/

class Rect:public Shape //Detailed comments in the correspoding cpp file
{
public:
    Rect(SDL_Rect*,int[3],int);
    Rect(){}
    void Draw(SDL_Renderer*);
};

