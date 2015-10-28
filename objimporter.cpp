#include "objimporter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "hlm.h"
#include "mesh.h"

using namespace std;
using namespace hlm;

bool objload(const std::string& filename, Mesh& out){
	ifstream count_stream(filename);
	unsigned vcount = 0;
	unsigned icount = 0;
	if(count_stream.is_open()){
		// count number of verts and indices in file to make a well sized buffer to load into.
		string line;
		while(getline(count_stream, line)){
			if(line.substr(0, 2) == "v "){
				vcount++;
			}
			else if(line.substr(0, 2) == "f "){
				icount++;
			}
		}
		count_stream.close();
	}
	ifstream stream(filename);
	if(stream.is_open()){
		out.vertices.clear();
		out.vertices.reserve(vcount);
		out.indices.clear();
		out.indices.reserve(icount);
		string line;
		while(getline(stream, line)){
			if(line.substr(0, 2) == "v "){
				istringstream s(line.substr(2));
				MeshVertex v;
				s >> v.position.x; s >> v.position.y; s >> v.position.z; v.position.w = 1.0f;
				out.vertices.push_back(v);
			} 
			else if(line.substr(0, 2) == "f "){
				char f[16];
				int i1, i2, i3, ivn1, ivn2, ivn3;
				sscanf(line.c_str(), "%s %i//%i %i//%i %i//%i\n", 
					f, &i1, &ivn1, &i2, &ivn2, &i3, &ivn3);
				//cout << i1 << " " << i2 << " " << i3 << endl;
				out.indices.push_back(i1 - 1);
				out.indices.push_back(i2 - 1);
				out.indices.push_back(i3 - 1);
			}
		}
		stream.close();
		return true;
	} 
	else {
		printf("Could not find file %s\n", filename.c_str());
		return false;
	}
}

bool objloadNoIndices(const std::string& filename, Mesh& out){
	Mesh temp;
	ifstream stream(filename);
	if(stream.is_open()){
		string line;
		while(getline(stream, line)){
			if(line.substr(0, 2) == "v "){
				istringstream s(line.substr(2));
				MeshVertex v;
				s >> v.position.x; s >> v.position.y; s >> v.position.z; v.position.w = 1.0f;
				temp.vertices.push_back(v);
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
		}
		stream.close();
		out.vertices.clear();
		out.vertices.reserve(temp.indices.size());
		out.indices.clear();
		std::vector<int> neighbors;
		for(unsigned i = 0; i < temp.indices.size(); i++){
			MeshVertex& mv = temp.atIndex(i);
			for(unsigned j = 0; j < temp.indices.size() - 2; j+=3){
				// for each face
				for(unsigned k = 0; k < 3; k++){
					// for each vertex in the face
					if(temp.indices[j + k] == temp.indices[i]){
						// if one of the indices in the face
						// matches the current index it is a neighbor.
						// insert j representing the face index and break from face loop
						neighbors.push_back(j);
						break;
					}
				}
			}
			for(int j : neighbors){
				vec4& j1 = temp.atIndex(j).position;
				vec4& j2 = temp.atIndex(j+1).position;
				vec4& j3 = temp.atIndex(j+2).position;
				vec3 jnormal = cross(vec3(j2 - j1), vec3(j3 - j1));
				mv.normal += jnormal;
			}
			mv.normal = normalize(mv.normal);
			out.vertices.push_back(mv);
			neighbors.clear();
		}

		return true;
	} 
	else {
		printf("Could not find file %s\n", filename.c_str());
		return false;
	}
}