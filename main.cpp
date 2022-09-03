#include "Misc Functions.cpp" //CPP file containing the initializing functions of SDL
#include <time.h> //for time() function
#include <random> //for rand()
#include <cstdlib> // for srnd()
#include <math.h>
#include <vector>

// #define scale 10
class vec3{
public:
    vec3(float x_,float y_,float z_, float w_=1.0){
        x=x_;
        y=y_;
        z=z_;
    }
    vec3(){}
    float x,y,z;
    void vecprint(){
        printf("%f, %f, %f ", x,y,z);
    }
    void rotate(float a, float b, float c, vec3 v){
        
        // x = 0 + v.x*cos(a)*cos(b)+v.y*(cos(a)*sin(b)*sin(c)-sin(a)*cos(c))+v.z*(cos(a)*sin(b)*cos(c)+sin(a)*sin(c));//*cos(angle) + v.z*sin(angle);
        // y = 0 + v.x*sin(a)*cos(b)+v.y*(sin(a)*sin(b)*sin(c)+cos(a)*cos(c))+v.z*(sin(a)*sin(b)*cos(c)-cos(a)*sin(c));//*cos(angle);
        // z = 0 + v.x*-sin(b)+v.y*(cos(b)*sin(c))+v.z*(cos(b)*cos(c));

        x = v.x * (cos(b)*cos(c)) + v.y*(sin(a)*sin(b)*cos(c) - cos(a)*sin(c))+v.z*(cos(a)*sin(b)*cos(c) + sin(a)*sin(c));
        y = v.x*(cos(b)*sin(c))+v.y*(sin(a)*sin(b)*sin(c)+cos(a)*cos(c)) + v.z*(cos(a)*sin(b)*sin(c)-sin(a)*cos(c));
        z = v.x * (-sin(b)) + v.y*(sin(a)*cos(b))+v.z*(cos(a)*cos(b));
        // printf("rot: %f %f    ",x,z);
    }
};

class vec2{
public:
    vec2(float x_,float y_) {
        x = (int) x_;
        y = (int) y_;
    }
    vec2(){}
    int x,y;
    void vec2print(){
        printf("%d, %d    ", x,y);
    }
};

class face{
public:    
    vec3 a,b,c;
    vec3 a_r,b_r,c_r;
    vec2 persp_a, persp_b, persp_c;
    vec3 rot_x, rot_y, rot_z;
    vec2 rotp_x, rotp_y, rotp_z;
    std::vector< SDL_Vertex > verts;
    int scale = 10;
    int offset_x = 0;
    int offset_y = 0;

    face(vec3 lst[],int x, int y, int z) {
        a = vec3(lst[x-1].x,lst[x-1].y,lst[x-1].z);
        b = vec3(lst[y-1].x,lst[y-1].y, lst[y-1].z);
        c = vec3(lst[z-1].x,lst[z-1].y,lst[z-1].z);

        rot_x = vec3(15,0,0);
        rot_y = vec3(0,15,0);
        rot_z = vec3(0,0,15);

        // persp_a = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(a.z) == 0) ? 0 : (scale * a.x/a.z)), SCREEN_HEIGHT/2 +0+ ((a.z == 0) ? 0 : (scale * a.y/a.z)));
        // persp_b = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(b.z) == 0) ? 0 : (scale * b.x/b.z)), SCREEN_HEIGHT/2 +0+ ((b.z == 0) ? 0 : (scale * b.y/b.z)));
        // persp_c = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(c.z) == 0) ? 0 : (scale * c.x/c.z)), SCREEN_HEIGHT/2 +0+ ((c.z == 0) ? 0 : (scale * c.y/c.z)));
        persp_a = vec2(SCREEN_WIDTH*1.0/2 + scale*a.x,SCREEN_HEIGHT/2+scale*a.y);
        persp_b = vec2(SCREEN_WIDTH*1.0/2 + scale*b.x,SCREEN_HEIGHT/2+scale*b.y);
        persp_c = vec2(SCREEN_WIDTH*1.0/2 + scale*c.x,SCREEN_HEIGHT/2+scale*c.y);

        rotp_x = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_x.x,SCREEN_HEIGHT/2+scale*rot_x.y);
        rotp_y = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_y.x,SCREEN_HEIGHT/2+scale*rot_y.y);
        rotp_z = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_z.x,SCREEN_HEIGHT/2+scale*rot_z.y);
        verts =
        {
            { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_b.x, persp_b.y }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_c.x, persp_c.y }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
        };
    }
    
    void draw(){
        // SDL_RenderGeometry( gRenderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
        // SDL_SetRenderDrawColor(gRenderer, 255, 0,0,255);
        SDL_SetRenderDrawColor(gRenderer, 255, 255,255,255);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x, persp_a.y);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x, persp_a.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x+1, persp_a.y);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x+1, persp_a.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_a.x, SCREEN_WIDTH),min(persp_a.y, SCREEN_HEIGHT),min(persp_b.x, SCREEN_WIDTH),min(persp_b.y, SCREEN_HEIGHT));
        // SDL_SetRenderDrawColor(gRenderer, 0, 255,0,255);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x, persp_b.y);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x, persp_b.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x+1, persp_b.y);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x+1, persp_b.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_b.x, SCREEN_WIDTH),min(persp_b.y, SCREEN_HEIGHT),min(persp_c.x, SCREEN_WIDTH),min(persp_c.y, SCREEN_HEIGHT));
        // SDL_SetRenderDrawColor(gRenderer, 0, 0,255,255);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x, persp_c.y);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x, persp_c.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x+1, persp_c.y);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x+1, persp_c.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_c.x, SCREEN_WIDTH),min(persp_c.y, SCREEN_HEIGHT),min(persp_a.x, SCREEN_WIDTH),min(persp_a.y, SCREEN_HEIGHT));

        SDL_SetRenderDrawColor(gRenderer, 255, 0,0,255);
        SDL_RenderDrawLine(gRenderer, rotp_x.x % SCREEN_WIDTH,rotp_x.y % SCREEN_HEIGHT,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        SDL_SetRenderDrawColor(gRenderer, 0, 255,0,255);
        SDL_RenderDrawLine(gRenderer, rotp_y.x % SCREEN_WIDTH,rotp_y.y % SCREEN_HEIGHT,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        SDL_SetRenderDrawColor(gRenderer, 0, 0,255,255);
        SDL_RenderDrawLine(gRenderer, rotp_z.x % SCREEN_WIDTH,rotp_z.y % SCREEN_HEIGHT,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        // SDL_SetRenderDrawColor(gRenderer, 255, 255,255,255);

        
    }
    void rotate(float ax, float by, float cz){
        a_r.rotate(ax,by,cz,a);
        b_r.rotate(ax,by,cz,b);
        c_r.rotate(ax,by,cz,c);
        rot_x.rotate(ax, by,cz, vec3(15,0,0));
        rot_y.rotate(ax, by,cz, vec3(0,15,0));
        rot_z.rotate(ax, by,cz, vec3(0,0,15));
        // printf("rotated: ");
        // a_r.vecprint();
        // printf("  ");
        // b_r.vecprint();
        // printf("  ");
        // c_r.vecprint();
        // printf("  \n");
        // persp_a = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(a_r.z) == 0) ? 0 : (scale * a_r.x/a_r.z)), SCREEN_HEIGHT/2 +0+ ((a_r.z == 0) ? 0 : (scale * a_r.y/a_r.z)));
        // persp_b = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(b_r.z) == 0) ? 0 : (scale * b_r.x/b_r.z)), SCREEN_HEIGHT/2 +0+ ((b_r.z == 0) ? 0 : (scale * b_r.y/b_r.z)));
        // persp_c = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(c_r.z) == 0) ? 0 : (scale * c_r.x/c_r.z)), SCREEN_HEIGHT/2 +0+ ((c_r.z == 0) ? 0 : (scale * c_r.y/c_r.z)));




        rotp_x = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_x.x,SCREEN_HEIGHT/2+scale*rot_x.y);
        rotp_y = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_y.x,SCREEN_HEIGHT/2+scale*rot_y.y);
        rotp_z = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_z.x,SCREEN_HEIGHT/2+scale*rot_z.y);

        persp_a = vec2(SCREEN_WIDTH*1.0/2 + scale*(a_r.x+offset_x),SCREEN_HEIGHT/2+scale*(a_r.y+offset_y));
        persp_b = vec2(SCREEN_WIDTH*1.0/2 + scale*(b_r.x+offset_x),SCREEN_HEIGHT/2+scale*(b_r.y+offset_y));
        persp_c = vec2(SCREEN_WIDTH*1.0/2 + scale*(c_r.x+offset_x),SCREEN_HEIGHT/2+scale*(c_r.y+offset_y));
        verts =
        {
            { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_b.x, persp_b.y }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_c.x, persp_c.y }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
        };
    }
    
    void set_scale(int scale_){
        scale = scale_;
    }

    void calc_persp(int scale_){
        // persp_a = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(a.z) == 0) ? 0 : (scale * a.x/a.z)), SCREEN_HEIGHT/2 +0+ ((a.z == 0) ? 0 : (scale * a.y/a.z)));
        // persp_b = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(b.z) == 0) ? 0 : (scale * b.x/b.z)), SCREEN_HEIGHT/2 +0+ ((b.z == 0) ? 0 : (scale * b.y/b.z)));
        // persp_c = vec2(SCREEN_WIDTH*1.0/2 +0  + ((round(c.z) == 0) ? 0 : (scale * c.x/c.z)), SCREEN_HEIGHT/2 +0+ ((c.z == 0) ? 0 : (scale * c.y/c.z)));

        scale = scale_;
        persp_a = vec2(SCREEN_WIDTH*1.0/2 + scale*a.x,SCREEN_HEIGHT/2+scale_*a.y);
        persp_b = vec2(SCREEN_WIDTH*1.0/2 + scale*b.x,SCREEN_HEIGHT/2+scale_*b.y);
        persp_c = vec2(SCREEN_WIDTH*1.0/2 + scale*c.x,SCREEN_HEIGHT/2+scale_*c.y);
        verts =
        {
            { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_b.x, persp_b.y }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_c.x, persp_c.y }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
        };
    }

    void printFace(){
        persp_a.vec2print();
        printf("    ");
        persp_b.vec2print();
        printf("    ");
        persp_c.vec2print();
        printf("        ");
        a.vecprint();
        printf("    ");
        b.vecprint();
        printf("    ");
        c.vecprint();
        printf("    \n");
    }

};

int main( int argc, char* args[] )
{
    srand(time(NULL)); // for generating random numbers with rand()
    int faces = 96;
    int vecs = 64;
    int scale = 10;
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

    // vec3 vecList[8] =  {vec3(0.0,0.0,0.0),
    //                     vec3(0.0,0.0,1.0),
    //                     vec3(0.0,1.0,0.0),
    //                     vec3(0.0,1.0,1.0),
    //                     vec3(1.0,0.0,0.0),
    //                     vec3(1.0,0.0,1.0),
    //                     vec3(1.0,1.0,0.0),
    //                     vec3(1.0,1.0,1.0)};


    // vec3 vecList[5] = {vec3(0,0,0), vec3(1,0,0), vec3(1,1,0), vec3(0,1,0), vec3(0.5,0.5,1.6)};
    // vec3 vecList[5] = {vec3(-1,-1,0), vec3(1,-1,0), vec3(1,1,0), vec3(-1,1,0), vec3(0,0,2)};

    
    

    vec3 vecList[64] = {vec3(3.25000, -2.48000, 14.0000, 1.00000),
    vec3(3.25000, -2.48000, 9.01000, 1.00000),
    vec3(3.25000, 2.48000, 9.01000, 1.00000),
    vec3(3.25000, 2.48000, 14.0000, 1.00000),
    vec3(0.773000, -2.48000, 14.0000, 1.00000),
    vec3(0.773000, -2.48000, 9.01000, 1.00000),
    vec3(0.773000, 2.48000, 14.0000, 1.00000),
    vec3(0.773000, 2.48000, 9.01000, 1.00000),
    vec3(3.47000, -1.29000, 17.4000, 1.00000),
    vec3(3.47000, -1.29000, 15.0000, 1.00000),
    vec3(3.47000, 1.19000, 15.0000, 1.00000),
    vec3(3.47000, 1.19000, 17.4000, 1.00000),
    vec3(0.601000, -1.29000, 17.4000, 1.00000),
    vec3(0.601000, -1.29000, 15.0000, 1.00000),
    vec3(0.601000, 1.19000, 17.4000, 1.00000),
    vec3(0.601000, 1.19000, 15.0000, 1.00000),
    vec3(3.15000, -2.47000, 8.01000, 1.00000),
    vec3(3.15000, -2.47000, 3.05000, 1.00000),
    vec3(3.15000, -0.486000, 3.05000, 1.00000),
    vec3(3.15000, -0.486000, 8.01000, 1.00000),
    vec3(0.892000, -2.47000, 8.01000, 1.00000),
    vec3(0.892000, -2.47000, 3.05000, 1.00000),
    vec3(0.892000, -0.486000, 8.01000, 1.00000),
    vec3(0.892000, -0.486000, 3.05000, 1.00000),
    vec3(3.23000, -3.96000, 14.0000, 1.00000),
    vec3(3.23000, -3.96000, 9.01000, 1.00000),
    vec3(3.23000, -2.48000, 9.01000, 1.00000),
    vec3(3.23000, -2.48000, 14.0000, 1.00000),
    vec3(0.747000, -3.96000, 14.0000, 1.00000),
    vec3(0.747000, -3.96000, 9.01000, 1.00000),
    vec3(0.747000, -2.48000, 14.0000, 1.00000),
    vec3(0.747000, -2.48000, 9.01000, 1.00000),
    vec3(3.27000, 2.46000, 14.0000, 1.00000),
    vec3(3.27000, 2.46000, 9.01000, 1.00000),
    vec3(3.27000, 3.95000, 9.01000, 1.00000),
    vec3(3.27000, 3.95000, 14.0000, 1.00000),
    vec3(0.795000, 2.46000, 14.0000, 1.00000),
    vec3(0.795000, 2.46000, 9.01000, 1.00000),
    vec3(0.795000, 3.95000, 14.0000, 1.00000),
    vec3(0.795000, 3.95000, 9.01000, 1.00000),
    vec3(2.49000, -0.498000, 15.0000, 1.00000),
    vec3(2.49000, -0.498000, 14.0000, 1.00000),
    vec3(2.49000, 0.493000, 14.0000, 1.00000),
    vec3(2.49000, 0.493000, 15.0000, 1.00000),
    vec3(1.50000, -0.498000, 15.0000, 1.00000),
    vec3(1.50000, -0.498000, 14.0000, 1.00000),
    vec3(1.50000, 0.493000, 15.0000, 1.00000),
    vec3(1.50000, 0.493000, 14.0000, 1.00000),
    vec3(3.25000, -2.50000, 9.01000, 1.00000),
    vec3(3.25000, -2.50000, 8.01000, 1.00000),
    vec3(3.25000, 2.45000, 8.01000, 1.00000),
    vec3(3.25000, 2.45000, 9.01000, 1.00000),
    vec3(0.771000, -2.50000, 9.01000, 1.00000),
    vec3(0.771000, -2.50000, 8.01000, 1.00000),
    vec3(0.771000, 2.45000, 9.01000, 1.00000),
    vec3(0.771000, 2.45000, 8.01000, 1.00000),
    vec3(3.27000, 0.465000, 8.01000, 1.00000),
    vec3(3.27000, 0.465000, 3.05000, 1.00000),
    vec3(3.27000, 2.45000, 3.05000, 1.00000),
    vec3(3.27000, 2.45000, 8.01000, 1.00000),
    vec3(0.795000, 0.465000, 8.01000, 1.00000),
    vec3(0.795000, 0.465000, 3.05000, 1.00000),
    vec3(0.795000, 2.45000, 8.01000, 1.00000),
    vec3(0.795000, 2.45000, 3.05000, 1.00000)};
    // vec3 vecList[8] =  {vec3(1, 4, -9),
    //                     vec3(1, 4, -10),
    //                     vec3(1, 6, -10),
    //                     vec3(1, 6, -9),
    //                     vec3(-1, 4, -9),
    //                     vec3(-1, 4, -10),
    //                     vec3(-1, 6, -10),
    //                     vec3(-1, 6, -9)};
    // for (int j=0;j<8;j++)
    // {
    //     printf("%d ",j);
    //     vecList[j].vecprint();
    //     printf("\n");
    // }





    float max_x = vecList[0].x;
    float max_y = vecList[0].y;
    float max_z = vecList[0].z;
    float min_x = vecList[0].x;
    float min_y = vecList[0].y;
    float min_z = vecList[0].z;
    for (int i=0; i<vecs; i++)
    {
        if (vecList[i].x > max_x) max_x = vecList[i].x;
        if (vecList[i].y > max_y) max_y = vecList[i].y;
        if (vecList[i].z > max_z) max_z = vecList[i].z;
        
        if (vecList[i].x < min_x) min_x = vecList[i].x;
        if (vecList[i].y < min_y) min_y = vecList[i].y;
        if (vecList[i].z < max_z) min_z = vecList[i].z;
    }
    printf("MAX Coords = %f %f %f , MIN Coords = %f %f %f\n",max_x, max_y, max_z, min_x, min_y, min_z);
    printf("Mid Point Coords = %f %f %f \n",(max_x+min_x)/2, (max_y+min_y)/2, (max_z+min_z)/2);
    for (int i=0; i<vecs; i++)
    {
        
        vecList[i].x -= (max_x+min_x)/2;
        vecList[i].y -= (max_y+min_y)/2;
        vecList[i].z -= (max_z+min_z)/2;
    }

    // face faceList[12] = { face(vecList,1,7,5),  face(vecList,1,3,7),  face(vecList,1,4,3),  face(vecList,1,2,4),  face(vecList,3,8,7),  face(vecList,3,4,8), 
    //  face(vecList,5,7,8),  face(vecList,5,8,6),  face(vecList,1,5,6),  face(vecList,1,6,2),  face(vecList,2,6,8),  face(vecList,2,8,4)};

    // face faceList[6] = {face(vecList, 5, 2, 3), face(vecList, 4, 5, 3), face(vecList, 1, 5, 4), face(vecList, 5, 1, 2), face(vecList, 4, 3, 2), face(vecList, 1, 4, 2)};
    
    face faceList[96] = {face(vecList, 1, 2, 3),
face(vecList, 4, 2, 3),
face(vecList, 5, 6, 2),
face(vecList, 1, 6, 2),
face(vecList, 7, 8, 6),
face(vecList, 5, 8, 6),
face(vecList, 4, 3, 8),
face(vecList, 7, 3, 8),
face(vecList, 7, 5, 1),
face(vecList, 4, 5, 1),
face(vecList, 2, 6, 8),
face(vecList, 3, 6, 8),
face(vecList, 9, 10, 11),
face(vecList, 12, 10, 11),
face(vecList, 13, 14, 10),
face(vecList, 9, 14, 10),
face(vecList, 15, 16, 14),
face(vecList, 13, 16, 14),
face(vecList, 12, 11, 16),
face(vecList, 15, 11, 16),
face(vecList, 15, 13, 9),
face(vecList, 12, 13, 9),
face(vecList, 10, 14, 16),
face(vecList, 11, 14, 16),
face(vecList, 17, 18, 19),
face(vecList, 20, 18, 19),
face(vecList, 21, 22, 18),
face(vecList, 17, 22, 18),
face(vecList, 23, 24, 22),
face(vecList, 21, 24, 22),
face(vecList, 20, 19, 24),
face(vecList, 23, 19, 24),
face(vecList, 23, 21, 17),
face(vecList, 20, 21, 17),
face(vecList, 18, 22, 24),
face(vecList, 19, 22, 24),
face(vecList, 25, 26, 27),
face(vecList, 28, 26, 27),
face(vecList, 29, 30, 26),
face(vecList, 25, 30, 26),
face(vecList, 31, 32, 30),
face(vecList, 29, 32, 30),
face(vecList, 28, 27, 32),
face(vecList, 31, 27, 32),
face(vecList, 31, 29, 25),
face(vecList, 28, 29, 25),
face(vecList, 26, 30, 32),
face(vecList, 27, 30, 32),
face(vecList, 33, 34, 35),
face(vecList, 36, 34, 35),
face(vecList, 37, 38, 34),
face(vecList, 33, 38, 34),
face(vecList, 39, 40, 38),
face(vecList, 37, 40, 38),
face(vecList, 36, 35, 40),
face(vecList, 39, 35, 40),
face(vecList, 39, 37, 33),
face(vecList, 36, 37, 33),
face(vecList, 34, 38, 40),
face(vecList, 35, 38, 40),
face(vecList, 41, 42, 43),
face(vecList, 44, 42, 43),
face(vecList, 45, 46, 42),
face(vecList, 41, 46, 42),
face(vecList, 47, 48, 46),
face(vecList, 45, 48, 46),
face(vecList, 44, 43, 48),
face(vecList, 47, 43, 48),
face(vecList, 47, 45, 41),
face(vecList, 44, 45, 41),
face(vecList, 42, 46, 48),
face(vecList, 43, 46, 48),
face(vecList, 49, 50, 51),
face(vecList, 52, 50, 51),
face(vecList, 53, 54, 50),
face(vecList, 49, 54, 50),
face(vecList, 55, 56, 54),
face(vecList, 53, 56, 54),
face(vecList, 52, 51, 56),
face(vecList, 55, 51, 56),
face(vecList, 55, 53, 49),
face(vecList, 52, 53, 49),
face(vecList, 50, 54, 56),
face(vecList, 51, 54, 56),
face(vecList, 57, 58, 59),
face(vecList, 60, 58, 59),
face(vecList, 61, 62, 58),
face(vecList, 57, 62, 58),
face(vecList, 63, 64, 62),
face(vecList, 61, 64, 62),
face(vecList, 60, 59, 64),
face(vecList, 63, 59, 64),
face(vecList, 63, 61, 57),
face(vecList, 60, 61, 57),
face(vecList, 58, 62, 64),
face(vecList, 62, 64, 59)};

    //  for (int i=0; i<10; i++){
    //             printf("Drawing %d ", i);
    //             faceList[i].printFace();
    // }


    // COPIED FROM LA ASSIGNMENT 2 Q3 BECAUSE I AM TOO DUMB TO COME UP WITH MY OWN COORDINATES
    // float coords [8][3];
    // float perspCoords [8][2];
    // float rotatedCoords [8][3];
    // int ind = 0;
    // int dist = -1;
    // cout << "Original Coordinates" << endl;
    // for (int i = -1; i < 2; i+=2)
    // {
    //     for (int j = 4; j<7; j+=2)
    //     {
    //         for (int k = -10; k < -8; k++)
    //         {
    //             coords[ind][0] = i;
    //             coords[ind][1] = j;
    //             coords[ind][2] = k;
    //             cout << i << ' ' << j << ' ' << k << endl;
    //             ind++;
    //         }
    //     }
    // }

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
    // cout << "Rotated Coordinates " << endl;
    // for (int i = 0; i < 8 ; i++)
    // {
    //     rotatedCoords[i][0] = coords[i][0]*cos(0) + coords[i][2]*sin(0);
    //     rotatedCoords[i][1] = coords[i][1];
    //     rotatedCoords[i][2] = -coords[i][0]*sin(0) + coords[i][2]*cos(0);
    //     cout << rotatedCoords[i][0] << ' ' << rotatedCoords[i][1] << ' ' << rotatedCoords[i][2] << endl;
    // }


    //----------------------------------------------------------------------//
    //                  Perspective Projection Coordinates                  //
    //----------------------------------------------------------------------//
    // cout << "Perspective Projection Coordinates " << endl;
    // for (int i = 0; i < 8 ; i++)
    // {
    //     perspCoords[i][0] = centrex + 20* dist * rotatedCoords[i][0] / rotatedCoords[i][2]; // x' = dx/z
    //     perspCoords[i][1] = centrey/2 + 20*dist * rotatedCoords[i][1] / rotatedCoords[i][2]; // y' = dy/z
    //     cout << '(' << perspCoords[i][0] << ',' << perspCoords[i][1] << ')'<< endl;
    // }
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
    int alpha=0, beta=0, gamma=0;
    long int frame = 0;
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch(e.type){
            //User requests quit
            case SDL_QUIT :
            {
                quit = true;
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                if (e.wheel.y>0) scale += 5;
                else if (e.wheel.y<0) scale -= 5;
            }
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( e.key.keysym.sym ){
                    case SDLK_LEFT:
                        gamma += 1;
                        break;
                    case SDLK_RIGHT:
                        gamma -= 1;
                        break;
                    case SDLK_UP:
                        beta += 1;
                        break;
                    case SDLK_DOWN:
                        beta -= 1;
                        break;
                    case SDLK_PERIOD:
                        alpha -= 1;
                        break;
                    case SDLK_COMMA:
                        alpha += 1;
                        break;
                    case SDLK_r:
                        gamma = 0;
                        alpha = 0;
                        beta  = 0;
                        scale = 10;
                        break;
                    default:
                        break;
                }
                break;
            }
        }
        //Clear screen
    //     for (int i = 0; i < 8 ; i++)
    //     {
    //         rotatedCoords[i][0] = coords[i][0]*cos(0) + coords[i][2]*sin(0);
    //         rotatedCoords[i][1] = coords[i][1] + coords[i][2] * cos(k) + coords[i][1] * cos(k);
    //         rotatedCoords[i][2] = -coords[i][0]*sin(0) + coords[i][2]*cos(0);
    // //        cout << rotatedCoords[i][0] << ' ' << rotatedCoords[i][1] << ' ' << rotatedCoords[i][2] << endl;
    //     }


        //----------------------------------------------------------------------//
        //                  Perspective Projection Coordinates                  //
        //----------------------------------------------------------------------//
    //    cout << "Perspective Projection Coordinates " << endl;
    //     for (int i = 0; i < 8 ; i++)
    //     {
    //         perspCoords[i][0] = centrex + 200* dist * rotatedCoords[i][0] / rotatedCoords[i][2]; // x' = dx/z
    //         perspCoords[i][1] = centrey/2 + 200*dist * rotatedCoords[i][1] / rotatedCoords[i][2]; // y' = dy/z
    // //        cout << '(' << perspCoords[i][0] << ',' << perspCoords[i][1] << ')'<< endl;
    //     }
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
            for (int i=0; i<faces; i++){
                // printf("Drawing %d ", i);
                // faceList[i].rotate(90*3.142/180,k,k*0.5);
                faceList[i].set_scale(scale);
                faceList[i].rotate(alpha*3.142/180,beta*3.142/180,gamma*3.142/180);
                // printf("\n\n");
                // faceList[i].calc_persp();
                faceList[i].draw();
            }

            SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
            SDL_RenderDrawLine(gRenderer, 0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);
            // SDL_RenderDrawLine(gRenderer, perspCoords[0][0],perspCoords[0][1],perspCoords[2][0],perspCoords[2][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[0][0],perspCoords[0][1],perspCoords[4][0],perspCoords[4][1]);

            // SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[4][0],perspCoords[4][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[1][0],perspCoords[1][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[5][0],perspCoords[5][1],perspCoords[7][0],perspCoords[7][1]);

            // SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[2][0],perspCoords[2][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[4][0],perspCoords[4][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[6][0],perspCoords[6][1],perspCoords[7][0],perspCoords[7][1]);

            // SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[7][0],perspCoords[7][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[2][0],perspCoords[2][1]);
            // SDL_RenderDrawLine(gRenderer, perspCoords[3][0],perspCoords[3][1],perspCoords[1][0],perspCoords[1][1]);

            //=============================================================
            SDL_RenderPresent(gRenderer);
            // if (frame % 60 == 0) {
            //     k+= 1*(3.142/180);
            //     // k+= 10;
            //     // for (int l=0; l<12; l++){
            //     // printf("Drawing %d ", l);
            //     // faceList[l].printFace();
            //     // }
            //     // printf("\n\n");
            // }
    }
    close(); // DeAllocation of dynamic arrays and objects and destruction of SDL window
    return 0;
}
