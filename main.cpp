/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include "Misc Functions.cpp" //CPP file containing the initializing functions of SDL
#include <time.h> //for time() function
#include <random> //for rand()
#include <cstdlib> // for srnd()
#include "Line.h"

int ID=0; // ID of the shape. Difference bw this and the index is that the ID is assigned to the shape and will never change.
int mode=1;
enum {RECT,LINE,POINT}; // enum for setting the mode flag to rectangle, point or line

int main( int argc, char* args[] )
{
    srand(time(NULL)); // for generating random numbers with rand()

//    Uint8 r,g,b; // for the colors of the shapes
//    shapelist* poppedshapes = new shapelist; // the list storing popped shapes when the undo button is pressed

    //Start up SDL and create window
    init();

    bool quit = false;  //Main loop controller

    SDL_Event e;        //Event handler that takes care of all events

    int centrex= SCREEN_WIDTH/2;
    int centrey = SCREEN_HEIGHT/2;

    Shape* studShape = new Shape(); // Due to some complications, I had to put an empty shape as the 0th element of the linked list
    Shape* shape = NULL; // declaration of the shape pointer containing the rectangle, line or point information
    ShapeList->append(studShape); // append the empty shape into the list
    //----------------------------------------------------------

    int xout[2] = {centrex+200, (centrex-200)};
    int yout[2] = {centrey+200, (centrey-200)};
    int xin[2] = {centrex+140, (centrex-140)};
    int yin[2] = {centrey+140, (centrey-140)};

    int colors[3] = {250,250,250};
    SDL_Rect liner = {xout[1],yout[1],xout[0],yout[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xout[1],yout[0],xout[0],yout[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xout[0],yout[1],xout[0],yout[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);


    liner = {xout[1],yout[1],xout[1],yout[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    //------------------------------------------------------

    ShapeList->append(studShape); // append the empty shape into the list
    liner = {xin[0],yin[0] ,xin[1],yin[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[0],yin[0] ,xin[0],yin[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[1],yin[0] ,xin[1],yin[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[1],yin[1] ,xin[0],yin[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);
    //---------------------------------------------------

    ShapeList->append(studShape); // append the empty shape into the list
    liner = {xin[0],yin[0] ,xout[0],yout[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[1],yin[0] ,xout[1],yout[0]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[0],yin[1] ,xout[0],yout[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);

    liner = {xin[1],yin[1] ,xout[1],yout[1]};
    shape = new Line(&liner,colors,ID);
    ShapeList->append(shape);
    //-----------------------------------------------

    SDL_RenderClear( gRenderer ); //Clear window when the program starts.

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                delete shape; // Delete the dynamically allocated memory when quitting. the deallocation has to be done here because the pointer goes out of scope outside the loop
                quit = true;
            }

        }
        //Clear screen

        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );

        if (shape != NULL) // Iterate thru the list and draw all objects in the list
        {
            for (int i=1; i<ShapeList->length(); i++)
            {
                SDL_SetRenderDrawColor( gRenderer, ShapeList->getShapeAt(i)->colors[0],
                                        ShapeList->getShapeAt(i)->colors[1],ShapeList->getShapeAt(i)->colors[2], 0x00 );
                ShapeList->getShapeAt(i)->Draw(gRenderer);
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    close(); // DeAllocation of dynamic arrays and objects and destruction of SDL window
    delete ShapeList;
    return 0;
}
