#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include "vertexbuffer.h"
#include <string>

void objload(const std::string& filename, VertexBuffer& verts);

#endif