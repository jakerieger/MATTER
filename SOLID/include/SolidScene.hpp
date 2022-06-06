#pragma once

#include <string>
#include <vector>

#include "SolidGameObject.hpp"
#include "SolidLight.hpp"
#include "SolidCamera.hpp"

class SolidScene {
public:
    void CreateEmpty(const char* name);
    void Load(const char* path);
    void Save();

    const char* GetScenePath() const { return mPath; }
    const char* GetSceneName() const { return mName; }

    std::vector<SolidGameObject*> GetGameObjects() { return mGameObjects; }
    std::vector<SolidLight*> GetLights() { return mLights; }
    SolidCamera* GetActiveCamera();

    void AddGameObject(SolidGameObject* gameObject);
    void AddLight(SolidLight* light);

private:
    std::vector<SolidGameObject*> mGameObjects; 
    std::vector<SolidLight*> mLights;
    const char* mPath;
    const char* mName;
};