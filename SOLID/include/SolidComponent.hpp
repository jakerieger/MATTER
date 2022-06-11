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

#include <msgpack.hpp>
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

MSGPACK_ADD_ENUM(SolidComponentType);

class SolidComponent {
public:
    bool mActive;
    const char* mName;
    SolidGameObject* mGameObject;

    ~SolidComponent() { mGameObject = nullptr; }

    void SetType(SolidComponentType type) { mType = std::move(type); }
    SolidComponentType GetType() const { return mType; }

    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update(SolidSceneCamera& sceneCamera) {}
    virtual void FixedUpdate() {}
    virtual void LateUpdate() {}
    virtual void Destroyed() {}

    MSGPACK_DEFINE(mActive, mType);

private:
    SolidComponentType mType;
};