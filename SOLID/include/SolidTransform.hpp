#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

private:
    glm::mat4 mModelMatrix;

};