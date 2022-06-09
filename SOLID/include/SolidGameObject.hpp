#pragma once

#include <vector>
#include <map>

#include "SolidCamera.hpp"
#include "SolidTransform.hpp"
#include "SolidComponent.hpp"
#include "SolidSceneCamera.hpp"

enum SolidGameObjectType {
    GO_GameObject,
    GO_Light,
    GO_Camera,
    GO_Terrain,
    GO_Skybox
};

class SolidGameObject {
public:
    const char* mName;
    SolidTransform mTransform;

    SolidGameObject(const char* name, SolidGameObjectType type);
    SolidGameObjectType GetType() const { return mType; }

    std::vector<SolidComponent*> mComponents;
    std::vector<SolidGameObject*> mChildren;

    unsigned int GetID() const { return mID; }
    void SetID(unsigned int id) { mID = std::move(id); }

    template<typename T>
    T* GetComponent() {
        for (auto& component : mComponents) {
            if (typeid(*component) == typeid(T)) {
                return static_cast<T*>(component);
            }
        }
        return nullptr;
    }

    template<typename T>
    void AddComponent(T* component) {
        mComponents.push_back(component);
        component->mGameObject = this;
    }

    void Awake();
    void Start();
    void Update(SolidSceneCamera& sceneCamera);
    void LateUpdate();
    void FixedUpdate();
    void Destroyed();

private:
    SolidGameObjectType mType;
    unsigned int mID;
};