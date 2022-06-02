#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct GeneralPreferences {
    bool loadPreviousProjectOnStartup;
    bool showWelcomeScreenOnStartup;
};

struct ExternalToolsPreferences {
    const char* externalScriptEditor;
    const char* externalScriptEditorArgs;
    const char* imageEditor;
    const char* imageEditorArgs;
};

struct EditorPreferences {
    GeneralPreferences generalPreferences;
    ExternalToolsPreferences externalTools;
};

class SolidEditorConfig {
public:
    void Load();
    void Save();
    void SetEditorPreferences(EditorPreferences editorPreferences) { mEditorPreferences = editorPreferences; };
    EditorPreferences GetEditorPreferences() { return mEditorPreferences; };

private:
    EditorPreferences mEditorPreferences;
};