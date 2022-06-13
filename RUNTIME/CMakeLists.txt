cmake_minimum_required(VERSION 3.23)

project(MatterRT VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DBUILD_MATTER_RT_DLL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /DBUILD_MATTER_RT_DLL")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_library(MatterRT SHARED src/Core.cpp)

set_target_properties(MatterRT PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(MatterRT PROPERTIES PUBLIC_HEADER include/MatterRT/Matter.hpp)