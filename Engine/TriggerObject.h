#pragma once

struct TriggerObject {
    glm::vec3 position;
    glm::vec3 size; // AABB
    std::function<void()> onEnter; 
    std::function<void()> onExit;  
};