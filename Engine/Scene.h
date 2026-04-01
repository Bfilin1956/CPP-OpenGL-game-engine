#pragma once
#include "TriggerObject.h"

struct Scene {
    std::vector<RenderObject> staticObjects;
    std::vector<RenderObject> dynamicObjects;
    std::vector<Light> lights;
    std::vector<TriggerObject> triggers;
};