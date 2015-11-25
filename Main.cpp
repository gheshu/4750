#include "renderer.h"
#include <iostream>

#include <fstream>

using namespace std;

void fillvec3(ifstream& stream, hlm::vec3& out){
	string line;
	getline(stream, line);
	out.x = stof(line);
	getline(stream, line);
	out.y = stof(line);
	getline(stream, line);
	out.z = stof(line);
}

void doTRS(const string& file, BoshartParam& param){
	ifstream trs(file);
	if(trs.is_open()){
		string line;
		while(getline(trs, line)){
			if(line.substr(0, 3) == "sca"){
				fillvec3(trs, param.s);
			}
			else if(line.substr(0, 3) == "rot"){
				fillvec3(trs, param.r);
			}
			else if(line.substr(0, 3) == "tra"){
				fillvec3(trs, param.t);
			}
			else if(line.substr(0, 3) == "mat"){
				fillvec3(trs, param.mat);
			}
		}
		trs.close();
	}
}

void doLight(const string& file, BoshartParam& param){
	ifstream trs(file);
	if(trs.is_open()){
		string line;
		while(getline(trs, line)){
			if(line.substr(0, 3) == "poi"){
				fillvec3(trs, param.light_pos);
			}
			else if(line.substr(0, 3) == "amb"){
				fillvec3(trs, param.ambient);
			}
			else if(line.substr(0, 3) == "lin"){
				getline(trs, line);
				param.lin_atten = stof(line);
			}
			else if(line.substr(0, 3) == "shi"){
				getline(trs, line);
				param.spec_power = stof(line);
			}
		}
		trs.close();
	}
}

void doCamera(const string& file, BoshartParam& param){
	ifstream trs(file);
	if(trs.is_open()){
		string line;
		while(getline(trs, line)){
			if(line.substr(0, 3) == "eye"){
				fillvec3(trs, param.eye);
			}
			else if(line.substr(0, 2) == "at"){
				fillvec3(trs, param.at);
			}
			else if(line.substr(0, 2) == "up"){
				fillvec3(trs, param.up);
			}
		}
		trs.close();
	}
}

void doFOV(const string& file, BoshartParam& param){
	ifstream trs(file);
	if(trs.is_open()){
		string line;
		while(getline(trs, line)){
			if(line.substr(0, 3) == "fov"){
				getline(trs, line);
				param.fov = stof(line);
			}
			else if(line.substr(0, 3) == "zma"){
				getline(trs, line);
				param.near = stof(line);
			}
			else if(line.substr(0, 3) == "zmi"){
				getline(trs, line);
				param.far = stof(line);
			}
		}
		trs.close();
	}
}

int main()
{
	{
		BoshartParam param;
		doTRS("trs.txt", param);
		doCamera("camera.txt", param);
		doFOV("fov.txt", param);
		doLight("shade.txt", param);
		Renderer renderer;
		renderer.init(800, 600, 4);
		renderer.draw(param);
		renderer.destroy();
	}
	printf("Clean exit\n");
	return 0;
}
