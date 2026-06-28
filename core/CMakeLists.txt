# Bundle ONLY your custom engine classes
add_library(DemoglCore STATIC
    #src/shader.cpp
    #src/camera.cpp
    #src/model.cpp
    #src/mesh.cpp
    initGlfw.cpp
    basicCamera.cpp
    utils.cpp
    math3D.h
)

# Include your own headers
target_include_directories(DemoglCore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Debugging Power-Ups
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(DemoglCore PUBLIC -g -O0 -fsanitize=address)
    target_link_libraries(DemoglCore PUBLIC -fsanitize=address)
endif()

# Link the Vendor library (ImGui/Glad) AND the system libraries (GL/Assimp)
target_link_libraries(DemoglCore PUBLIC
    DemoglVendor
    ${CMAKE_THREAD_LIBS_INIT} 
    GL 
    assimp
)
