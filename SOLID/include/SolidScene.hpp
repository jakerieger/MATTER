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

#include <string>
#include <vector>
#include <algorithm>

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
    std::vector<SolidLight*> GetLights();
    SolidCamera* GetActiveCamera();

    void AddGameObject(SolidGameObject* gameObject);
    void RemoveGameObject(unsigned int ID);

private:
    std::vector<SolidGameObject*> mGameObjects;
    const char* mPath;
    const char* mName;
};