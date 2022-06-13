#include "Hub.hpp"
#include "HubUI.hpp"

std::shared_ptr<Hub> Hub::GetInstance() {
    static std::shared_ptr<Hub> instance(new Hub);
    return instance;
}

void Hub::Run() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(900, 500, "Hub", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    glfwSetWindowTitle(window, "Matter Hub");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, 900, 500);

    HubUI::Init(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        HubUI::Draw();
        glClearColor(
            HubUI::GetColors()["panel"].x,
            HubUI::GetColors()["panel"].y,
            HubUI::GetColors()["panel"].z,
            1.0f
        );
        glClear(GL_COLOR_BUFFER_BIT);
        HubUI::Render();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}