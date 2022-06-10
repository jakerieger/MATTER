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

    const char* GetTag() const { return mTag; }
    void SetTag(const char* tag) { mTag = std::move(tag); }

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
    const char* mTag;
};