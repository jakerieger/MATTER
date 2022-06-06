#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "SolidShader.hpp"

class SolidGizmo {
public:
    const char* mGizmoName;
    SolidGizmo(const char* gizmoName);
    virtual ~SolidGizmo();

private:
    SolidShader* mGizmoShader;
};

class SolidAxisGizmo : public SolidGizmo {
public:
    glm::vec3 mPosition;
};