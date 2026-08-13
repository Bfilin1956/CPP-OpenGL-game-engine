//
// Created by filin on 8/13/26.
//

#include "RenderSystem.h"

RenderSystem &RenderSystem::instance() {
    static RenderSystem inst;
    return inst;
}

void RenderSystem::setSkyBox(Skybox *skybox) {
    skybox_ = skybox;
}

void RenderSystem::render(Scene &scene, Camera &camera) const {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), Window::instance().getAspectRatio(), 0.1f, 100.0f);

    skybox_->draw(camera, projection);
    Renderer::instance().draw(scene, view, projection, camera.position());
    Window::instance().swapBuffers();
}
