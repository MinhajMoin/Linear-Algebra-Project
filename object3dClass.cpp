class object3D{
public:
	std::vector<vec3> vectors;
	std::vector<vec2> persp;
	std::vector<std::vector<int>> faces;
	std::vector<std::vector<SDL_Vertex>> verts_sdl;
	int scale = 10;
    int offset_x = 0, offset_y = 0;
    float alpha = 0.0, beta = 0.0, gamma = 0.0;
    float center_offset_x = 0, center_offset_y = 0, center_offset_z = 0;

    object3D(){
    	loadOBJ(filename);

    	calculate_persp();		
    }

    void rotate(float alpha_, float beta_, float gamma_)
    {
    	alpha = alpha_;
    	beta = beta_;
    	gamma = gamma_;
    }

    void offset(int x, int y)
    {
    	offset_x = x;
    	offset_y = y;
    }

    void calculate_persp()
    {
    	for (int i = 0; i<vectors.size(); i++)
    	{
    		vec3 rot_vector = vectors[i].rotate(alpha, beta, gamma);
    		persp[i] = vec2(SCREEN_WIDTH*1.0/2 + scale*rot_vector.x+offset_x,SCREEN_HEIGHT/2+scale*rot_vector.y+offset_y);
    	}

    	for (int i = 0; i<faces.size(); i++)
    	{
    		for (int j = 0; j<faces[i].size(); j++)
    		{
    			verts_sdl[i][j] = { SDL_FPoint{ persp[faces[i][j]].x , persp[faces[i][j]].y }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }};
    		}
    		
    	}

    }

    void draw(SDL_Renderer* gRenderer)
    {
    	for (int i = 0; i<faces.size(); i++)
    	{
    		for (int j = 0; j<faces[i].size(); j++)
    		{
    			SDL_RenderGeometry( gRenderer, nullptr, verts_sdl[i][j].data(), verts_sdl[i][j].size(), nullptr, 0 );
    		}
    		
    	}
    	
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
		            v++;
		            break;
		      }
		      case ('f'):
		      {
		            f++;
		            break;
		      }
			}
		}
		myfile.close();
	}

	vectors.resize(v);
	faces.resize(f, vector<int> (3));

	myfile.open(filename);

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
	                if (spaces > 3) faces[f_iter].resize(spaces, 0);

	                lineparse >> temp;
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
	}




};