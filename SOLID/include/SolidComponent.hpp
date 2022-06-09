#pragma once

#include "SolidSceneCamera.hpp"

class SolidGameObject; ///< Forward declaration

enum SolidComponentType {
    COM_Light,
    COM_Camera,
    COM_Model,
    COM_Rigidbody,
    COM_Softbody,
    COM_Terrain,
    COM_Material
};

class SolidComponent {
public:
    bool mActive;
    const char* mName;
    SolidGameObject* mGameObject;

    void SetType(SolidComponentType type) { mType = std::move(type); }
    SolidComponentType GetType() const { return mType; }

    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update(SolidSceneCamera& sceneCamera) {}
    virtual void FixedUpdate() {}
    virtual void LateUpdate() {}
    virtual void Destroyed() {}

private:
    SolidComponentType mType;
};