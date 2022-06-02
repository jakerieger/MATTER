#include "SolidEditor.hpp"

int SolidEditor::InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(800, 600, "Solid", NULL, NULL);

    if (mWindow == nullptr) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return INIT_RESULT_FAILURE;
    }

    glfwMakeContextCurrent(mWindow);

    // VSYNC
    glfwSwapInterval(1);

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
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    return INIT_RESULT_SUCCESS;
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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