cmake_minimum_required(VERSION 3.21)

project(project_momentum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

add_executable(project_momentum main.cpp)

target_include_directories(project_momentum
    PRIVATE ./
)
    
target_link_libraries(project_momentum PRIVATE application)
    
add_library(application STATIC application.cpp)

target_include_directories(application 
    PUBLIC ./
)

target_link_libraries(application PUBLIC raylib input_manager)

add_library(input_manager STATIC input_manager.cpp)

target_include_directories(input_manager
    PUBLIC ./
)

target_link_libraries(input_manager PUBLIC raylib)