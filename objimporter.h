#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include "hlm.h"
#include <vector>
#include <string>

typedef std::vector<hlm::vec4> VertexBuffer;
typedef std::vector<int> IndexBuffer;

void objload(const std::string& filename, VertexBuffer& verts);

#endif