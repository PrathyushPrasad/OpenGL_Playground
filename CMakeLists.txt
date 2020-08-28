cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(PROJECT_NAME "OpenGL_Playground")
project(${PROJECT_NAME})

enable_language(C)
enable_language(CXX)

set(CMAKE_SUPPRESS_REGENERATION true)
set(DCMAKE_GENERATOR_PLATFORM "x64")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

# ---------------------------
# Add Subprojects Directories
# ---------------------------
add_subdirectory(Example_01_Creating_OpenGL_glfw_window)

