cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SOLID VERSION 0.1.0)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set(CMAKE_PREFIX_PATH Y:/vcpkg/installed/x64-windows)
find_package(msgpack REQUIRED)

set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_CURRENT_SOURCE_DIR}/appres.rc)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/include
    ${PROJECT_SOURCE_DIR}/../EXTERNAL/src
)

add_executable(
    SOLID
    src/main.cpp
    src/SolidEditor.cpp
    src/SolidProject.cpp
    src/SolidEditorConfig.cpp
    src/SolidLogger.cpp
    src/SolidProfiler.cpp
    src/SolidShader.cpp
    src/SolidEditorGrid.cpp
    src/SolidMeshRenderer.cpp
    src/SolidGameObject.cpp
    src/SolidScene.cpp
    src/SolidTransform.cpp
    src/SolidMaterial.cpp
    src/SolidColor.cpp
    src/SolidModel.cpp
    src/Windows/SplashScreen.cpp
    src/Windows/Dialogs.cpp
    include/SolidEditor.hpp
    include/SolidEditorConfig.hpp
    include/SolidProject.hpp
    include/SolidTransform.hpp
    include/SolidUI.hpp
    include/SolidUtils.hpp
    include/SolidLogger.hpp
    include/SolidProfiler.hpp
    include/SolidShader.hpp
    include/SolidEditorGrid.hpp
    include/SolidSceneCamera.hpp
    include/SolidMeshRenderer.hpp
    include/SolidCamera.hpp
    include/SolidComponent.hpp
    include/SolidLight.hpp
    include/SolidUIComponents.hpp
    include/SolidMaterial.hpp
    include/SolidColor.hpp
    include/SolidModel.hpp
    include/Windows/SplashScreen.hpp
    include/Windows/Dialogs.hpp
    ../EXTERNAL/src/glad.c
    ../EXTERNAL/src/stb_image.cpp
    ../EXTERNAL/src/imgui/imgui.cpp
    ../EXTERNAL/src/imgui/imgui_draw.cpp
    ../EXTERNAL/src/imgui/imgui_impl_glfw.cpp
    ../EXTERNAL/src/imgui/imgui_impl_opengl3.cpp
    ../EXTERNAL/src/imgui/imgui_tables.cpp
    ../EXTERNAL/src/imgui/imgui_widgets.cpp
    ../EXTERNAL/src/pugixml.cpp
    ../EXTERNAL/src/Str.cpp
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(SOLID debug ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Debug/glfw3.lib
                            optimized ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/glfw3.lib)

target_link_libraries(SOLID debug ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Debug/assimp-vc143-mtd.lib
                            optimized ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/assimp-vc143-mt.lib)

target_link_libraries(SOLID ${PROJECT_SOURCE_DIR}/../EXTERNAL/lib/Release/mono-2.0-sgen.lib)

target_link_libraries(SOLID msgpackc-cxx)