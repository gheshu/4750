#include "objimporter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "hlm.h"

using namespace std;
using namespace hlm;

void objload(const std::string& filename, VertexBuffer& verts){
	ifstream stream(filename);
	if(stream.is_open()){
		string line;
		VertexBuffer temp_verts;
		IndexBuffer indices;
		while(getline(stream, line)){
			if(line.substr(0, 2) == "v "){
				istringstream s(line.substr(2));
				vec4 v;
				s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
				temp_verts.push_back(v);
			} 
			else if(line.substr(0, 2) == "f "){
				char f[16];
				int i1, i2, i3, ivn1, ivn2, ivn3;
				sscanf(line.c_str(), "%s %i//%i %i//%i %i//%i\n", 
					f, &i1, &ivn1, &i2, &ivn2, &i3, &ivn3);
				//cout << i1 << " " << i2 << " " << i3 << endl;
				indices.push_back(i1 - 1);
				indices.push_back(i2 - 1);
				indices.push_back(i3 - 1);
			}
		}
		stream.close();
		for(unsigned i = 0; i < indices.size(); i++){
			verts.push_back(temp_verts[indices[i]]);
		}
	} 
	else {
		printf("Could not find file %s\n", filename.c_str());
	}
}