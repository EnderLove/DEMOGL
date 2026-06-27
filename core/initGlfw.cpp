#include "utils.h"
#include <cstdlib>
#include "initGlfw.h"
//#include "glm_camera.h"

static int glMajorVersion = 0;
static int glMinorVersion = 0;

int GetGLMajorVersion(){ return glMajorVersion; }
int GetGLMinorVersion(){ return glMinorVersion; }

int IsGLVersionHigher(int MajorVer, int MinorVer){
    return ((glMajorVersion >= MajorVer) && (glMinorVersion >= MinorVer));
}

static void glfw_lib_init(){
    if (glfwInit() != 1){
        printf("Error initializing GLFW\n");
        exit(1);
    }

    int Major, Minor, Rev;
    glfwGetVersion(&Major, &Minor, &Rev);
}

static void EnableDebugOutput(){
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
}

static void InitGlad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Error initializing GLAD\n");
        exit(1);
    }
}

GLFWwindow* glfwInit(int majorVer, int minorVer, int width, int height, bool isFullScreen, const char* title){
    glfw_lib_init();

    GLFWmonitor* monitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    if (majorVer > 0) glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
    if (minorVer > 0) glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (!window){
        const char* Desc = NULL;
        int errorCode = glfwGetError(&Desc);
        exit(0);
    }

    glfwMakeContextCurrent(window);

    glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);

    if (majorVer > 0){
        if (majorVer != glMajorVersion){
            printf("Requested major version %d is not the same as created version %d", majorVer, glMajorVersion);
            exit(0);
        }
    }
    if (minorVer > 0){
        if (majorVer != glMinorVersion){
            printf("Requested major version %d is not the same as created version %d", majorVer, glMinorVersion);
            exit(0);
        }
    }

    InitGlad();
    EnableDebugOutput();
    glfwSwapInterval(1);
    return window;
}
