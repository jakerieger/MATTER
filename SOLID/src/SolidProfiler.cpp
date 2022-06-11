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

std::tuple<size_t, size_t> SolidProfiler::Process::GetProcessMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    size_t virtualMemUsage = pmc.PrivateUsage;
    size_t physMemUsage = pmc.WorkingSetSize;

    return std::make_tuple(virtualMemUsage, physMemUsage);
}

double SolidProfiler::Process::GetProcessCPUUsage() {
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    SolidProfiler::Process::numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&SolidProfiler::Process::lastCPU, &ftime, sizeof(FILETIME));

    SolidProfiler::Process::self = GetCurrentProcess();
    GetProcessTimes(SolidProfiler::Process::self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&SolidProfiler::Process::lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&SolidProfiler::Process::lastUserCPU, &fuser, sizeof(FILETIME));

    ULARGE_INTEGER now, sys, user;
    double percent;
    memcpy(&now, &ftime, sizeof(FILETIME));

    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - SolidProfiler::Process::lastSysCPU.QuadPart) + (user.QuadPart - SolidProfiler::Process::lastUserCPU.QuadPart);
    percent /= (now.QuadPart - SolidProfiler::Process::lastCPU.QuadPart);
    percent /= SolidProfiler::Process::numProcessors;
    SolidProfiler::Process::lastCPU = now;
    SolidProfiler::Process::lastUserCPU = user;
    SolidProfiler::Process::lastSysCPU = sys;

    return percent * 100;
}