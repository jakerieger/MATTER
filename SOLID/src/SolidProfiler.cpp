#include "SolidProfiler.hpp"

std::string SolidProfiler::GPU::GetVendor() {
    const unsigned char *vendor = glGetString(GL_VENDOR);
    return std::string((const char*)vendor);
}

std::string SolidProfiler::GPU::GetRenderer() {
    const unsigned char *renderer = glGetString(GL_RENDERER);
    return std::string((const char*)renderer);
}

std::tuple<float, float, float> SolidProfiler::GPU::GetMemoryUsage() {
    float totalMemory = 0.0f;
    float usedMemory = 0.0f;
    float freeMemory = 0.0f;

    glGetFloatv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemory);
    glGetFloatv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &usedMemory);
    glGetFloatv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &freeMemory);

    return std::make_tuple(totalMemory, usedMemory, freeMemory);
}