#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SolidColor.hpp"
#include "SolidShader.hpp"

struct Diffuse {
    SolidColor color;
    unsigned int* texture;
};

struct Specular {
    SolidColor color;
    unsigned int* texture;
    float strength;
};

struct Emission {
    SolidColor color;
    unsigned int* texture;
    float strength;
};

enum RenderingMode { Opaque, Transparent };

class SolidMaterial {
public:
    void SetShader(SolidShader* shader) { mShader = shader; }
    SolidShader* GetShader() { return mShader; }

    void SetRenderingMode(RenderingMode mode) { mRenderingMode = mode; }
    RenderingMode GetRenderingMode() { return mRenderingMode; }

    void SetColor(std::string name, const SolidColor& color);
    void SetInteger(std::string name, int value);
    void SetFloat(std::string name, float value);
    void SetVector(std::string name, const glm::vec3& vector);
    void SetVector(std::string name, const glm::vec4& vector);
    void SetMatrix(std::string name, const glm::mat4& matrix);
    void SetTexture(std::string name, const unsigned int texture);

    virtual void Bind(glm::mat4 MVP) {}

private:
    SolidShader* mShader;
    RenderingMode mRenderingMode;
};

class PhongMaterial : public SolidMaterial {
public:
    PhongMaterial();
    ~PhongMaterial();

    void SetDiffuse(const Diffuse& diffuse) { mDiffuse = diffuse; }
    void SetSpecular(const Specular& specular) { mSpecular = specular; }
    void SetEmission(const Emission& emission) { mEmission = emission; }

    Diffuse GetDiffuse() { return mDiffuse; }
    Specular GetSpecular() { return mSpecular; }
    Emission GetEmission() { return mEmission; }

    void Bind(glm::mat4 MVP);

private:
    Diffuse mDiffuse;
    Specular mSpecular;
    Emission mEmission;
};

class UnlitMaterial: public SolidMaterial {
public:
    UnlitMaterial();
    ~UnlitMaterial();

    void SetDiffuse(const Diffuse& diffuse) { mDiffuse = diffuse; }
    Diffuse GetDiffuse() { return mDiffuse; }

    void Bind(glm::mat4 MVP);

private:
    Diffuse mDiffuse;
};