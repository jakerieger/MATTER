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

#include <fstream>
#include "SolidUtils.hpp"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

/**
 * @brief Editor general preferences struct
 *
 * @author Jake Rieger
 */
struct GeneralPreferences {
    bool loadPreviousProjectOnStartup;
    bool showWelcomeScreenOnStartup;
};

/**
 * @brief Editor external tools preferences struct
 * 
 */
struct ExternalToolsPreferences {
    const char* externalScriptEditor;
    const char* externalScriptEditorArgs;
    const char* imageEditor;
    const char* imageEditorArgs;
};

/**
 * @brief Editor base preferences struct
 * 
 * Get's serialized to JSON for storage
 * 
 */
struct EditorPreferences {
    GeneralPreferences generalPreferences;
    ExternalToolsPreferences externalTools;
};

/**
 * @brief The Solid Editor configuration class.
 * 
 * Handles loading, saving, and initializing the Solid Editor configuration
 * 
 * @author Jake Rieger
 */
class SolidEditorConfig {
public:
    /**
     * @brief Load the Solid Editor configuration from a json file
     * 
     * @param config Serialized JSON object to load. This is the C++ representation of the JSON file that's been parsed elsewhere.
     */
    void Load(JSON config);

    /**
     * @brief Save the Solid Editor configuration to a json file
     * 
     * Serializes the Solid Editor configuration to a JSON file
     */
    void Save();

    /**
     * @brief Initialize the Solid Editor configuration
     * 
     * If no Solid Editor configuration file exists, this will create one.
     */
    void InitConfig();

    void SetEditorPreferences(EditorPreferences editorPreferences) { mEditorPreferences = editorPreferences; };
    EditorPreferences GetEditorPreferences() { return mEditorPreferences; };

    bool* GetLoadPreviousProjectOnStartup() { return &mEditorPreferences.generalPreferences.loadPreviousProjectOnStartup; }
    bool* GetShowWelcomeScreenOnStartup() { return &mEditorPreferences.generalPreferences.showWelcomeScreenOnStartup; }

private:
    EditorPreferences mEditorPreferences;
};