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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum ShaderType { Phong, BlinnPhong, Unlit };

/**
 * @brief Class used to load, compile, and link GLSL shaders
 * 
 * @author Jake Rieger
 */
class SolidShader {
public:
    unsigned int ID;
    SolidShader(const char* shaderPath);
    ~SolidShader();
    static SolidShader* NewFromType(ShaderType type);
    void Use();
    void Destroy();

    /**
     * @defgroup Uniform Setters
     * @{
     */
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    /**
     * @}
     */

private:
    enum ECompileType {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        PROGRAM
    };

    void checkCompileErrors(GLuint shader, ECompileType type);
};