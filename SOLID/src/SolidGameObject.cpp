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

#include "SolidGameObject.hpp"

SolidGameObject::SolidGameObject(const char* name, SolidGameObjectType type) {
    mName = std::move(name);
    mType = std::move(type);
    mTransform = SolidTransform();
    Awake();
}

SolidGameObject::~SolidGameObject() {
    for (auto& component : mComponents) {
        delete component;
    }

    mComponents.clear();

    for (auto& child : mChildren) {
        delete child;
    }

    mChildren.clear();
}

void SolidGameObject::Awake() {
    for (auto& component : mComponents) {
        component->Awake();
    }

    for (auto& child : mChildren) {
        child->Awake();
    }
}

void SolidGameObject::Start() {
    for (auto& component : mComponents) {
        component->Start();
    }

    for (auto& child : mChildren) {
        child->Start();
    }
}

void SolidGameObject::Update(SolidSceneCamera& sceneCamera) {
    mTransform.Update();

    for (auto& component : mComponents) {
        component->Update(sceneCamera);
    }

    for (auto& child : mChildren) {
        child->Update(sceneCamera);
    }
}

void SolidGameObject::LateUpdate() {
    for (auto& component : mComponents) {
        component->LateUpdate();
    }

    for (auto& child : mChildren) {
        child->LateUpdate();
    }
}

void SolidGameObject::FixedUpdate() {
    for (auto& component : mComponents) {
        component->FixedUpdate();
    }

    for (auto& child : mChildren) {
        child->FixedUpdate();
    }
}

void SolidGameObject::Destroyed() {
    for (auto& component : mComponents) {
        component->Destroyed();
    }

    for (auto& child : mChildren) {
        child->Destroyed();
    }
}

void SolidGameObject::Serialize(SolidGameObject& gameObject) {

}