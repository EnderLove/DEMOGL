add_library(DemoglVendor STATIC
    glad.c
    imgui/imgui.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
)

# Tell CMake where the third-party headers are, and make them PUBLIC
# so anything linking to DemoglVendor can #include them.
target_include_directories(DemoglVendor PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

# ImGui and Glad need GLFW and system libraries to compile
target_link_libraries(DemoglVendor PUBLIC 
    glfw 
    ${CMAKE_DL_LIBS}
)
