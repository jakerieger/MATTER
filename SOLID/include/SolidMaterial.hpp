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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SolidColor.hpp"
#include "SolidShader.hpp"

struct Diffuse {
    SolidColor color;
    unsigned int* texture;
    Diffuse();
};

struct Specular {
    SolidColor color;
    unsigned int* texture;
    float strength;
    Specular();
};

struct Emission {
    SolidColor color;
    unsigned int* texture;
    float strength;
    Emission();
};

enum RenderingMode { Opaque, Transparent };
enum MaterialType { MAT_Phong, MAT_Unlit };

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
    MaterialType GetType() { return mType; }
    void SetType(MaterialType type) { mType = type; }
    
    SolidShader* mShader;
    RenderingMode mRenderingMode;

private:
    MaterialType mType;
};

class PhongMaterial : public SolidMaterial {
public:
    PhongMaterial();
    ~PhongMaterial();

    void SetDiffuse(const Diffuse& diffuse) { mDiffuse = diffuse; }
    void SetSpecular(const Specular& specular) { mSpecular = specular; }
    void SetEmission(const Emission& emission) { mEmission = emission; }

    void Bind(glm::mat4 MVP);

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
    Diffuse mDiffuse;
};