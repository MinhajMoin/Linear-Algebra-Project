#include"Rect.h"
#include <iostream>
using namespace std;

Rect::Rect(SDL_Rect* rect,int _colors[3],int ID):Shape(rect,_colors,ID) //Constructor
{
    this->type = 0;
}


/** Draws the rectangle **/
void Rect::Draw(SDL_Renderer* gRenderer) // Draw Function. Uses the colors in the shape object to fill the rectangle
{
    SDL_SetRenderDrawColor( gRenderer, colors[0],colors[1],colors[2], 255 );
    SDL_RenderFillRect(gRenderer,&(Shape::fillRect));
    SDL_SetRenderDrawColor( gRenderer, 0,0,0, 255 );
    SDL_RenderDrawRect(gRenderer,&(Shape::fillRect));
}

