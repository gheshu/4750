#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "vec2.h"

struct Material{
	hlm::vec2 uv_scale, uv_offset;
	float spec_exp, spec_str;
	unsigned d_id, n_id;
	Material(unsigned _d_id, unsigned _n_id, float spec_e = 32.0f, 
		float spec_s = 1.0f, const hlm::vec2& uv_s = hlm::vec2(1.0f, 1.0f), 
		const hlm::vec2& uv_o = hlm::vec2(0.0f, 0.0f)) 
		: uv_scale(uv_s), uv_offset(uv_o),  
		spec_exp(spec_e), spec_str(spec_s), 
		d_id(_d_id), n_id(_n_id) {};
};

#endif