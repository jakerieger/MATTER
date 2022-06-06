#pragma once

#include "SolidShader.hpp"
#include "SolidUtils.hpp"
#include "SolidSceneCamera.hpp"

class SolidEditorGrid {
public:
    void Init();
    void Draw(SolidSceneCamera &sceneCamera);
    void Destroy();

private:
    SolidShader* mGridShader;
    unsigned int mVBO, mVAO;
};