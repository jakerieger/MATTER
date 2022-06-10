/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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