#include "SolidMaterial.hpp"

void SolidMaterial::SetColor(std::string name, const SolidColor& color) {
    mShader->setVec4(name, color.r, color.g, color.b, color.a);
}

void SolidMaterial::SetInteger(std::string name, int value) {
    mShader->setInt(name, value);
}

void SolidMaterial::SetFloat(std::string name, float value) {
    mShader->setFloat(name, value);
}

void SolidMaterial::SetVector(std::string name, const glm::vec3& vector) {
    mShader->setVec3(name, vector);
}

void SolidMaterial::SetVector(std::string name, const glm::vec4& vector) {
    mShader->setVec4(name, vector);
}

void SolidMaterial::SetMatrix(std::string name, const glm::mat4& matrix) {
    mShader->setMat4(name, matrix);
}

void SolidMaterial::SetTexture(std::string name, const unsigned int texture) {
    mShader->setInt(name, texture);
}

PhongMaterial::PhongMaterial() : SolidMaterial() {
    mShader = SolidShader::NewFromType(ShaderType::Phong);
    mRenderingMode = Opaque;
    SetType(MaterialType::MAT_Phong);

    mDiffuse = Diffuse();
    mSpecular = Specular();
    mEmission = Emission();
}

PhongMaterial::~PhongMaterial() {
    delete mShader;
}

void PhongMaterial::Bind(glm::mat4 MVP) {
    mShader->Use();
    SetColor("material.ambient", mDiffuse.color);
    SetColor("material.diffuse", mDiffuse.color);
    SetColor("material.specular", mSpecular.color);
    SetColor("material.emission", mEmission.color);
    SetFloat("material.shininess", mSpecular.strength);
    SetTexture("material.diffuseTexture", *mDiffuse.texture);
    SetTexture("material.specularTexture", *mSpecular.texture);
    SetTexture("material.emissionTexture", *mEmission.texture);
    SetMatrix("MVP", MVP);
}

UnlitMaterial::UnlitMaterial() : SolidMaterial() {
    mShader = SolidShader::NewFromType(ShaderType::Unlit);
    mRenderingMode = Opaque;
    SetType(MaterialType::MAT_Unlit);

    mDiffuse = Diffuse();
}

void UnlitMaterial::Bind(glm::mat4 MVP) {
    mShader->Use();
    SetColor("material.diffuse", mDiffuse.color);

    if (mDiffuse.texture != nullptr) {
        SetTexture("material.texture", *mDiffuse.texture);
        SetInteger("material.hasTexture", 1);
    } else {
        SetInteger("material.hasTexture", 0);
    }

    SetMatrix("MVP", MVP);
}

UnlitMaterial::~UnlitMaterial() {
    delete mShader;
}

Diffuse::Diffuse() {
    color = SolidColor(1.0f, 1.0f, 1.0f, 1.0f);
    texture = nullptr;
}

Specular::Specular() {
    color = SolidColor(1.0f, 1.0f, 1.0f, 1.0f);
    texture = nullptr;
    strength = 1.0f;
}

Emission::Emission() {
    color = SolidColor(1.0f, 1.0f, 1.0f, 1.0f);
    texture = nullptr;
    strength = 1.0f;
}