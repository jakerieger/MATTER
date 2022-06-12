/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SolidModel.hpp"
#include "SolidGameObject.hpp"
#include "SolidEditor.hpp"

SolidModel::SolidModel(char* path) {
    LoadModel(path);
    mName = "Model"; // Redundant with the mType member, TODO: remove
    SetType(COM_Model);
}

SolidModel::~SolidModel() {

}

void SolidModel::Draw(glm::mat4 MVP) {
    for (unsigned int i = 0; i < mMeshes.size(); i++) {
        mMeshes[i].Draw(MVP);
    }
}

void SolidModel::LoadModel(std::string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('\\'));
    ProcessNode(scene->mRootNode, scene);
}

void SolidModel::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        mMeshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

SolidMeshRenderer SolidModel::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    aiString name = mesh->mName;
    std::string meshName = std::string(name.C_Str());

    return SolidMeshRenderer(vertices, indices, textures, meshName);
}

std::vector<Texture> SolidModel::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        for (unsigned int j = 0; j < mTexturesLoaded.size(); j++) {
            if (std::strcmp(mTexturesLoaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(mTexturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            /**
             * @todo Load textures from model
             */
        }
    }

    return textures;
}

void SolidModel::Awake() {

}

void SolidModel::Start() {

}

void SolidModel::Update(SolidSceneCamera& sceneCamera) {
    unsigned int numOfLights = SolidEditor::GetInstance()->GetProject().GetActiveScene()->GetLights().size();

    glm::mat4 model = this->mGameObject->mTransform.GetModelMatrix();
    glm::mat4 view = sceneCamera.GetViewMatrix();
    glm::mat4 projection = sceneCamera.GetProjectionMatrix();
    glm::mat4 MVP = projection * view * model;

    Draw(MVP);
}

void SolidModel::LateUpdate() {

}

void SolidModel::FixedUpdate() {

}

void SolidModel::Destroyed() {

}