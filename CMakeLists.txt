cmake_minimum_required(VERSION 3.21)

project(project_momentum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------------------------------------------------------------------------------------------------------------------



# INTERFACE FOR ALL THE HEADERS

# include/
add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(project_includes INTERFACE raylib)

#----------------------------------------------------------------------------------------------------------------------------------


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