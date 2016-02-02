#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include <string>
struct Mesh;

bool objload(const std::string& filename, Mesh& out);
bool objloadNoIndices(const std::string& filename, Mesh& out, bool smooth, bool project);

#endif
