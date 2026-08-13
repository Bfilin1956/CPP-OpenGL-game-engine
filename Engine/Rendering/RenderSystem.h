//
// Created by filin on 8/13/26.
//

#pragma once

#include "Rendering/Renderer.h"
#include "Skybox.h"
#include "Platform/Window.h"

class RenderSystem {
public:
    void render(Scene& scene, Camera& camera) const;

    static RenderSystem &instance();
    void setSkyBox(Skybox *skybox);

    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;
    RenderSystem(RenderSystem&&) = delete;
    RenderSystem& operator=(RenderSystem&&) = delete;
private:
    Skybox *skybox_;
};

