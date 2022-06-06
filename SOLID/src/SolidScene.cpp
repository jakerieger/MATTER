#include "SolidScene.hpp"

void SolidScene::CreateEmpty(const char* name) {
    mGameObjects.clear();
    mLights.clear();
    mName = std::move(name);
}

void SolidScene::Load(const char* path) {}
void SolidScene::Save() {}

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
    mGameObjects.push_back(gameObject);
}

void SolidScene::AddLight(SolidLight* light) {
    mLights.push_back(light);
}