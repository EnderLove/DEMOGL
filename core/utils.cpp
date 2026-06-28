#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "utils.h"

char* ReadBinaryFile(const char* fileName, int& size){
    FILE* f = fopen(fileName, "rb");
    
    if (!f){
        printf("Error opening '%s'", fileName); 
        exit(0);
    }

    struct stat statBuf;
    int error = stat(fileName, &statBuf);

    if (error){
        printf("Error getting file stats: %s\n", strerror(errno));
        return NULL;
    }

    size = statBuf.st_size;
    char* p = (char*)malloc(size);
    //assert(p);

    size_t bytesRead = fread(p, 1, size, f);

    if (bytesRead != size){
        printf("Read file eror file: %s\n", strerror(errno));
        exit(0);
    }

    fclose(f);
    return p;
}

void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam){
    GLuint ignore_ids[] = { 131185, 131218 }; // "will use video memory..."

    for (int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(ignore_ids) ; i++) {
        if (id == ignore_ids[i]) {
            return;
        }
    }

    printf("!!! Debug callback !!!\n");
    printf("Debug message: id %d, %s\n", id, message);

    printf("Message source: ");
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             printf("API\n"); break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Window System\n"); break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Shader Compiler\n"); break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Third Party\n"); break;
    case GL_DEBUG_SOURCE_APPLICATION:     printf("Application\n"); break;
    case GL_DEBUG_SOURCE_OTHER:           printf("Other\n"); break;
    }

    printf("Error type: ");
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               printf("Error\n"); break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Deprecated Behaviour\n"); break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Undefined Behaviour\n"); break;
    case GL_DEBUG_TYPE_PORTABILITY:         printf("Portability\n"); break;
    case GL_DEBUG_TYPE_PERFORMANCE:         printf("Performance\n"); break;
    case GL_DEBUG_TYPE_MARKER:              printf("Marker\n"); break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Push Group\n"); break;
    case GL_DEBUG_TYPE_POP_GROUP:           printf("Pop Group\n"); break;
    case GL_DEBUG_TYPE_OTHER:               printf("Other\n"); break;
    }

    printf("Severity: ");
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         printf("High\n"); break;
    case GL_DEBUG_SEVERITY_MEDIUM:       printf("Medium\n"); break;
    case GL_DEBUG_SEVERITY_LOW:          printf("Low\n"); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Notification\n"); break;
    }
}
