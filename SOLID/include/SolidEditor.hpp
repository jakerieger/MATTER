#pragma once

#define INIT_RESULT_SUCCESS 0
#define INIT_RESULT_FAILURE 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SolidEditorConfig.hpp"
#include "SolidProject.hpp"

class SolidEditor {
public:
    void Run();

    void SetEditorConfig(SolidEditorConfig editorConfig) { mEditorConfig = editorConfig; };
    SolidEditorConfig GetEditorConfig() { return mEditorConfig; };

    void SetProject(SolidProject project) { mProject = project; };
    SolidProject GetProject() { return mProject; };

private:
    int InitGLFW();
    int InitGlad();
    int InitOpenGL();

    void ProcessInput();

    void Init();
    void Render();
    void Shutdown();

    SolidEditorConfig mEditorConfig;
    SolidProject mProject;
    GLFWwindow* mWindow;
};