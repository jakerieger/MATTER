#include "SolidEditor.hpp"
#include "SolidUI.hpp"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define WINDOW_TITLE "SOLID <OpenGL 4.6> | "
#define CLEAR_COLOR_R 36
#define CLEAR_COLOR_G 40
#define CLEAR_COLOR_B 58

int SolidEditor::InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (mWindow == nullptr) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return INIT_RESULT_FAILURE;
    }

    glfwMakeContextCurrent(mWindow);

    // Setup GLFW callbacls
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // VSYNC
    glfwSwapInterval(0);

    mLogger.Log("GLFW initialized", "", __FILE__, (int*)__LINE__, LogLevel::INFO);

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return INIT_RESULT_FAILURE;
    }

    mLogger.Log("GLAD initialized", "", __FILE__, (int*)__LINE__, LogLevel::INFO);

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitOpenGL() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    mLogger.Log("OpenGL initialized", "", __FILE__, (int*)__LINE__, LogLevel::INFO);

    return INIT_RESULT_SUCCESS;
}

void SolidEditor::ProcessInput() {

}

void SolidEditor::Init() {
    int INIT_RESULT = 0;

    INIT_RESULT = InitGLFW();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    INIT_RESULT = InitGlad();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    INIT_RESULT = InitOpenGL();
    if (INIT_RESULT == INIT_RESULT_FAILURE) { return; }

    mLogger.Log("Editor initialized", "", __FILE__, (int*)__LINE__, LogLevel::INFO);
    mLogger.Log("Warning test", "", __FILE__, (int*)__LINE__, LogLevel::WARNING);
    mLogger.Log("Error test", "", __FILE__, (int*)__LINE__, LogLevel::ERROR);
    mLogger.Log("Fatal test", "", __FILE__, (int*)__LINE__, LogLevel::FATAL);

    SolidUI::InitUI(mWindow);
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

    mLogger.Log("Created render buffers", "", __FILE__, (int*)__LINE__, LogLevel::INFO);

    return std::make_tuple(framebuffer, sceneTextureBuffer);
}

void SolidEditor::CheckFramebufferStatus() {
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        mLogger.Log("Framebuffer is not complete", "", __FILE__, (int*)__LINE__, LogLevel::ERROR);

    if (fboStatus == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        mLogger.Log("Framebuffer is incomplete attachment", "", __FILE__, (int*)__LINE__, LogLevel::ERROR);

    if (fboStatus == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        mLogger.Log("Framebuffer is incomplete missing attachment", "", __FILE__, (int*)__LINE__, LogLevel::ERROR);

    if (fboStatus == GL_FRAMEBUFFER_UNSUPPORTED)
        mLogger.Log("Framebuffer is unsupported", "", __FILE__, (int*)__LINE__, LogLevel::ERROR);
}

void SolidEditor::Render() {
    std::tuple<unsigned int, unsigned int> renderBuffers = CreateRenderBuffers();
    unsigned int framebuffer = std::get<0>(renderBuffers);
    unsigned int sceneTexture = std::get<1>(renderBuffers);

    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
        ProcessInput();

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);
        SolidUI::DrawUI(sceneTexture, mLogger);

        glClearColor(
            CLEAR_COLOR_R / 255.0f,
            CLEAR_COLOR_G / 255.0f,
            CLEAR_COLOR_B / 255.0f,
            1.0f
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        SolidUI::RenderUI();

        glfwSwapBuffers(mWindow);
    }
}

void SolidEditor::Shutdown() {
    SolidUI::ShutdownUI();
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void SolidEditor::Run() {
    Init();
    Render();
    Shutdown();
}