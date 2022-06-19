#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Project {
    std::string name;
    std::string path;
    bool favorite;
    time_t last_modified;
    std::string editor_version;
};

class Hub {
public:
    Hub(Hub const&) = delete;
    Hub& operator=(Hub const&) = delete;
    static std::shared_ptr<Hub> GetInstance();

    void Run();
    std::string dataPath;
    std::vector<Project> projects;

private:
    void Init();
    Hub() {
        Init();
    }
};