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

#include <stdio.h>
#include <istream>
#include <fstream>
#include <chrono>
#include <thread>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include "SolidEditorConfig.hpp"
#include "SolidEditor.hpp"
#include "SolidUtils.hpp"
#include "SolidProject.hpp"

#include <Windows/SplashScreen.hpp>

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

int main(int argc, char *argv[]) {
    // Show splash screen and wait for it to be closed
    // CreateSplashScreen();

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

    SolidScene testScene;
    testScene.CreateEmpty("TestScene");

    SolidProject testProject;
    testProject.SetProjectName("Test Project");
    testProject.SetProjectPath("Y:\\tmp\\TestProject");
    testProject.SetActiveScene(&testScene);

    SolidEditor::GetInstance()->SetEditorConfig(editorConfig);
    SolidEditor::GetInstance()->SetProject(testProject);
    SolidEditor::GetInstance()->Run();

    return 0;
}