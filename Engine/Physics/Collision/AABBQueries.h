#pragma once

#include "AABB.h"
#include "../../Scene/RenderObject.h"

inline AABB getWorldAABB(const RenderObject& obj)
{
    const glm::vec3 scaledMin =
        obj.aabb.min * obj.scale;

    const glm::vec3 scaledMax =
        obj.aabb.max * obj.scale;

    return {
        obj.position + scaledMin,
        obj.position + scaledMax
    };
}