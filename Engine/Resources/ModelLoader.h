#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Rendering/Texture.h"
#include "Rendering/TextureLoader.h"

class ModelLoader {
public:
    static Model load(TextureLoader &texture_loader,const std::string& path);
    static std::vector<Texture> loadMaterialTextures(TextureLoader &texture_loader, aiMaterial* mat, aiTextureType type, const std::string& typeName);


    static ModelLoader& instance();
    ModelLoader() = default;
    ModelLoader(const ModelLoader&) = delete;
    ModelLoader& operator=(const ModelLoader&) = delete;
    ModelLoader(ModelLoader&&) = delete;
    ModelLoader& operator=(ModelLoader&&) = delete;
private:
    static void processNode(TextureLoader &texture_loader,aiNode *node, aiScene *scene, Model &model);

    static Mesh processMesh(TextureLoader &texture_loader,aiMesh* mesh, aiScene* scene);
};
