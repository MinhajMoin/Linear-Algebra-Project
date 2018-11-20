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

    Uint8 r,g,b; // for the colors of the shapes
    shapelist* poppedshapes = new shapelist; // the list storing popped shapes when the undo button is pressed

    //Start up SDL and create window
    if(!init())
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {

        if( !loadMedia() )  //Load media
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;  //Main loop controller

            SDL_Event e;        //Event handler that takes care of all events

            bool mouseClicked = false;
            SDL_Rect fillRect; //Object containing the co ordinates of the shapes
            int oldx = 0;
            int oldy = 0;

            int centrex= SCREEN_WIDTH/2;
            int centrey = SCREEN_HEIGHT/2;

            Shape* studShape = new Shape(); // Due to some complications, I had to put an empty shape as the 0th element of the linked list
            Shape* shape = NULL; // declaration of the shape pointer containing the rectangle, line or point information

            //----------------------------------------------------------
            int colors[3] = {0,0,0};
            ShapeList->append(studShape); // append the empty shape into the list
            SDL_Rect liner = {centrex-100,centrey-100 ,centrex,centrey-100};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);


            colors[1] = 255;
            liner = {centrex-100,centrey ,centrex,centrey};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);

            colors[1] = 120;
            colors[2] = 255;
            liner = {centrex,centrey-100 ,centrex,centrey};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);

            colors[0] = 250;

            liner = {centrex-100,centrey-100 ,centrex-100,centrey};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);

            //------------------------------------------------------


            colors[0] = 0; colors[1] = 0;
            ShapeList->append(studShape); // append the empty shape into the list
            liner = {centrex-50,centrey-50 ,centrex-50,centrey-50};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);


            colors[1] = 255;
            liner = {centrex-50,centrey ,centrex-50,centrey-50};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);

            colors[1] = 120;
            colors[2] = 255;
            liner = {centrex,centrey-50 ,centrex-50,centrey-50};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);

            colors[0] = 250;

            liner = {centrex-50,centrey-50 ,centrex-50,centrey=50};
            shape = new Line(&liner,colors,ID);
            ShapeList->append(shape);
            //---------------------------------------------------


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
                    //User Inputs from the KeyBoard
                    if (e.type == SDL_KEYDOWN)
                    {
                        switch( e.key.keysym.sym )
                        {
                        case (SDLK_u): //Clear Screen when user presses U. all lists will be emptied. extra functionality
                            delete ShapeList;
                            ShapeList = new shapelist;
                            ShapeList->append(new Shape());
                            delete poppedshapes;
                            delete shape;
                            poppedshapes = new shapelist;
                            shape = NULL;
                            cout << "SCREEN CLEARED" << endl;
                            break;
                        case (SDLK_DOWN): //User wants to move the latest shape down
                            cout << "DOWN BUTTON" << endl;
                            if (shape!=NULL && ShapeList->length()>2)
                            {
                                ShapeList->push_to_back(shape);
                            }
                            break;
                        case (SDLK_UP): //User wants to move the latest shape up
                            cout << "UP BUTTON" << endl;
                            if(shape!=NULL && ShapeList->getIndex(shape)<ShapeList->length()-1 && ShapeList->getIndex(shape)>0)
                            {
                                ShapeList->push_to_front(shape);
                            }
                            break;

                        case (SDLK_q)://User wants to undo something. Assigned to Q as an extra functionality
                            cout << "UNDO BUTTON PRESSED" << endl;
                            if (ShapeList->length()-1>0)
                            {
                                Shape* pop = ShapeList->pop();
                                poppedshapes->append(pop);

                            }
                            break;

                        case (SDLK_e): //User wants to redo something he did in the past.Assigned to E as an extra functionality
                            cout << "REDO BUTTON PRESSED" << endl;
                            if (poppedshapes->length()>0)
                            {
                                Shape* pop = poppedshapes->pop();
                                Shape* redoshape = NULL;
                                if (pop->type == LINE)
                                {
                                    redoshape = new Line(&pop->fillRect,pop->colors,pop->ID);
                                }
                                ShapeList->append(redoshape);
                            }
                            break;
                        }
                    }

                    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                    {
                        //Get mouse position
                        int x, y;
                        SDL_GetMouseState( &x, &y );

                        if(e.type ==  SDL_MOUSEMOTION)
                        {
                            if(mouseClicked == true) //change the fillRect when click-dragging the mouse
                            {
                                fillRect = { oldx, oldy, x - oldx, y - oldy };
                            }
                        }

                        if(e.type == SDL_MOUSEBUTTONDOWN) // change the click position of the mouse
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                if(mouseClicked == false)
                                {
                                    mouseClicked = true;
                                    oldx = x;
                                    oldy = y;
                                }
                            }
                            if (e.button.button == SDL_BUTTON_RIGHT) // Undo Button
                            {
                                cout << "UNDO BUTTON PRESSED" << endl;
                                if (ShapeList->length()-1>0)
                                {
                                    Shape* pop = ShapeList->pop();
                                    poppedshapes->append(pop);
                                }
                            }
                            if (e.button.button == SDL_BUTTON_MIDDLE) // Redo Button. rebuild the shapes from the poppedshapes list
                            {
                                cout << "REDO BUTTON PRESSED" << endl;
                                if (poppedshapes->length()>0)
                                {
                                    Shape* pop = poppedshapes->pop();
                                    Shape* redoshape = NULL;
                                    if (pop->type == LINE)
                                    {
                                        redoshape = new Line(&pop->fillRect,pop->colors,pop->ID);
                                    }
                                    ShapeList->append(redoshape);
                                }
                            }
                        }

                        if(e.type == SDL_MOUSEBUTTONUP) //When user finishes clicking the mouse button
                        {
                            mouseClicked = false;
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                //Make a new shape according to the set mode and append into the list
                                r = rand()%256;
                                g = rand()%256;
                                b = rand()%256;
                                int colors[3] = {r,g,b};

                                delete poppedshapes;
                                poppedshapes = new shapelist;
                                SDL_Rect liner = {oldx,oldy,x,y};
                                shape = new Line(&liner,colors,ID);
                                ShapeList->append(shape);
                                ID++; //ID uniquely identifies a shape according to a 'serial' number
                            }

                        }

                    }
                }
                //Clear screen

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x0FF, 255 );
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
        }
    }
    close(); // DeAllocation of dynamic arrays and objects and destruction of SDL window
    delete ShapeList;
    delete poppedshapes;
    return 0;
}
