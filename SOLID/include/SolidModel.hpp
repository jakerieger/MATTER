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

class SolidModel : public SolidComponent {
public:
    SolidModel(char* path);
    ~SolidModel();

    void Draw();
    std::vector<SolidMeshRenderer> mMeshes;

    void Awake();
    void Start();
    void Update();
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