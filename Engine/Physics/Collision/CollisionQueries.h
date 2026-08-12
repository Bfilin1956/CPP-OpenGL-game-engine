#pragma once

#include "Physics/Shapes/Capsule.h"
#include "Physics/Collision/AABB.h"
#include "Physics/Collision/CollisionHit.h"

bool sweepCapsuleVsAABB( const Capsule& capsule, const AABB& box, const glm::vec3& displacement, CollisionHit& hit);