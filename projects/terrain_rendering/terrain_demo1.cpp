#include <GL/gl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../vendor/glad/glad.h"

#include "../../core/utils.h"
#include "../../core/basic_glfw_camera.h"
#include "../../core/initGlfw.h"

#define WINDOW_WIDTH 16 * 10
#define WINDOW_HEIGHT 9 * 10

class TerrainDemo1{
private:
    GLFWwindow* window = NULL;
    BasicCamera* gameCamera_ = NULL;
    bool isWireframe_ = false;

public:
    TerrainDemo1(){}

    virtual ~TerrainDemo1(){ delete gameCamera_; }
    
    void Init(){
        CreateWindow();
        InitCallbacks();
        InitCamera();
        //InitTerrain();
    }

    void Run(){
        while (!glfwWindowShouldClose(window)){
            RenderScene();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void RenderScene(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        terrain_.Render(gameCamera_);
    }

    void PassiveMouseCB(int x, int y){ gameCamera_->OnMouse(x, y); }

    void KeyboardCB(u_int key, int state){
        if (state == GLFW_PRESS){
            switch (key){
                case GLFW_KEY_ESCAPE:
                case GLFW_KEY_Q:
                    glfwDestroyWindow(window)
                    glfwTerminate();
                    exit(0);

                case GLFW_KEY_C:
                    gameCamera_->Print();
                    break;

                case GLFW_KEY_W:
                    isWireframe_ = !isWireframe_;
                   
                    if (isWireframe_) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;

            }
        }
        gameCamera_->OnKeyboard(key);
    }

    void MouseCB(int button, int action, int x, int y){}

private:
    void CreateWindow(){
        int majorVer = 0;
        int minorVer = 0;
        bool isFullScreen = false;
        window = glfw_init(majorVer, minorVer, WINDOW_WIDTH, WINDOW_HEIGHT, isFullScreen, "Terrain Rendering - Demo");
        glfwGetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );
    }

    void InitCallbacks(){
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    void InitCamera(){
        Vector3f Pos(100.0f, 220.0f, -400.0f);
        Vector2f Target(0.0f, -0.25f, 1.0f);
        Vector3f Up(0.0f, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 0.1f;
        float zFar = 2000.0f;

        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };
        gameCamera_ = new BasicCamera(persProjInfo, Pos, Target, Up);
    }
};

TerrainDemo1* app = NULL;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    app->KeyboardCB(key, action);
}
static void CursorPosCallback(GLFWwindow* window, double x, double y){
    app->PassiveMouseCB((int)x, (int)y);
}
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    app->MouseCB(Button, Action, (int)x, (int)y);
}

int main(int argc, char** argv){
    app = new TerrainDemo1();
    app->Init();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    app->Run();

    delete app;
    return 0;
}
