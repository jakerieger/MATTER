cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SOLID VERSION 0.1.0)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/include
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/src
)

add_executable(SOLID src/main.cpp src/SolidEditor.cpp src/SolidProject.cpp ../EXTERNAL/src/glad.c ../EXTERNAL/src/stb_image.cpp)

target_link_libraries(SOLID debug ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Debug/glfw3.lib
                            optimized ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/glfw3.lib)

target_link_libraries(SOLID debug ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Debug/assimp-vc143-mtd.lib
                            optimized ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/assimp-vc143-mt.lib)