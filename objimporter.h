#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include <string>

struct MeshData;

bool objload(const std::string& filename, MeshData& out, bool smooth, bool project);

#endif