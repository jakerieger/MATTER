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