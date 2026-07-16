# CUSTOM ENGINE CLASSES
add_library(DemoglCore STATIC
    initGlfw.cpp
    basicCamera.cpp
    camera.cpp
    utils.cpp
    shader.cpp
)

# HEADERS
target_include_directories(DemoglCore PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# DEBUGGING FLAGS
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
