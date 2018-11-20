#ifndef SHAPE_H
#define SHAPE_H
#include <SDL.h>

class Shape
{
    public:
        Shape();
        virtual ~Shape();
        virtual void Draw(SDL_Renderer*);
        Shape(SDL_Rect*,int[3],int);
        Shape(Shape&);
        int colors[3];
        int X1=0;
        int Y1=0;
        int X2=0;
        int Y2=0;
        int ID;
        int type;
        SDL_Rect fillRect;
        void Lmao();
        bool isdrawn = true;

    protected:

    private:
};

#endif // SHAPE_H
