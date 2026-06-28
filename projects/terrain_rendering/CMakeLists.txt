# Create your specific demo
add_executable(terrain_rendering terrain_demo1.cpp)

# Link your core library (this automatically pulls in Vendor, GL, glfw, assimp, etc.)
target_link_libraries(terrain_rendering PRIVATE DemoglCore)
