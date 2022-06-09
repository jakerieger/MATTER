#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SolidMaterial.hpp"

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

    SolidMeshRenderer(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(glm::mat4& MVP);
    SolidMaterial* GetMaterial() { return mMaterial; }

private:
    unsigned int VAO, VBO, EBO;
    SolidMaterial* mMaterial;
    void SetupMesh();
};