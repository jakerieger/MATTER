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
#include <msgpack.hpp>

enum RotationAxis { X, Y, Z };

class SolidTransform {
public:
    SolidTransform();

    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;

    glm::mat4 GetModelMatrix() { return mModelMatrix; }
    glm::vec3 GetEulerAngles();

    void Translate(glm::vec3 translation);
    void Rotate(float angle, RotationAxis axis);
    void Scale(glm::vec3 scale);
    void SetPositionAndRotation(glm::vec3 position, glm::vec3 rotation);

    void Update();

    MSGPACK_DEFINE(mPosition[0], mPosition[1], mPosition[2], mRotation[0], mRotation[1], mRotation[2], mScale[0], mScale[1], mScale[2]);

private:
    glm::mat4 mModelMatrix;
};