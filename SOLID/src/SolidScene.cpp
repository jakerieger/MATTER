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

#include "SolidScene.hpp"

void SolidScene::CreateEmpty(const char* name) {
    mGameObjects.clear();
    mName = std::move(name);
}

void SolidScene::Load(const char* path) {}
void SolidScene::Save() {}

std::vector<SolidLight*> SolidScene::GetLights() {
    std::vector<SolidLight*> lights;

    for (auto& gameObject : mGameObjects) {
        if (gameObject->GetType() == SolidGameObjectType::GO_Light) {
            lights.push_back(static_cast<SolidLight*>(gameObject));
        }
    }

    return lights;
}

SolidCamera* SolidScene::GetActiveCamera() {
    if (mGameObjects.size() <= 0) {
        return nullptr;
    }

    for (auto& gameObject : mGameObjects) {
        if (gameObject->GetType() == SolidGameObjectType::GO_Camera) {
            for (auto& component : gameObject->mComponents) {
                if (component->GetType() == SolidComponentType::COM_Camera) {
                    return static_cast<SolidCamera*>(component);
                }
            }
        }
    }

    return nullptr;
}

void SolidScene::AddGameObject(SolidGameObject* gameObject) {
    gameObject->SetID(mGameObjects.size() + 1);
    mGameObjects.push_back(gameObject);
}

void SolidScene::RemoveGameObject(unsigned int ID) {
    for (auto& gameObject : mGameObjects) {
        if (gameObject->GetID() == ID) {
            delete gameObject;
            mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), gameObject), mGameObjects.end());
            break;
        }
    }

    // mGameObjects.erase(mGameObjects.begin() + (ID - 1));
}