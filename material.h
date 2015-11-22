#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "vec2.h"

struct Material{
	hlm::vec2 uv_scale, uv_offset;
	std::string diffuse, normal;
	float spec_exp, spec_str;
	Material(const std::string& dname, const std::string& nname, float spec_e = 32.0f, 
		float spec_s = 1.0f, const hlm::vec2& uv_s = hlm::vec2(1.0f), 
		const hlm::vec2& uv_o = hlm::vec2(0.0f)) 
		: uv_scale(uv_s), uv_offset(uv_o), diffuse(d_id), normal(n_id), 
		spec_exp(spec_e), spec_str(spec_s){};
};

#endif