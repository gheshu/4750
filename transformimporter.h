#ifndef TRANFORM_IMPORTER_H
#define TRANFORM_IMPORTER_H

#include "mat4.h"
#include <string>

void transformLoad(const std::string& filename, hlm::mat4& mat);

#endif