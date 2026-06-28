cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(DemoglWorkspace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Finding system-wide Linux dependencies ONCE
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

#Building core & vendor library 
add_subdirectory(core)
add_subdirectory(vendor)

#Building demos
add_subdirectory(projects/terrain_rendering)
