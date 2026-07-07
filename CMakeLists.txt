cmake_minimum_required(VERSION 3.21)

project(project_momentum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------------------------------------------------------------------------------------------------------------------

# FETCH CONTENT

# raylib---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# nlohmann/json
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

#----------------------------------------------------------------------------------------------------------------------------------

# INTERFACE FOR ALL THE HEADERS

# include/
add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(project_includes INTERFACE raylib)

#----------------------------------------------------------------------------------------------------------------------------------

# STATIC LIBRARIES

# src/game/systems/---



# src/engine/core/---
add_library(core STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/core/input_manager.cpp
)


# src/engine/ecs/---
add_library(ecs STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entity_manager.cpp
)


#src/engine/systems/---
add_library(engine_systems STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/systems/physics_system.cpp
)
target_link_libraries(engine_systems PUBLIC ecs)

# PROVIDING INCLUDE PATHS FOR LIBRARIES

set(PROJECT_STATIC_LIBS
    core
    ecs
    engine_systems
)

foreach(lib IN LISTS PROJECT_STATIC_LIBS)
    target_link_libraries(${lib} PUBLIC project_includes)
endforeach()

#----------------------------------------------------------------------------------------------------------------------------------

# EXECUTABLES

# src/game/---
add_executable(main_client 
    src/game/main.cpp
    src/game/application.cpp
    src/game/entity_factory.cpp
)

target_link_libraries(main_client PRIVATE 
    project_includes
    core
    ecs
    engine_systems
)