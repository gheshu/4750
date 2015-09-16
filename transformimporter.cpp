#include "transformimporter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "hlm.h"
#include "stdlib.h"

using namespace std;
using namespace hlm;

void transformLoad(const std::string& filename, hlm::mat4& mat){
	ifstream stream(filename);
	if(!stream.is_open()){
		cout << "Cannot open file " << filename << endl;
		return;
	}
	
	string line;
	getline(stream, line);
	if(line.substr(0, 3) == "sca"){
		vec3 v;
		getline(stream, line);
		v.x = atof(line.c_str());
		getline(stream, line);
		v.y = atof(line.c_str());
		getline(stream, line);
		v.z = atof(line.c_str());
		mat = mat * scale(v);
		getline(stream, line);
	}
	else {
		cout << "No scale in " << filename << endl;
	}
	if(line.substr(0, 3) == "rot"){
		vec3 v;
		getline(stream, line);
		v.x = atof(line.c_str());
		getline(stream, line);
		v.y = atof(line.c_str());
		getline(stream, line);
		v.z = atof(line.c_str());
		float angle = max(v.x, max(v.y, v.z));
		mat = mat * rotate(angle, v);
		getline(stream, line);
	}
	else {
		cout << "No rotation in " << filename << endl;
	}
	if(line.substr(0, 3) == "tra"){
		vec3 v;
		getline(stream, line);
		v.x = atof(line.c_str());
		getline(stream, line);
		v.y = atof(line.c_str());
		getline(stream, line);
		v.z = atof(line.c_str());
		mat = mat * translate(v);
		getline(stream, line);
	}
	else {
		cout << "No translation in " << filename << endl;
	}
	stream.close();
}