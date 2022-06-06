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