//
// Created by r13x on 3/28/26.
//

#include "ModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

std::vector<Texture> ModelLoader::loadMaterialTextures(TextureLoader &texture_loader, aiMaterial *mat,
                                                       aiTextureType type, const std::string &typeName) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        Texture tex;
        tex.id = texture_loader.getIdTexture(str.C_Str());
        tex.type = typeName;
        tex.path = str.C_Str();

        textures.push_back(tex);
    }
    return textures;
}

Model ModelLoader::load(TextureLoader &texture_loader, const std::string &path) {
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs
    );

    if (!scene || !scene->mRootNode) {
        throw std::runtime_error("Assimp load error");
    }

    Model model;

    processNode(texture_loader, scene->mRootNode, const_cast<aiScene *>(scene), model);
    return model;
}

void ModelLoader::processNode(TextureLoader &texture_loader, aiNode *node, aiScene *scene, Model &model) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.push_back(processMesh(texture_loader, mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(texture_loader, node->mChildren[i], scene, model);
    }
}

Mesh ModelLoader::processMesh(TextureLoader &texture_loader, aiMesh *mesh, aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    auto diffuseMaps = loadMaterialTextures(texture_loader, material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    auto specularMaps = loadMaterialTextures(texture_loader, material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex v{};

        v.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        v.normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        };

        if (mesh->mTextureCoords[0]) {
            v.texCoords = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        } else {
            v.texCoords = {0.0f, 0.0f};
        }

        vertices.push_back(v);
    }

    // indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return {vertices, indices, textures};
}
