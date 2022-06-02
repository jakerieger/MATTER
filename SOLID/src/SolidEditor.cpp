#include "SolidEditor.hpp"

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

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return INIT_RESULT_FAILURE;
    }

    return INIT_RESULT_SUCCESS;
}

int SolidEditor::InitOpenGL() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);

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
}

void SolidEditor::Render() {
    while (!glfwWindowShouldClose(mWindow)) {
        ProcessInput();

        glClearColor(
            CLEAR_COLOR_R / 255.0f,
            CLEAR_COLOR_G / 255.0f,
            CLEAR_COLOR_B / 255.0f,
            1.0f
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void SolidEditor::Shutdown() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void SolidEditor::Run() {
    Init();
    Render();
    Shutdown();
}