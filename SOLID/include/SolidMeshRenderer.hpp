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

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SolidMaterial.hpp"
#include "SolidLogger.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int ID;
    std::string type;
    std::string path;
};

class SolidMeshRenderer {
public:
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;

    SolidMeshRenderer(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::string name);
    void Draw(glm::mat4& MVP);
    SolidMaterial* GetMaterial() { return mMaterial; }
    std::string& GetName() { return mName; }
    void SetName(const std::string& name) { mName = std::move(name); }

private:
    unsigned int VAO, VBO, EBO;
    SolidMaterial* mMaterial;
    std::string mName;
    void SetupMesh();
};