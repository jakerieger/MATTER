#pragma once

#include <vector>

struct BuildSettings {
    const char* companyName;
    const char* productName;
    const char* productVersion;
    const char* productCopyright;
    const char* productDescription;
    const char* productUrl;
    const char* productIcon;
};

struct ActionMapping {
    const char* actionName;
    int actionId; // GLFW_KEY_XXX ID
};

struct AxisMapping {
    const char* axisName;
    int axisId; // GLFW_KEY_XXX ID or GLFW_MOUSE_XXX ID
};

struct InputManager {
    std::vector<ActionMapping> actionMappings;
    std::vector<AxisMapping> axisMappings;
};

struct ProjectSettings {
    BuildSettings buildSettings;
    InputManager inputManager;
};

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

private:
    const char* mName;
    const char* mPath;
    ProjectSettings mProjectSettings;

};