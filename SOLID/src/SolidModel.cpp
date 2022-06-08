#include "SolidModel.hpp"
#include "SolidGameObject.hpp"

SolidModel::SolidModel(char* path) {
    LoadModel(path);
    mName = "Model"; // Redundant with the mType member, TODO: remove
    SetType(COM_Model);
}

SolidModel::~SolidModel() {

}

void SolidModel::Draw() {
    for (unsigned int i = 0; i < mMeshes.size(); i++) {
        mMeshes[i].Draw(glm::mat4(1.0f));
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

    return SolidMeshRenderer(vertices, indices, textures);
}

std::vector<Texture> SolidModel::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    return std::vector<Texture>();
}

void SolidModel::Awake() {

}

void SolidModel::Start() {

}

void SolidModel::Update() {

}

void SolidModel::LateUpdate() {

}

void SolidModel::FixedUpdate() {

}

void SolidModel::Destroyed() {

}