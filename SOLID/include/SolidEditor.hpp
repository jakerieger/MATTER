#pragma once

#define INIT_RESULT_SUCCESS 0
#define INIT_RESULT_FAILURE 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SolidEditorConfig.hpp"
#include "SolidProject.hpp"
#include "SolidLogger.hpp"

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
    std::tuple<unsigned int, unsigned int> CreateRenderBuffers();
    void CheckFramebufferStatus();

    void Init();
    void Render();
    void Shutdown();

    GLFWwindow* mWindow;
    SolidEditorConfig mEditorConfig;
    SolidProject mProject;
    SolidLogger mLogger;
};