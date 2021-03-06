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

#include "SolidScene.hpp"

/**
 * @brief Application settings when building a project
 * 
 */
struct BuildSettings {
    const char* companyName;
    const char* productName;
    const char* productVersion;
    const char* productCopyright;
    const char* productDescription;
    const char* productUrl;
    const char* productIcon;
};

/**
 * @brief Input action mapping struct
 * 
 */
struct ActionMapping {
    const char* actionName;
    int actionId; ///< GLFW_KEY_* or GLFW_MOUSE_BUTTON_*
};

/**
 * @brief Input axis mapping struct
 * 
 */
struct AxisMapping {
    const char* axisName;
    int axisId; ///< GLFW_KEY_* or GLFW_MOUSE_BUTTON_*
};

/**
 * @brief Holds input mappings for the current project
 * 
 */
struct InputManager {
    std::vector<ActionMapping> actionMappings;
    std::vector<AxisMapping> axisMappings;
};

/**
 * @brief Project-specific settings struct
 * 
 */
struct ProjectSettings {
    BuildSettings buildSettings;
    InputManager inputManager;
};

/**
 * @brief Class for managing project loading, saving, and settings
 * 
 * @author Jake Rieger
 */
class SolidProject {
public:
    void Load(const char* path);
    void Save(const char* path);

    void SetProjectSettings(ProjectSettings projectSettings) { mProjectSettings = projectSettings; }
    ProjectSettings GetProjectSettings() { return mProjectSettings; }

    void SetBuildSettings(BuildSettings buildSettings) { mProjectSettings.buildSettings = buildSettings; }
    BuildSettings GetBuildSettings() { return mProjectSettings.buildSettings; }

    void SetInputManager(InputManager inputManager) { mProjectSettings.inputManager = inputManager; }
    InputManager GetInputManager() { return mProjectSettings.inputManager; }

    void SetProjectName(const char* projectName) { mName = projectName; }
    const char* GetProjectName() { return mName; }

    void SetProjectPath(const char* projectPath) { mPath = projectPath; }
    const char* GetProjectPath() { return mPath; }

    void SetActiveScene(SolidScene* scene) { mActiveScene = std::move(scene); }
    SolidScene* GetActiveScene() { return mActiveScene; }

private:
    const char* mName;
    const char* mPath;
    ProjectSettings mProjectSettings;
    SolidScene* mActiveScene;
};