#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SolidMeshRenderer.hpp"
#include "SolidComponent.hpp"

class SolidModel : public SolidComponent {
public:
    SolidModel(char* path);
    ~SolidModel();

    void Draw();
    std::vector<SolidMeshRenderer> mMeshes;

    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FixedUpdate();
    void Destroyed();
private:

};