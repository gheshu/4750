#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include <string>
class Mesh;

bool objload(const std::string& filename, Mesh& out);

#endif