#include "objimporter.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace hlm;

void objload(const std::string& filename, VertexBuffer& verts){
	ifstream stream(filename);
	if(stream.is_open()){
		string line;
		while(getline(stream, line)){
			if(line.substr(0, 2) == "v "){
				istringstream s(line.substr(2));
				vec4 v;
				s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
				verts.push_back(v);
			}
		}
		stream.close();
	} 
	else {
		printf("Could not find file %s\n", filename.c_str());
	}
}