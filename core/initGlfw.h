#ifndef INIT_GLFW_H
#define INIT_GLFW_H

#include "../vendor/glad/glad.h"
#include <GLFW/glfw3.h>

GLFWwindow* glfw_init(int majorVer, int minorVer, int width, int height, bool isFullScreen, const char* title);

#endif // INIT_GLFW_H!
