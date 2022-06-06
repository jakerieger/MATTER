#pragma once

#define INIT_RESULT_SUCCESS 0
#define INIT_RESULT_FAILURE 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SolidEditorConfig.hpp"
#include "SolidProject.hpp"
#include "SolidLogger.hpp"
#include "SolidEditorGrid.hpp"

/**
 * @brief The SolidEditor class is the main class of the Solid Editor.
 * 
 * It is responsible for initializing the editor and the OpenGL context.
 * It also handles the main loop of the editor.
 * 
 * @author Jake Rieger
 */
class SolidEditor {
public:
    /**
     * @brief Initializes the editor and runs the main loop, terminating and cleaning up when the editor is closed.
     */
    void Run();

    /**
     * @brief Sets the editor configuration.
     * 
     * @param config The editor configuration struct.
     */
    void SetEditorConfig(SolidEditorConfig editorConfig) { mEditorConfig = std::move(editorConfig); };

    /**
     * @brief Gets the editor configuration.
     * 
     * @return SolidEditorConfig The editor configuration struct.
     */
    SolidEditorConfig GetEditorConfig() { return mEditorConfig; };

    /**
     * @brief Sets the current project.
     * 
     * @return SolidProject The project class.
     */
    void SetProject(SolidProject project) { mProject = std::move(project); };

    /**
     * @brief Gets the current project.
     * 
     * @return SolidProject The project class.
     */
    SolidProject GetProject() { return mProject; };

private:
    /**
     * @brief Initializes GLFW.
     * 
     * @return int The initialization result.
     */
    int InitGLFW();

    /**
     * @brief Initializes GLAD.
     * 
     * @return int The initialization result.
     */
    int InitGlad();

    /**
     * @brief Initializes OpenGL.
     * 
     * @return int The initialization result.
     */
    int InitOpenGL();


    /**
     * @brief Processes input during the main loop.
     */
    void ProcessInput();

    /**
     * @brief Creates the frame and render buffers that get passed to the UI for rendering.
     */
    std::tuple<unsigned int, unsigned int> CreateRenderBuffers();

    /**
     * @brief Checks that the frame and render buffers are valid.
     */
    void CheckFramebufferStatus();

    /**
     * @brief Calls InitGLFW(), InitGlad(), and InitOpenGL().
     */
    void Init();

    /**
     * @brief The main loop of the editor.
     */
    void Render();

    /**
     * @brief Shuts the editor down and cleans up.
     */
    void Shutdown();

    /**
     * @brief The GLFW window
     */
    GLFWwindow* mWindow;

    /**
     * @brief The editor configuration struct.
     */
    SolidEditorConfig mEditorConfig;

    /**
     * @brief The project class.
     */
    SolidProject mProject;

    /**
     * @brief The logging class.
     */
    SolidLogger mLogger;

    SolidEditorGrid mEditorGrid;

    bool mFirstMouse = false;
    float mLastX = 0.0f;
    float mLastY = 0.0f;

    void UpdateWindowTitle();
};