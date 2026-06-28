#ifndef UTILS_H
#define UTILS_H

#include "glad.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <cstdint>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

char* ReadBinaryFile(const char* fileName, int& size);

// This handles all the debug output 
void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

#endif // UTILS_H!
