#include <stdio.h>
#include <istream>
#include <fstream>

#include "SolidEditorConfig.hpp"
#include "SolidEditor.hpp"
#include "SolidUtils.hpp"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

int main(int argc, char *argv[]) {
    // Get last opened project

    if (argv[1] != nullptr) {
        // Project path provided, load project
    }

    SolidEditorConfig editorConfig;

    if (!std::filesystem::exists(SolidUtils::GetEditorConfigPath())) {
        // Create new config
        editorConfig.InitConfig();
    } else {
        // Load config
        std::ifstream configFile(SolidUtils::GetEditorConfigPath());
        JSON config;
        configFile >> config;
        configFile.close();

        editorConfig.Load(config);
    }

    SolidEditor editor;
    editor.SetEditorConfig(editorConfig);
    editor.Run();

    return 0;
}