#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SolidProfiler {
    namespace GPU {
        std::string GetVendor();
        std::string GetRenderer();
        std::tuple<float, float, float> GetMemoryUsage();
    }
}