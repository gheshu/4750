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
		for(unsigned i = 0; i < out.indices.size(); i++){
			vec3& v = out.at(i).color;
			switch(i%3){
				case 0:
					v = vec3(255.0f, 0.0f, 0.0f);
					break;
				case 1:
					v = vec3(0.0f, 255.0f, 0.0f);
					break;
				case 2:
					v = vec3(0.0f, 0.0f, 255.0f);
					break;
				default:
					break;
			}
		}
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
		for(unsigned i = 0; i < temp.indices.size(); i++){
			MeshVertex& mv = temp.atIndex(i);
			switch(i%3){
				case 0:
					mv.color = vec3(255.0f, 0.0f, 0.0f);
					break;
				case 1:
					mv.color = vec3(0.0f, 255.0f, 0.0f);
					break;
				case 2:
					mv.color = vec3(0.0f, 0.0f, 255.0f);
					break;
				default:
					break;
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