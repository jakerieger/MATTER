cmake_minimum_required(VERSION 3.23)

project(MatterHub VERSION 0.0.1)

if(MSVC)
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_CURRENT_SOURCE_DIR}/appres.rc)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/include
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/src
    ${PROJECT_SOURCE_DIR}/../SOLID/include
)

add_executable(MatterHub
    src/Hub.cpp
    src/main.cpp
    ../EXTERNAL/src/glad.c
    ../EXTERNAL/src/stb_image.cpp
    ../EXTERNAL/src/pugixml.cpp
    ../EXTERNAL/src/imgui/imgui_draw.cpp
    ../EXTERNAL/src/imgui/imgui_impl_glfw.cpp
    ../EXTERNAL/src/imgui/imgui_impl_opengl3.cpp
    ../EXTERNAL/src/imgui/imgui.cpp
    ../EXTERNAL/src/imgui/imgui_tables.cpp
    ../EXTERNAL/src/imgui/imgui_widgets.cpp
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(MatterHub debug ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Debug/glfw3.lib
                            optimized ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/glfw3.lib)