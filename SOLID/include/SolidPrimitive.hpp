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
#include <glm/glm.hpp>

struct Primitive {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> texCoords;
};

struct PrimitiveVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct PrimitiveData {
    std::vector<PrimitiveVertex> vertices;
    std::vector<unsigned int> indices;
};

/**
 * @brief Namespace providing some basic polygon primitives.
 * 
 * Each Primitive type provides an array of vertices, normals, texture coordinates, and indices
 * that can be passed directly to OpenGL for rendering.
 * 
 * @author Jake Rieger
 */
namespace SolidPrimitive {
    inline static Primitive Plane = {
        {
            // first triangle
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f,  // top left 
            // second triangle
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        },
        {
            0, 1, 3,
            1, 2, 3
        },
        {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        }
    };

    inline static PrimitiveData Quad = {
        {
            { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) }
        },
        {
            0, 1, 3,
            1, 2, 3
        },
    };

    inline static Primitive Cube = {
        {
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
        },
        {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            4, 5, 1,
            1, 0, 4
        },
        {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
        }
    };
}