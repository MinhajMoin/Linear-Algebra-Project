#include "Line.h"

Line::Line()
{
}

Line::Line(SDL_Rect* line_fillRect ,int _colors[3],int ID) : Shape(line_fillRect,_colors,ID) //Proper Ctor which makes the line
{
    this->X1 = line_fillRect->x;
    this->Y1 = line_fillRect->y;
    this->X2 = line_fillRect->w;
    this->Y2 = line_fillRect->h;
    this->type = 1; // Type 1 means the shape is a Line
}

void Line::Draw(SDL_Renderer* gRenderer) // for drawing the line
{
    SDL_RenderDrawLine(gRenderer, this->X1, this->Y1, this->X2, this->Y2);
}
