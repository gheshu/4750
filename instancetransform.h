#ifndef INSTANCE_TRANSFORM_H
#define INSTANCE_TRANSFORM_H

#include <tuple>
#include <string>
#include <vector>
#include "mat4.h"

typedef std::pair<std::string, hlm::mat4> InstanceTransform;
typedef std::vector<InstanceTransform> TransformList;

#endif