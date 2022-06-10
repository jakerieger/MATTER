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

#include "SolidTransform.hpp"

SolidTransform::SolidTransform() {
    mModelMatrix = glm::mat4(1.0f);
    mPosition = glm::vec3(0.0f);
    mRotation = glm::vec3(0.0f);
    mScale = glm::vec3(1.0f);
}

void SolidTransform::Translate(glm::vec3 translation) {
    mPosition += translation;
}

void SolidTransform::Rotate(float angle, RotationAxis axis) {
    switch (axis) {
    case X:
        mRotation.x += angle;
        break;
    case Y:
        mRotation.y += angle;
        break;
    case Z:
        mRotation.z += angle;
        break;
    }
}

void SolidTransform::Scale(glm::vec3 scale) {
    mScale += scale;
}

void SolidTransform::SetPositionAndRotation(glm::vec3 position, glm::vec3 rotation) {
    mPosition = position;
    mRotation = rotation;
}

glm::vec3 SolidTransform::GetEulerAngles() {
    glm::vec3 eulerAngles;
    eulerAngles.x = glm::degrees(glm::atan(mModelMatrix[1][0] / mModelMatrix[0][0]));
    eulerAngles.y = glm::degrees(glm::asin(-mModelMatrix[2][0]));
    eulerAngles.z = glm::degrees(glm::atan(mModelMatrix[2][1] / mModelMatrix[2][2]));
    return eulerAngles;
}

void SolidTransform::Update() {
    mModelMatrix = glm::mat4(1.0f);
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    mModelMatrix = glm::scale(mModelMatrix, mScale);
}