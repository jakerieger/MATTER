#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Hub {
public:
    Hub(Hub const&) = delete;
    Hub& operator=(Hub const&) = delete;
    static std::shared_ptr<Hub> GetInstance();

    void Run();

private:
    Hub() {}
};