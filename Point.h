#pragma once
#include "Shape.h"
#include <SDL.h>

struct Point : public Shape
{
    int x;
    int y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(SDL_Rect* fillRect,int colors[3],int ID):Shape(fillRect,colors,ID)
    {
        this->x = fillRect->x;
        this->y = fillRect->y;
        this->type = 2;
    }

    void Draw(SDL_Renderer* gRenderer)
    {
        SDL_RenderDrawPoint(gRenderer,x,y);
    }

    Point(const Point& point)
    {
        x = point.x;
        y = point.y;
    }

};
