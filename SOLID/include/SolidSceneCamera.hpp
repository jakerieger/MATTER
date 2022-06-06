#pragma once

#include <corecrt_math_defines.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*******************************************************************************************
 * This is the camera used in the scene view.
 * It implements the Arcball (aka Orbit) camera mode.
 * FOV, aspect ratio, and near/far planes are configurable but the defaults are recommended.
 * 
 * This is a header-only class with all the implementation done here.
 *
 * @remark I based my implementation on the wonderful tutorial by
 * Marie Eve Dube here: https://asliceofrendering.com/camera/2019/11/30/ArcballCamera/
 *
 * @authors Jake Rieger, Marie Eve Dube
 ********************************************************************************************/
class SolidSceneCamera {
public:
    SolidSceneCamera() = default;

    SolidSceneCamera(glm::vec3 eye, glm::vec3 lookAt, glm::vec3 upVector, float fov = 45.0f, float aspectRatio = 16.f/9.f, float nearPlane = 0.01f, float farPlane = 1000.f)
        : mEye(std::move(eye))
        , mLookAt(std::move(lookAt))
        , mUpVector(std::move(upVector))
        , mFOV(fov)
        , mAspectRatio(aspectRatio)
        , mNearPlane(nearPlane)
        , mFarPlane(farPlane)
    {
        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }

    glm::mat4x4 GetViewMatrix() const { return mViewMatrix; }
    glm::mat4x4 GetProjectionMatrix() const { return mProjectionMatrix; }
    glm::vec3 GetEye() const { return mEye; }
    glm::vec3 GetLookAt() const { return mLookAt; }
    glm::vec3 GetUpVector() const { return mUpVector; }

    float GetNearPlane() const { return mNearPlane; }
    float GetFarPlane() const { return mFarPlane; }

    glm::vec3 GetViewDir() const { return -glm::transpose(mViewMatrix)[2]; }
    glm::vec3 GetRightVector() const { return glm::transpose(mViewMatrix)[0]; }

    void SetCameraView(glm::vec3 eye, glm::vec3 lookAt, glm::vec3 upVector) {
        mEye = std::move(eye);
        mLookAt = std::move(lookAt);
        mUpVector = std::move(upVector);
        UpdateViewMatrix();
    }

    void UpdateViewMatrix() {
        mViewMatrix = glm::lookAt(mEye, mLookAt, mUpVector);
    }

    void UpdateProjectionMatrix() {
        mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, mNearPlane, mFarPlane);
    }

    void ProcessMouseOrbit(float xoffset, float yoffset, glm::vec2 viewport) {
        glm::vec4 position(GetEye().x, GetEye().y, GetEye().z, 1.0f);
        glm::vec4 pivot(GetLookAt().x, GetLookAt().y, GetLookAt().z, 1.0f);

        float deltaAngleX = (2 * M_PI / viewport.x);
        float deltaAngleY = (M_PI / viewport.y);
        float angleX = deltaAngleX * xoffset;
        float angleY = deltaAngleY * yoffset;

        float cosAngle = glm::dot(GetViewDir(), mUpVector);
        if (cosAngle * glm::sign(deltaAngleY) > 0.99f) {
            deltaAngleY = 0.0f;
        }

        glm::mat4x4 rotationMatrix_X(1.0f);
        rotationMatrix_X = glm::rotate(rotationMatrix_X, angleX, mUpVector);
        position = (rotationMatrix_X * (position - pivot)) + pivot;

        glm::mat4x4 rotationMatrix_Y(1.0f);
        rotationMatrix_Y = glm::rotate(rotationMatrix_Y, angleY, GetRightVector());
        glm::vec3 finalPosition = (rotationMatrix_Y * (position - pivot)) + pivot;

        SetCameraView(finalPosition, GetLookAt(), mUpVector);
    }

private:
    glm::vec3 mEye;
    glm::vec3 mLookAt;
    glm::vec3 mUpVector;
    glm::mat4x4 mViewMatrix;
    glm::mat4x4 mProjectionMatrix;
    float mFOV;
    float mAspectRatio;
    float mNearPlane;
    float mFarPlane;
};