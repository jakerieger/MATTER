#include "SolidMeshRenderer.hpp"

SolidMeshRenderer::SolidMeshRenderer(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    mVertices = vertices;
    mIndices = indices;
    mTextures = textures;
    SetupMesh();
}

void SolidMeshRenderer::SetupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

/**
 * @todo Pass a material to this function and use it to set the shader uniforms.
 * Practically, each material will have one texture map for each texture type.
 */
void SolidMeshRenderer::Draw() {
    // unsigned int diffuseNr = 1;
    // unsigned int specularNr = 1;
    // for (unsigned int i = 0; i < mTextures.size(); i++) {
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     std::string number;
    //     std::string name = mTextures[i].type;
    //     if (name == "texture_diffuse") {
    //         number = std::to_string(diffuseNr++);
    //     } else if (name == "texture_specular") {
    //         number = std::to_string(specularNr++);
    //     }
    //     glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
    //     glBindTexture(GL_TEXTURE_2D, mTextures[i].ID);
    // }

    // glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}