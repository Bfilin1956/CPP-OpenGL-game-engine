#pragma once

#include "RenderObject.h"
#include "Light.h"

struct Scene {
    std::vector<RenderObject> staticObjects;
    std::vector<RenderObject> dynamicObjects;
    std::vector<Light> lights;
};