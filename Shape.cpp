#include "SDL.h"
#include "Shape.h"

#include <iostream>

Shape::Shape()
{
    //ctor
}

Shape::~Shape()
{
    //dtor
}

void Shape::Draw(SDL_Renderer* gRenderer)
{

}

Shape::Shape(Shape& shape)
{
    this->colors[0] = shape.colors[0];
    this->colors[1] = shape.colors[1];
    this->colors[2] = shape.colors[2];
    this->fillRect = shape.fillRect;
    this->ID = shape.ID;
    this->isdrawn = true;
    this->type = shape.type;
    this->X1 = shape.X1;
    this->X2 = shape.X2;
    this->Y1 = shape.Y1;
    this->Y2 = shape.Y2;
}

Shape::Shape(SDL_Rect* _fillRect,int _colors[3],int id)
{
    this->fillRect = {_fillRect->x,_fillRect->y,_fillRect->w,_fillRect->h};
    this->X1 = _fillRect->x;
    this->Y1 = _fillRect->y;
    this->X2 = _fillRect->w;
    this->Y2 = _fillRect->h;
    this->ID=id;
    this->colors[0] = _colors[0];
    this->colors[1] = _colors[1];
    this->colors[2] = _colors[2];
}
