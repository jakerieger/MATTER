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