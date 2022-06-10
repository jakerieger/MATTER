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

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SolidMeshRenderer.hpp"
#include "SolidComponent.hpp"
#include "SolidSceneCamera.hpp"

class SolidModel : public SolidComponent {
public:
    SolidModel(char* path);
    ~SolidModel();

    void Draw(glm::mat4 MVP);
    std::vector<SolidMeshRenderer> mMeshes;

    void Awake();
    void Start();
    void Update(SolidSceneCamera& sceneCamera);
    void LateUpdate();
    void FixedUpdate();
    void Destroyed();
private:
    std::string directory;

    void LoadModel(std::string path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    SolidMeshRenderer ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    std::vector<Texture> mTexturesLoaded;
};