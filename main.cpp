#include "Misc Functions.cpp" //CPP file containing the initializing functions of SDL
#include <time.h> //for time() function
#include <random> //for rand()
#include <cstdlib> // for srnd()
#include <math.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>




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

    vec3 rotate_(float a, float b, float c)
    {
        return vec3(x * (cos(b)*cos(c)) + y*(sin(a)*sin(b)*cos(c) - cos(a)*sin(c))+z*(cos(a)*sin(b)*cos(c) + sin(a)*sin(c)),
            x*(cos(b)*sin(c))+y*(sin(a)*sin(b)*sin(c)+cos(a)*cos(c)) + z*(cos(a)*sin(b)*sin(c)-sin(a)*cos(c)),
            x * (-sin(b)) + y*(sin(a)*cos(b))+z*(cos(a)*cos(b)));
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
        persp_a = vec2(SCREEN_WIDTH*1.0/2 + scale*a.x+offset_x,SCREEN_HEIGHT/2+scale*a.y+offset_y);
        persp_b = vec2(SCREEN_WIDTH*1.0/2 + scale*b.x+offset_x,SCREEN_HEIGHT/2+scale*b.y+offset_y);
        persp_c = vec2(SCREEN_WIDTH*1.0/2 + scale*c.x+offset_x,SCREEN_HEIGHT/2+scale*c.y+offset_y);

        rotp_x = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_x.x+offset_x,SCREEN_HEIGHT/2+scale*rot_x.y+offset_y);
        rotp_y = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_y.x+offset_x,SCREEN_HEIGHT/2+scale*rot_y.y+offset_y);
        rotp_z = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_z.x+offset_x,SCREEN_HEIGHT/2+scale*rot_z.y+offset_y);
        verts =
        {
            { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_b.x, persp_b.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_c.x, persp_c.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }//,
            // { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, }
        };
    }
    
    void set_offset(int x, int y){
        offset_x = x;
        offset_y = y;
    }
    void fill(){
        SDL_RenderGeometry( gRenderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
    }
    void draw(){
        
        SDL_SetRenderDrawColor(gRenderer, 255, 0,0,255);
        // SDL_SetRenderDrawColor(gRenderer, 255, 255,255,255);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x, persp_a.y);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x, persp_a.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x+1, persp_a.y);
        // SDL_RenderDrawPoint(gRenderer, persp_a.x+1, persp_a.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_a.x, SCREEN_WIDTH),min(persp_a.y, SCREEN_HEIGHT),min(persp_b.x, SCREEN_WIDTH),min(persp_b.y, SCREEN_HEIGHT));
        SDL_SetRenderDrawColor(gRenderer, 0, 255,0,255);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x, persp_b.y);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x, persp_b.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x+1, persp_b.y);
        // SDL_RenderDrawPoint(gRenderer, persp_b.x+1, persp_b.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_b.x, SCREEN_WIDTH),min(persp_b.y, SCREEN_HEIGHT),min(persp_c.x, SCREEN_WIDTH),min(persp_c.y, SCREEN_HEIGHT));
        SDL_SetRenderDrawColor(gRenderer, 0, 0,255,255);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x, persp_c.y);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x, persp_c.y+1);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x+1, persp_c.y);
        // SDL_RenderDrawPoint(gRenderer, persp_c.x+1, persp_c.y+1);
        SDL_RenderDrawLine(gRenderer, min(persp_c.x, SCREEN_WIDTH),min(persp_c.y, SCREEN_HEIGHT),min(persp_a.x, SCREEN_WIDTH),min(persp_a.y, SCREEN_HEIGHT));

        SDL_SetRenderDrawColor(gRenderer, 255, 0,0,255);
        SDL_RenderDrawLine(gRenderer, min(rotp_x.x, SCREEN_WIDTH),min(rotp_x.y, SCREEN_HEIGHT),offset_x+SCREEN_WIDTH/2,offset_y+SCREEN_HEIGHT/2);
        SDL_SetRenderDrawColor(gRenderer, 0, 255,0,255);
        SDL_RenderDrawLine(gRenderer, min(rotp_y.x, SCREEN_WIDTH),min(rotp_y.y, SCREEN_HEIGHT),offset_x+SCREEN_WIDTH/2,offset_y+SCREEN_HEIGHT/2);
        SDL_SetRenderDrawColor(gRenderer, 0, 0,255,255);
        SDL_RenderDrawLine(gRenderer, min(rotp_z.x, SCREEN_WIDTH),min(rotp_z.y, SCREEN_HEIGHT),offset_x+SCREEN_WIDTH/2,offset_y+SCREEN_HEIGHT/2);
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




        rotp_x = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_x.x+offset_x,SCREEN_HEIGHT/2+scale*rot_x.y+offset_y);
        rotp_y = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_y.x+offset_x,SCREEN_HEIGHT/2+scale*rot_y.y+offset_y);
        rotp_z = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_z.x+offset_x,SCREEN_HEIGHT/2+scale*rot_z.y+offset_y);

        persp_a = vec2(SCREEN_WIDTH*1.0/2 + scale*a_r.x+offset_x,SCREEN_HEIGHT/2+scale*a_r.y+offset_y);
        persp_b = vec2(SCREEN_WIDTH*1.0/2 + scale*b_r.x+offset_x,SCREEN_HEIGHT/2+scale*b_r.y+offset_y);
        persp_c = vec2(SCREEN_WIDTH*1.0/2 + scale*c_r.x+offset_x,SCREEN_HEIGHT/2+scale*c_r.y+offset_y);
        verts =
        {
            { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_b.x, persp_b.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ persp_c.x, persp_c.y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }//,
            // { SDL_FPoint{ persp_a.x, persp_a.y }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, }
            
        };
    }
    
    void set_scale(int scale_){
        scale = max(1,scale_);
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

// class obj3d{
// public:

// };

class object3D{
public:
    std::vector<vec3> vectors;
    std::vector<vec2> persp;
    std::vector<std::vector<int>> faces;
    std::vector<int> faceZ;
    std::vector<SDL_Color> faceColors;
    std::vector<std::vector<SDL_Vertex>> verts_sdl;
    int scale = 10;
    int offset_x = 0, offset_y = 0;
    float alpha = 0.0, beta = 0.0, gamma = 0.0;
    float center_offset_x = 0, center_offset_y = 0, center_offset_z = 0;

    object3D(string filename){
        loadOBJ(filename);
        // center_model();
        faceZ.resize(faces.size());
        faceColors.resize(faces.size());
        std::iota(faceZ.begin(), faceZ.end(), 0);


        for (int i = 0; i< faceColors.size(); i++)
        {
            faceColors[i] = {rand() % 256, rand() % 256, rand() % 256,255};
            // faceColors[i] = {95, 200, 128,255};
        }
        calculate_persp();
        printf("vectors:%d persp:%d faces:%d verts_sdl:%d scale:%d offset_x:%d offset_y:%d\ncenter_offset_x:%f center_offset_y:%f center_offset_z:%f\nalpha:%f beta:%f gamma:%f \n", vectors.size(), 
        persp.size(), faces.size(),verts_sdl.size(), scale, offset_x, offset_y, center_offset_x, center_offset_y, center_offset_z, alpha, beta, gamma);
    }

    void rotate(float alpha_, float beta_, float gamma_)
    {
        alpha = alpha_;
        beta = beta_;
        gamma = gamma_;
    }

    void sort_faces()
    {
        vector<float> faceZ_means(faces.size());
        for (int i = 0; i< faces.size(); i++)
        {
            float sumval = 0;
            for (int j = 0; j<faces[i].size(); j++)
            {
                sumval += vectors[faces[i][j]].z;
            }
            faceZ_means[i] = sumval / faces[i].size();
        }

        std::iota(faceZ.begin(), faceZ.end(), 0);

        std::sort(faceZ.begin(), faceZ.end(),
            [&](int A, int B) -> bool {
                return faceZ_means[A] > faceZ_means[B];
        });
    }

    void set_offset(int x, int y)
    {
        offset_x = x;
        offset_y = y;
    }

    void center_model()
    {
        for (int i = 0; i<vectors.size(); i++)
        {
            vectors[i].x -= center_offset_x;
            vectors[i].y -= center_offset_y;
            vectors[i].z -= center_offset_z;
        }
    }

    void calculate_persp()
    {
        for (int i = 0; i<vectors.size(); i++)
        {
            vec3 rot_vector = vectors[i].rotate_(this->alpha, this->beta, this->gamma);
            persp[i] = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_vector.x+offset_x,SCREEN_HEIGHT*1.0/2+scale*rot_vector.y+offset_y);
            // persp[i] = vec2(SCREEN_WIDTH*1.0/2 + scale*vectors[i].x+offset_x,SCREEN_HEIGHT*1.0/2+scale*vectors[i].y+offset_y);
        }

        for (int i = 0; i<faces.size(); i++)
        {
            for (int j = 0; j<faces[i].size(); j++)
            {
                verts_sdl[i][j] = { SDL_FPoint{ persp[faces[i][j]-1].x , persp[faces[i][j]-1].y }, faceColors[i], SDL_FPoint{ 0 }};
            }
            
        }

    }

    void fill(SDL_Renderer* gRenderer)
    {
        // printf("Drawing\n");
        for (int i = 0; i<faces.size(); i++)
        {

            if (faces[i].size() == 3) { SDL_RenderGeometry( gRenderer, nullptr, verts_sdl[faceZ[i]].data(), verts_sdl[faceZ[i]].size(), nullptr, 0 ); }
            else
            {
                
                for (int k = 0; k < faces[i].size()-2; k++)
                {
                    vector<SDL_Vertex> verts_temp = {verts_sdl[faceZ[i]][0],  verts_sdl[faceZ[i]][k+1], verts_sdl[faceZ[i]][k+2]};
                    SDL_RenderGeometry( gRenderer, nullptr, verts_temp.data(), verts_temp.size(), nullptr, 0 ); 
                }
            }
            
        }
        
    }

    void draw(SDL_Renderer* gRenderer)
    {
        for (int i = 0; i<faces.size(); i++)
        {
           for (int j = 0; j<faces[i].size(); j++)
            {
                // printf("i:%d, j:%d %d %d %d %d\t | %d %d | %d %d %d | vector: %f %f %f | vector to: %f %f %f\n", i, j,persp[faces[i][j]-1].x, persp[faces[i][j]-1].y, persp[faces[i][(j+1)%faces[i].size()]-1].x, persp[faces[i][(j+1)%faces[i].size()]-1].y,
                //     faces[i][j], faces[i][(j+1)%faces[i].size()], faces[i].size(), faces.size(), vectors.size(), vectors[faces[i][j]-1].x,vectors[faces[i][j]-1].y,vectors[faces[i][j]-1].z,
                //     vectors[faces[i][(j+1)%faces[i].size()]-1].x,vectors[faces[i][(j+1)%faces[i].size()]-1].y,vectors[faces[i][(j+1)%faces[i].size()]-1].z);
                SDL_SetRenderDrawColor(gRenderer,faceColors[faceZ[i]].r,faceColors[faceZ[i]].g,faceColors[faceZ[i]].b,255);
                SDL_RenderDrawLine(gRenderer, persp[faces[faceZ[i]][j]-1].x,persp[faces[faceZ[i]][j]-1].y,persp[faces[faceZ[i]][(j+1)%faces[i].size()]-1].x,persp[faces[faceZ[i]][(j+1)%faces[i].size()]-1].y);
            }   
        }
    }

     void set_scale(int scale_){
        scale = max(1,scale_);
    }

    bool loadOBJ(string filename)
    {
    string line;
    int v=0;
    int f =0;
    ifstream myfile;
    string temp;
    myfile.open(filename);

    stringstream lineparse;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {

            switch (line[0]){
              case ('v'):
              {
                // printf("%s\n", line.c_str());
                    v++;
                    break;
              }
              case ('f'):
              {
                // printf("%s\n", line.c_str());
                    f++;
                    break;
              }
            }
        }
        myfile.close();
    }
    else {
        printf("%s could not be loaded\n", filename.c_str()); return false;
    }

    printf("Vector Sizes:%d Face Sizes:%d\n", v,f);
    vectors.resize(v);
    persp.resize(v);
    faces.resize(f, vector<int> (3));
    verts_sdl.resize(f, vector<SDL_Vertex> (3));

    myfile.open(filename);

    float max_x;
    float max_y;
    float max_z;
    float min_x;
    float min_y;
    float min_z;
    int v_iter = 0, f_iter=0;

      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
          switch (line[0]){
              case ('v'):
                {
                    std::array<float, 3> v;
                    lineparse << line;
                    lineparse >> temp >> v[0] >> v[1] >> v[2];
                    vectors[v_iter] = vec3(v[0], v[1], v[2]);

                    if (v_iter == 0){
                        max_x = v[0];
                        max_y = v[1];
                        max_z = v[2];
                        min_x = v[0];
                        min_y = v[1];
                        min_z = v[2];
                    }

                    if (v[0] > max_x) max_x = v[0];
                    else if (v[0] < min_x) min_x = v[0];

                    if (v[1] > max_y) max_y = v[1];
                    else if (v[1] < min_y) min_y = v[1];
                    
                    if (v[2] > max_z) max_z = v[2];
                    else if (v[2] < max_z) min_z = v[2];

                    lineparse.str( std::string() );
                    lineparse.clear();
                    // cout << temp << ' ' << vectors[v_iter][0] << ' '<< vectors[v_iter][1] << ' '<< vectors[v_iter][2] << endl;
                    v_iter++;
                    break;
                }
              case ('f'):
                {
                    int spaces = 0;
                    lineparse << line;
                    for (int i = 0; i<line.length(); i++){
                        if (line[i] == ' ') spaces++;
                    }
                    if (spaces > 3) {
                        faces[f_iter].resize(spaces, 0);
                        verts_sdl[f_iter].resize(spaces);
                    }

                    lineparse >> temp;
                    printf(" Spaces: %d\n", spaces);
                    for (int i = 0; i<=spaces; i++)
                    {
                        lineparse >> faces[f_iter][i];
                    }
                    lineparse.str( std::string() );
                    lineparse.clear();
                    f_iter++;
                    break;
                }
        }
        }
        myfile.close();
      }
        center_offset_x = (max_x+min_x)/2;
        center_offset_y = (max_y+min_y)/2;
        center_offset_z = (max_z+min_z)/2;
        return true;
    }




};

int main( int argc, char* args[] )
{
    srand(time(NULL)); // for generating random numbers with rand()
    int scale = 10;
    int m_x=0, m_y = 0;
    bool clicked = false;
    int org_mx = 0, org_my = 0;
    int offset_x = 0, offset_y = 0, old_offx = 0, old_offy = 0;
    

    char filename[25];

    const std::vector< SDL_Vertex > verts =
            {
                { SDL_FPoint{ 400, 100 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
                { SDL_FPoint{ 600, 100 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
                { SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, }
                // { SDL_FPoint{ 400, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, }
            };


    printf("Enter obj file to load\n");
    scanf("%24s", filename);

    //Start up SDL and create window
    init();

    bool quit = false;  //Main loop controller

    SDL_Event e;        //Event handler that takes care of all events
    
    SDL_RenderClear( gRenderer ); //Clear window when the program starts.
    double k = 0.0;
    int alpha=0, beta=0, gamma=0;
    long int frame = 0;

    object3D humanoid(filename);
    humanoid.center_model();
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
                else if (e.wheel.y<0 & scale > 6) scale -= 5;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                clicked = true;
                SDL_GetMouseState( &org_mx, &org_my );
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                clicked = false;
                old_offx = offset_x;
                old_offy = offset_y;
                break;
            }
            case SDL_MOUSEMOTION:
            {
                if (clicked) {
                    SDL_GetMouseState( &m_x, &m_y );
                    offset_x = (int) (old_offx + (-org_mx+m_x));//m_x-SCREEN_WIDTH/2;
                    offset_y = (int) (old_offy + (-org_my+m_y)); //m_y-SCREEN_HEIGHT/2;//
                }
                break;
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
                        offset_x = 0;
                        offset_y = 0;
                        break;
                    default:
                        break;
                }
                break;
            }
            humanoid.rotate(alpha*3.141/180, beta*3.141/180, gamma*3.141/180);
            humanoid.set_scale(scale);
            humanoid.set_offset(offset_x, offset_y);
            humanoid.sort_faces();
            humanoid.calculate_persp();
            // printf("calculate_persp");
        }
            // printf("%d\r", frame);

            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
            SDL_RenderClear( gRenderer );

            


            // Set the color for drawing the lines. White on Black Background
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            
            humanoid.fill(gRenderer);
            humanoid.draw(gRenderer);
            

            // SDL_RenderGeometry( gRenderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
        
            frame++;

            // SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
            // SDL_RenderDrawLine(gRenderer, 0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);
            SDL_RenderPresent(gRenderer);
            // if (frame == 10) break;
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
