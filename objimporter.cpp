#include "objimporter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "hlm.h"
#include "mesh.h"

#include "debugmacro.h"

using namespace std;
using namespace hlm;

bool objload(const std::string& filename, MeshData& out, bool smooth, bool project){
	MeshData temp;
	std::vector<vec2> uvs;
	ifstream stream(filename);
	if(stream.is_open()){
		string line;
		vec3 min, max;
		while(getline(stream, line)){
			if(line.substr(0, 2) == "v "){
				istringstream s(line.substr(2));
				MeshVertex v;
				s >> v.position.x; s >> v.position.y; s >> v.position.z; v.position.w = 1.0f;
				temp.vertices.push_back(v);
				min.x = std::min(min.x, v.position.x);
				max.x = std::max(max.x, v.position.x);
				min.y = std::min(min.y, v.position.y);
				max.y = std::max(max.y, v.position.y);
				min.z = std::min(min.z, v.position.z);
				max.z = std::max(max.z, v.position.z);
			} 
			else if(line.substr(0, 2) == "f "){
				char f[16];
				int i1, i2, i3, ivn1, ivn2, ivn3;
				sscanf(line.c_str(), "%s %i//%i %i//%i %i//%i\n", 
					f, &i1, &ivn1, &i2, &ivn2, &i3, &ivn3);
				//cout << i1 << " " << i2 << " " << i3 << endl;
				temp.indices.push_back(i1 - 1);
				temp.indices.push_back(i2 - 1);
				temp.indices.push_back(i3 - 1);
			}
			else if(!project && line.substr(0, 2) == "vt"){
				istringstream s(line.substr(2));
				for(int i = 0; i < 3; i++){
					vec2 uv;
					s >> uv.x;
					s >> uv.y;
					uvs.push_back(uv);
				}
			}
		}
		stream.close();
		out.vertices.clear();
		out.vertices.reserve(temp.indices.size());
		out.indices.clear();
		for(unsigned i = 0; i < temp.indices.size(); i++){
			MeshVertex& mv = temp.atIndex(i);
			const unsigned index = temp.indices[i];
			if(smooth){
				for(unsigned j = 0; j < temp.indices.size() - 2; j+=3){
					// for each face
					for(unsigned k = 0; k < 3; k++){
						// for each vertex in the face
						if(temp.indices[j + k] == index){
							// if jth face has the ith vertex in it, add jth face normal to ith normal.
							vec4& j1 = temp.atIndex(j).position;
							vec4& j2 = temp.atIndex(j+1).position;
							vec4& j3 = temp.atIndex(j+2).position;
							vec3 jnormal = normalize(cross(vec3(j2 - j1), vec3(j3 - j1)));
							mv.normal += jnormal;
							break;
						}
					}
				}
				mv.normal = normalize(mv.normal);
			}
			else {
				int ind = i - (i%3);
				vec3 e1(temp.atIndex(ind+1).position - temp.atIndex(ind).position);
				vec3 e2(temp.atIndex(ind+2).position - temp.atIndex(ind).position);
				mv.normal = normalize(cross(e1, e2));
			}
			if(project){
				// figure out the polar texture mapping of this vertex.
				const float r = length(mv.position);
				const float theta = acos(mv.position.y / r) / PI;
				const float phi = atan2(mv.position.z, mv.position.x) / (2.0f*PI);
				mv.uv.y = theta;
				mv.uv.x = phi + 0.5f;
			}
			else {
				//mv.uv = uvs[index];	use cube mapping instead of imported uvs
				vec3 absn = abs(mv.normal);
				if(absn.y > absn.z && absn.y > absn.x){
					//use x-z plane
					mv.uv.x = (mv.normal.y < 0.0f) ? -mv.position.x / max.x : mv.position.x / max.x;
					mv.uv.y = mv.position.z / max.z;
				}
				else if(absn.x > absn.z && absn.x > absn.y){
					// use z-y plane
					mv.uv.x = (mv.normal.x < 0.0f) ? -mv.position.z / max.z : mv.position.z / max.z;
					mv.uv.y = mv.position.y / max.y;
				}
				else {
					// use x-y plane
					mv.uv.x = (mv.normal.z < 0.0f) ? mv.position.x / max.x : -mv.position.x / max.x;
					mv.uv.y = mv.position.y / max.y;
				}
			}
			out.vertices.push_back(mv);
		}
		return true;
	} 
	else {
		printf("Could not find file %s\n", filename.c_str());
		return false;
	}
}