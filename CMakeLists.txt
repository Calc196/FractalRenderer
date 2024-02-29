# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the c++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name
project (FractalRenderer)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    FractalRenderer/Camera/Camera.cpp
    FractalRenderer/Graphics/Graphics.cpp
    FractalRenderer/Input/Input.cpp
    FractalRenderer/Render/Render.cpp
    FractalRenderer/Shader/Shader.cpp
    FractalRenderer/Window/Window.cpp
    FractalRenderer/main.cpp
)

# Find a boost install with the libraries filesystem and system
find_package(SDL2 REQUIRED CONFIG)
find_package(GLEW REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

# Add an executable with the above sources
add_executable(FractalRenderer ${SOURCES})

# Link against the external libraries
target_link_libraries(FractalRenderer
    PRIVATE 
        SDL2::SDL2
        GLEW::glew
        glm::glm
)