#include "Hub.hpp"
#include "HubUI.hpp"

#include <filesystem>
namespace fs = std::filesystem;

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

std::shared_ptr<Hub> Hub::GetInstance() {
    static std::shared_ptr<Hub> instance(new Hub);
    return instance;
}

void Hub::Init() {
    auto appdata = fs::temp_directory_path().parent_path().parent_path() / "MatterHub";
    dataPath = appdata.string();

    auto logs = appdata / "logs";
    auto cache = appdata / "cache"; 
    auto templates = appdata / "templates";
    auto update = appdata / "update";

    if (!fs::exists(appdata)) {
        fs::create_directory(appdata);
        fs::create_directory(logs);
        fs::create_directory(cache);
        fs::create_directory(templates);
        fs::create_directory(update);

        JSON projects;
        projects["projects"] = JSON::array();
        std::ofstream projectsFileStream(appdata / "projects.json");
        projectsFileStream << projects;
        projectsFileStream.close();

        JSON settings;
        settings["settings"] = JSON::object();
        std::ofstream settingsFileStream(appdata / "settings.json");
        settingsFileStream << settings;
        settingsFileStream.close();
    } else {
        // Load projects
        JSON projectsJson;
        std::ifstream projectsFileStream(appdata / "projects.json");
        projectsFileStream >> projectsJson;
        projectsFileStream.close();

        for (auto& project : projectsJson["projects"]) {
            try {
                Project p;
                p.name = project["name"].get<std::string>();
                p.path = project["path"].get<std::string>();
                p.favorite = project["favorite"].get<bool>();
                p.last_modified = static_cast<time_t>(project["last_modified"].get<std::uint64_t>());
                p.editor_version = project["editor_version"].get<std::string>();
                projects.push_back(p);
            } catch (nlohmann::detail::exception e) {
                printf("Error: %s\n", e.what());
            }
        }

        printf("Found %d projects\n", (int)projects.size());
    }
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

    GLFWimage icon;
    std::string iconPath = SolidUtils::GetResourcesPath() + "\\interface\\icons\\hub_icon.png";
    icon.pixels = stbi_load(iconPath.c_str(), &icon.width, &icon.height, nullptr, STBI_rgb_alpha);
    glfwSetWindowIcon(window, 1, &icon);
    stbi_image_free(icon.pixels);

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