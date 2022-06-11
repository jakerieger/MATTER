#include <Windows/SplashScreen.hpp>
#include <stdio.h>
#include <SolidUtils.hpp>
#include <SolidShader.hpp>
#include <SolidPrimitive.hpp>

GLFWwindow* window;

void CreateSplashScreen() {
    // Create window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);

    window = glfwCreateWindow(SPLASH_WINDOW_WIDTH, SPLASH_WINDOW_HEIGHT, "", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    int screenWidth, screenHeight;
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    glfwSetWindowPos(window, (screenWidth - SPLASH_WINDOW_WIDTH) / 2, (screenHeight - SPLASH_WINDOW_HEIGHT) / 2);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return;
    }

    // Initialize OpenGL
    glViewport(0, 0, SPLASH_WINDOW_WIDTH, SPLASH_WINDOW_HEIGHT);

    stbi_set_flip_vertically_on_load(true);

    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int splashImage = SolidUtils::LoadTexture(
        (SolidUtils::GetResourcesPath() + "\\interface\\splash.jpg").c_str()
    );

    SolidShader shader(
        (SolidUtils::GetEditorShadersPath() + "\\editor\\Splash.shader").c_str()
    );

    shader.Use();
    shader.setInt("splashTexture", 0);

    float startTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, splashImage);

        shader.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, SolidPrimitive::Quad.indices.size(), GL_UNSIGNED_INT, 0);

        float currentTime = glfwGetTime();
        if (currentTime - startTime > 2.0f) {
            break;
        }
    }

    shader.Destroy();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &splashImage);

    glfwDestroyWindow(window);
    glfwTerminate();
}