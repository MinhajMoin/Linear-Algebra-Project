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
    int dist = -1;
    cout << "Original Coordinates" << endl;
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

    //==================================================================
    // SACRED CODE AHEAD. DONT TOUCH IT WITHOUT BEGGING FOR FORGIVENESS
    // OF YOUR SINS. PERFORM ABLUTION BEFORE CHANGING ANYTHING.
    //==================================================================
    // rotated coordinates after applying rotation matrix on the y-axis
    // x = x*cos(1) + z*sin(1);
    // y = y;
    // z = -x*sin(1) + z*cos(1);
    //----------------------------------------------------------------------//
    //                          Rotated Coordinates                         //
    //----------------------------------------------------------------------//
    cout << "Rotated Coordinates " << endl;
    for (int i = 0; i < 8 ; i++)
    {
        rotatedCoords[i][0] = coords[i][0]*cos(0) + coords[i][2]*sin(0);
        rotatedCoords[i][1] = coords[i][1];
        rotatedCoords[i][2] = -coords[i][0]*sin(0) + coords[i][2]*cos(0);
        cout << rotatedCoords[i][0] << ' ' << rotatedCoords[i][1] << ' ' << rotatedCoords[i][2] << endl;
    }


    //----------------------------------------------------------------------//
    //                  Perspective Projection Coordinates                  //
    //----------------------------------------------------------------------//
    cout << "Perspective Projection Coordinates " << endl;
    for (int i = 0; i < 8 ; i++)
    {
        perspCoords[i][0] = centrex + 20* dist * rotatedCoords[i][0] / rotatedCoords[i][2]; // x' = dx/z
        perspCoords[i][1] = centrey/2 + 20*dist * rotatedCoords[i][1] / rotatedCoords[i][2]; // y' = dy/z
        cout << '(' << perspCoords[i][0] << ',' << perspCoords[i][1] << ')'<< endl;
    }
    //----------------------------------------------------------------------
    // Now to convert the projected coordinates to something the SDL Window
    // Can Show.

    int xout[4] = {centrex+200, (centrex-200),(centrex+140), (centrex-140)};
    int yout[4] = {centrey+200, (centrey-200),(centrey+140), (centrey-140)};

//    int xout[2] = {centrex+50*perspCoords[0][0], (centrex+50*perspCoords[1][0])};
//    int yout[2] = {centrey+50*perspCoords[0][1], (centrey+50*perspCoords[1][1])};
//    int xin[2] = {centrex+50*perspCoords[2][0], (centrex+50*perspCoords[3][0])};
//    int yin[2] = {centrey+50*perspCoords[3][1], (centrey+50*perspCoords[3][1])};

    SDL_RenderClear( gRenderer ); //Clear window when the program starts.
    double k = 0.0;
    long int frame = 0;
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
        for (int i = 0; i < 8 ; i++)
        {
            rotatedCoords[i][0] = coords[i][0]*cos(0) + coords[i][2]*sin(0);
            rotatedCoords[i][1] = coords[i][1] + coords[i][2] * cos(k) + coords[i][1] * cos(k);
            rotatedCoords[i][2] = -coords[i][0]*sin(0) + coords[i][2]*cos(0);
    //        cout << rotatedCoords[i][0] << ' ' << rotatedCoords[i][1] << ' ' << rotatedCoords[i][2] << endl;
        }


        //----------------------------------------------------------------------//
        //                  Perspective Projection Coordinates                  //
        //----------------------------------------------------------------------//
    //    cout << "Perspective Projection Coordinates " << endl;
        for (int i = 0; i < 8 ; i++)
        {
            perspCoords[i][0] = centrex + 200* dist * rotatedCoords[i][0] / rotatedCoords[i][2]; // x' = dx/z
            perspCoords[i][1] = centrey/2 + 200*dist * rotatedCoords[i][1] / rotatedCoords[i][2]; // y' = dy/z
    //        cout << '(' << perspCoords[i][0] << ',' << perspCoords[i][1] << ')'<< endl;
        }
            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
            SDL_RenderClear( gRenderer );
            // Set the color for drawing the lines. White on Black Background
            SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

    //        SDL_RenderDrawLine(gRenderer, xout[1],yout[1],xout[0],yout[1]);
    //        SDL_RenderDrawLine(gRenderer, xout[1],yout[0],xout[0],yout[0]);
    //        SDL_RenderDrawLine(gRenderer, xout[0],yout[1],xout[0],yout[0]);
    //        SDL_RenderDrawLine(gRenderer, xout[1],yout[1],xout[1],yout[0]);
    //        SDL_RenderDrawLine(gRenderer, xout[2],   yout[2] ,xout[3],yout[2]);
    //        SDL_RenderDrawLine(gRenderer, xout[2],   yout[2] ,xout[2],yout[3]);
    //        SDL_RenderDrawLine(gRenderer, xout[3],   yout[2] ,xout[3],yout[3]);
    //        SDL_RenderDrawLine(gRenderer, xout[3],   yout[3] ,xout[2],yout[3]);
    //        SDL_RenderDrawLine(gRenderer, xout[2], yout[2] ,xout[0],yout[0]);
    //        SDL_RenderDrawLine(gRenderer, xout[3], yout[2] ,xout[1],yout[0]);
    //        SDL_RenderDrawLine(gRenderer, xout[2], yout[3] ,xout[0],yout[1]);
    //        SDL_RenderDrawLine(gRenderer, xout[3], yout[3] ,xout[1],yout[1]);

            frame++;
            SDL_RenderDrawLine(gRenderer, perspCoords[0][0],perspCoords[0][1],perspCoords[1][0],perspCoords[1][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[0][0],perspCoords[0][1],perspCoords[2][0],perspCoords[2][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[0][0],perspCoords[0][1],perspCoords[4][0],perspCoords[4][1]);

            SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[4][0],perspCoords[4][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[1][0],perspCoords[1][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[7][0],perspCoords[7][1]);

            SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[2][0],perspCoords[2][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[4][0],perspCoords[4][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[7][0],perspCoords[7][1]);

            SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[7][0],perspCoords[7][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[2][0],perspCoords[2][1]);
            SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[1][0],perspCoords[1][1]);
            //=============================================================
            SDL_RenderPresent(gRenderer);
            if (frame % 200 == 0) k+= (1/3.142);
    }
    close(); // DeAllocation of dynamic arrays and objects and destruction of SDL window
    return 0;
}
