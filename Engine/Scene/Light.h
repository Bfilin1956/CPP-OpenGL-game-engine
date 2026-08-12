#pragma once
#include <glm/glm.hpp>

struct Light {
    enum Type { Directional, Point, Spot } type;
    
    glm::vec3 position; 
    glm::vec3 direction;
    glm::vec3 color;    
    float intensity;     

    float cutoff;      
};