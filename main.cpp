/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include "Misc Functions.cpp" //CPP file containing the initializing functions of SDL
#include <time.h> //for time() function
#include <random> //for rand()
#include <cstdlib> // for srnd()
#include <math.h>

int main( int argc, char* args[] )
{
    srand(time(NULL)); // for generating random numbers with rand()

    //Start up SDL and create window
    init();

    bool quit = false;  //Main loop controller

    SDL_Event e;        //Event handler that takes care of all events

    int centrex = SCREEN_WIDTH/2;
    int centrey = SCREEN_HEIGHT/2;
    //----------------------------------------------------------
//    A = (1, 4, -9),
//    B = (1, 4, -10),
//    C = (1, 6, -10),
//    D = (1, 6, -9),
//    E = (-1, 4, -9),
//    F = (-1, 4, -10),
//    G = (-1, 6, -10),
//    H = (-1, 6, -9);
    // COPIED FROM LA ASSIGNMENT 2 Q3 BECAUSE I AM TOO DUMB TO COME UP WITH MY OWN COORDINATES
    float coords [8][3];
    float perspCoords [8][2];
    float rotatedCoords [8][3];
    int ind = 0;
    int dist = -3;
    for (int i = -1; i < 2; i+=2)
    {
        for (int j = 4; j<7; j+=2)
        {
            for (int k = -10; k < -8; k++)
            {
                coords[ind][0] = i;
                coords[ind][1] = j;
                coords[ind][2] = k;
                cout << i << ' ' << j << ' ' << k << endl;
                ind++;
            }
        }
    }


    // rotated coordinates after applying rotation matrix on the y-axis
    // x = x*cos(1) + z*sin(1);
    // y = y;
    // z = -x*sin(1) + z*cos(1);
    for (int i = 0; i < 8 ; i++)
    {
        rotatedCoords[i][0] = coords[i][0]*cos(1) + coords[i][2]*sin(1);
        rotatedCoords[i][1] = coords[i][1];
        rotatedCoords[i][2] = -coords[i][0]*sin(1) + coords[i][2]*cos(1);
        cout << "Rotated " << i << ' ' <<  rotatedCoords[i][0] << ' ' << rotatedCoords[i][1] << ' ' << rotatedCoords[i][2] << endl;
    }


    //----------------------------------------------------------------------//
    //                  Perspective Projection Coordinates                  //
    //----------------------------------------------------------------------//
    for (int i = 0; i < 8 ; i++)
    {
        perspCoords[i][0] = dist * rotatedCoords[i][0] / rotatedCoords[i][2]; // x' = dx/z
        perspCoords[i][1] = dist * rotatedCoords[i][1] / rotatedCoords[i][2]; // y' = dy/z
        cout << perspCoords[i][0] << ' ' << perspCoords[i][1] << endl;
    }
    //----------------------------------------------------------------------


    int xout[2] = {centrex+200, (centrex-200)};
    int yout[2] = {centrey+200, (centrey-200)};
    int xin[2] = {centrex+140, (centrex-140)};
    int yin[2] = {centrey+140, (centrey-140)};

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
                quit = true;
            }
        }
        //Clear screen

        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );
        // Set the color for drawing the lines. White on Black Background
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
        //=============================================================
        // SACRED CODE. DON'T TOUCH IT WITHOUT BEGGING FOR FORGIVENESS
        // OF YOUR SINS. PERFORM ABLUTION BEFORE CHANGING ANYTHING.
        //=============================================================
        SDL_RenderDrawLine(gRenderer, xout[1],yout[1],xout[0],yout[1]);
        SDL_RenderDrawLine(gRenderer, xout[1],yout[0],xout[0],yout[0]);
        SDL_RenderDrawLine(gRenderer, xout[0],yout[1],xout[0],yout[0]);
        SDL_RenderDrawLine(gRenderer, xout[1],yout[1],xout[1],yout[0]);
        SDL_RenderDrawLine(gRenderer, xin[0],   yin[0] ,xin[1],yin[0]);
        SDL_RenderDrawLine(gRenderer, xin[0],   yin[0] ,xin[0],yin[1]);
        SDL_RenderDrawLine(gRenderer, xin[1],   yin[0] ,xin[1],yin[1]);
        SDL_RenderDrawLine(gRenderer, xin[1],   yin[1] ,xin[0],yin[1]);
        SDL_RenderDrawLine(gRenderer, xin[0], yin[0] ,xout[0],yout[0]);
        SDL_RenderDrawLine(gRenderer, xin[1], yin[0] ,xout[1],yout[0]);
        SDL_RenderDrawLine(gRenderer, xin[0], yin[1] ,xout[0],yout[1]);
        SDL_RenderDrawLine(gRenderer, xin[1], yin[1] ,xout[1],yout[1]);
        //=============================================================
        SDL_RenderPresent(gRenderer);
    }
    close(); // DeAllocation of dynamic arrays and objects and destruction of SDL window
    return 0;
}
