#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.h"

Renderer::Renderer(TextureLoader &textureLoader): textureLoader_(textureLoader){}

void Renderer::applyLights(Shader* shader, const std::vector<Light>& lights)
{
    for (int i = 0; i < lights.size(); i++) {
        std::string base = "lights[" + std::to_string(i) + "]";
        shader->setVec3(base + ".position",
                        lights[i].position.x,
                        lights[i].position.y,
                        lights[i].position.z);
    }

    shader->setInt("lightCount", (int)lights.size());
}

void Renderer::buildBatches(std::vector<RenderObject>& objects,
                  std::unordered_map<Shader*, std::vector<RenderObject*>>& batches)
{
    batches.clear();

    for (auto& obj : objects) {
        if (!obj.material || !obj.material->shader) continue;
        batches[obj.material->shader].push_back(&obj);

    }
}
glm::vec3 lightPos(1.2f, 5.0f, 2.0f);
void Renderer::draw(Scene &scene,
            glm::mat4& view,
            glm::mat4& projection,
            glm::vec3 viewPos) {

    for (auto& obj : scene.staticObjects) {
        obj.material->shader->use();
        glm::mat4 model = obj.getModelMatrix();
        obj.material->shader->setMat4_mat4("view", view);
        obj.material->shader->setMat4_mat4("projection", projection);
        obj.material->shader->setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);
        obj.material->shader->setMat4_mat4("model", model);

        obj.material->shader->setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        obj.material->shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        obj.material->shader->setFloat("ambientStrength", 0.1f);
        obj.material->shader->setFloat("shininess", 32.0f);
        /*if (GLuint texID = textureLoader_.getIdTexture(obj.textureName)) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texID);

            obj.material->shader->setInt("uTexture", 0);
        }*/

        for (unsigned int i = 0; i < obj.model->meshes.front().textures_.size(); i++) {


            std::string name = obj.model->meshes.front().textures_[i].type + std::to_string(i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, obj.model->meshes.front().textures_[i].id);
            obj.material->shader->setInt("uTexture", 0);
        }

        for (auto& mesh : obj.model->meshes) {
            mesh.draw();
        }
    }



    /*std::unordered_map<Shader*, std::vector<RenderObject*>> batches;

    buildBatches(scene.staticObjects, batches);
    drawBatches(batches, view, projection, viewPos);

    buildBatches(scene.dynamicObjects, batches);
    drawBatches(batches, view, projection, viewPos);*/
}

void Renderer::drawBatches(std::unordered_map<Shader*, std::vector<RenderObject*>>& batches,
                glm::mat4& view,
                glm::mat4& projection,
                glm::vec3 viewPos)
{
    for (auto& [shader, objects] : batches) {

        shader->use();

        shader->setMat4_mat4("view", view);
        shader->setMat4_mat4("projection", projection);
        shader->setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);

        /*for (auto* obj : objects) {

            /*shader->setMat4_mat4("model", obj->model);#1#

            GLuint texID = textureLoader_.getIdTexture(obj->textureName);
            if (texID != 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texID);
                shader->setInt("uTexture", 0);
            }

            /*obj->mesh->draw();#1#
        }*/
    }
}