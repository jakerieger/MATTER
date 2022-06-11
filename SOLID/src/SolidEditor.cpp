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

/*******************************************************************************
 * This file is the heart of the SOLID Editor.
 *
 * It is responsible for the following:
 * - Initializing OpenGL and the window it renders to
 * - Setting up framebuffers and textures to pass to the UI
 * - Creating the main render loop and rendering the UI and scene
 * - Handling user input
 * - Dispatching events to the UI
 * - Handling the UI's events
 * - Handling the scene's events
 * - Cleaning up buffers and shutting down OpenGL
 *
 * @note Callback functions are defined globally instead of as class members
 * because OpenGL takes a C-style pointer.
 ******************************************************************************/

#include "SolidEditor.hpp"
#include "SolidUI.hpp"
#include "SolidSceneCamera.hpp"
#include "SolidGameObject.hpp"
#include "SolidModel.hpp"
#include "SolidLight.hpp"
#include "SolidLogger.hpp"

// Define some default values for the editor to avoid taking up memory
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define WINDOW_TITLE "SOLID <OpenGL 4.6> | "
#define CLEAR_COLOR_R 36
#define CLEAR_COLOR_G 40
#define CLEAR_COLOR_B 58
#define VSYNC_ENABLED 1
#define VSYNC_DISABLED 0

//========================================================================//
//======================== GLOBAL CALLBACKS ==============================//
//========================================================================//

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void GLAPIENTRY MessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam
);

//========================================================================//
//========================================================================//
//========================================================================//

SolidSceneCamera sceneCamera(
    glm::vec3(0.0f, 1.0f, 4.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
);

int SolidEditor::InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

    mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (mWindow == nullptr) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return INIT_RESULT_FAILURE;
    }

    glfwMakeContextCurrent(mWindow);

    SetWindowIcon();

    // Setup GLFW callbacls
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // VSYNC
    glfwSwapInterval(VSYNC_DISABLED);

    SolidLogger::GetInstance()->Log("GLFW initialized", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return INIT_RESULT_FAILURE;
    }

    SolidLogger::GetInstance()->Log("GLAD initialized", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitOpenGL() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glEnable(GL_BLEND);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    SolidLogger::GetInstance()->Log("OpenGL initialized", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);

    return INIT_RESULT_SUCCESS;
}

void SolidEditor::ProcessInput() {
    if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        double dXpos, dYpos;
        glfwGetCursorPos(mWindow, &dXpos, &dYpos);

        float xpos = static_cast<float>(dXpos);
        float ypos = static_cast<float>(dYpos);

        if (mFirstMouse) {
            mLastX = xpos;
            mLastY = ypos;
            mFirstMouse = false;
        }

        float xoffset = xpos - mLastX;
        float yoffset = mLastY - ypos;

        mLastX = xpos;
        mLastY = ypos;

        int viewportX, viewportY;
        glfwGetWindowSize(mWindow, &viewportX, &viewportY);
        glm::vec2 viewport = glm::vec2(viewportX, viewportY);

        sceneCamera.ProcessMouseOrbit(-xoffset, yoffset, viewport);
    }
}

void SolidEditor::Init() {
    int INIT_RESULT = 0;

    INIT_RESULT = InitGLFW();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    INIT_RESULT = InitGlad();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    INIT_RESULT = InitOpenGL();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    SolidLogger::GetInstance()->Log("Editor initialized", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);

    SolidUI::InitUI(mWindow, mProject);
}

std::tuple<unsigned int, unsigned int> SolidEditor::CreateRenderBuffers() {
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    unsigned int sceneTextureBuffer;
    glGenTextures(1, &sceneTextureBuffer);
    glBindTexture(GL_TEXTURE_2D, sceneTextureBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTextureBuffer, 0);

    unsigned int renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

    CheckFramebufferStatus();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    SolidLogger::GetInstance()->Log("Created render buffers", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);

    return std::make_tuple(framebuffer, sceneTextureBuffer);
}

void SolidEditor::CheckFramebufferStatus() {
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        SolidLogger::GetInstance()->Log("Framebuffer is not complete", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_ERROR);

    if (fboStatus == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        SolidLogger::GetInstance()->Log("Framebuffer is incomplete attachment", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_ERROR);

    if (fboStatus == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        SolidLogger::GetInstance()->Log("Framebuffer is incomplete missing attachment", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_ERROR);

    if (fboStatus == GL_FRAMEBUFFER_UNSUPPORTED)
        SolidLogger::GetInstance()->Log("Framebuffer is unsupported", "", __FILE__, (int*)__LINE__, LogLevel::LogLevel_ERROR);
}

void SolidEditor::Render() {
    std::tuple<unsigned int, unsigned int> renderBuffers = CreateRenderBuffers();
    unsigned int framebuffer = std::get<0>(renderBuffers);
    unsigned int sceneTexture = std::get<1>(renderBuffers);

    //mEditorGrid.Init();

    SolidDirectionalLight sceneLight("Directional Light");
    sceneLight.mTransform.SetPositionAndRotation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mProject.GetActiveScene()->AddGameObject(&sceneLight);

    for (auto& gameObject : mProject.GetActiveScene()->GetGameObjects()) {
        gameObject->Start();
    }

    while (!glfwWindowShouldClose(mWindow)) {
        UpdateWindowTitle();
        glfwPollEvents();
        ProcessInput();

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);
        SolidUI::DrawUI(mWindow, sceneTexture, mProject);

        glClearColor(
            SolidUI::GetColors()["scene"].x,
            SolidUI::GetColors()["scene"].y,
            SolidUI::GetColors()["scene"].z,
            1.0f
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //mEditorGrid.Draw(sceneCamera);

        for (auto& gameObject : mProject.GetActiveScene()->GetGameObjects()) {
            gameObject->Update(sceneCamera);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        SolidUI::RenderUI();

        glfwSwapBuffers(mWindow);
    }
}

void SolidEditor::UpdateWindowTitle() {
    std::string title = std::string(WINDOW_TITLE) + std::string(mProject.GetProjectName()) + " - " + std::string(mProject.GetActiveScene()->GetSceneName());
    glfwSetWindowTitle(mWindow, title.c_str());
}

void SolidEditor::SetWindowIcon() {
    GLFWimage icon;
    std::string iconPath = SolidUtils::GetResourcesPath() + "\\interface\\icons\\win_icon.png";
    icon.pixels = stbi_load(iconPath.c_str(), &icon.width, &icon.height, nullptr, STBI_rgb_alpha);
    glfwSetWindowIcon(mWindow, 1, &icon);
    stbi_image_free(icon.pixels);
}

void SolidEditor::Shutdown() {
    //mEditorGrid.Destroy();
    SolidUI::ShutdownUI();
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void SolidEditor::Run() {
    Init();
    Render();
    Shutdown();
}

std::shared_ptr<SolidEditor> SolidEditor::GetInstance() {
    static std::shared_ptr<SolidEditor> instance{new SolidEditor};
    return instance;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "[GL CALLBACK]: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);

    if (type == GL_DEBUG_TYPE_ERROR) {
        SolidLogger::GetInstance()->Log("GL_ERROR", message, __FILE__, (int*)__LINE__, LogLevel::LogLevel_ERROR);
    } else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
        SolidLogger::GetInstance()->Log("GL_DEPRECATED_BEHAVIOR", message, __FILE__, (int*)__LINE__, LogLevel::LogLevel_WARNING);
    } else {
        SolidLogger::GetInstance()->Log("GL_CALLBACK", message, __FILE__, (int*)__LINE__, LogLevel::LogLevel_INFO);
    }
}