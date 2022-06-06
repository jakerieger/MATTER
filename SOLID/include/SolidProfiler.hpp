#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief Profiling and engine internals for SOLID
 * 
 */
namespace SolidProfiler {
    /**
     * @brief Functions for getting information related to the GPU
     * 
     */
    namespace GPU {
        std::string GetVendor(); ///< Returns the GPU vendor, such as NVIDIA, AMD, etc.
        std::string GetRenderer(); ///< Returns the GPU renderer, such as GeForce GTX 1080, etc.
        std::tuple<float, float, float> GetMemoryUsage(); ///< Returns the GPU memory information in MB in the format (total, used, free)
    }
}