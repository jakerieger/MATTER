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

#include <iostream>

#include <glad/glad.h>
#include <imgui/imgui.h>

#include "SolidEditorGrid.hpp"
#include "SolidPrimitive.hpp"

void SolidEditorGrid::Init() {
    mGridShader = new SolidShader((SolidUtils::GetEditorShadersPath() + "\\editor\\Grid.shader").c_str());
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SolidPrimitive::Plane.vertices.size(), &SolidPrimitive::Plane.vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mGridShader->Use();
}

void SolidEditorGrid::Draw(SolidSceneCamera &sceneCamera) {
    glm::vec3 lineColor = glm::vec3(64.f / 255.f, 64.f / 255.f, 64.f / 255.f);
    glm::vec3 xAxisColor = glm::vec3(227.f / 255.f, 91.f / 255.f, 91.f / 255.f);
    glm::vec3 yAxisColor = glm::vec3(45.f / 255.f, 137.f / 255.f, 229.f / 255.f);

    mGridShader->Use();
    mGridShader->setMat4("projection", sceneCamera.GetProjectionMatrix());
    mGridShader->setMat4("view", sceneCamera.GetViewMatrix());
    mGridShader->setVec3("gridLineColor", lineColor);
    mGridShader->setVec3("xAxisColor", xAxisColor);
    mGridShader->setVec3("zAxisColor", yAxisColor);
    mGridShader->setFloat("near", sceneCamera.GetNearPlane());
    mGridShader->setFloat("far", sceneCamera.GetFarPlane());

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SolidEditorGrid::Destroy() {
    delete mGridShader;
}