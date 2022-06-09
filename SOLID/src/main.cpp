#include <stdio.h>
#include <istream>
#include <fstream>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include "SolidEditorConfig.hpp"
#include "SolidEditor.hpp"
#include "SolidUtils.hpp"
#include "SolidProject.hpp"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

std::tuple<MonoDomain*, MonoAssembly*> LoadManagedLibs() {
    MonoDomain* domain;
    domain = mono_jit_init("MatterEngine");
    MonoAssembly* assembly;
    assembly = mono_domain_assembly_open(domain, "MatterEngine.dll");

    return std::make_tuple(domain, assembly);
}

void CleanupManagedLibs(MonoDomain* domain) {
    mono_jit_cleanup(domain);
}

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

    SolidProject testProject;
    testProject.SetProjectName("Test Project");
    testProject.SetProjectPath("Y:\\tmp\\TestProject");
    SolidScene testScene;
    testScene.CreateEmpty("TestScene");
    testProject.SetActiveScene(&testScene);

    SolidEditor editor;
    editor.SetEditorConfig(editorConfig);
    editor.SetProject(testProject);
    editor.Run();

    return 0;
}