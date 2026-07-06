#include <stdio.h>
#include <string.h>
#include <math.h>

#include <imgui.h>

#include "basicCamera.h"
#include "camera.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "initGlfw.h"

#include "terrain.h"
#include "fault_formation.h"

static int WINDOW_WIDTH = 16 * 100;
static int WINDOW_HEIGHT = 9 * 100;

float lastX = 0.0f;
float lastY = 0.0f;

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);
 
class TerrainDemo1{
private:
    GLFWwindow* window = NULL;
    BasicCamera* gameCamera_ = NULL;
    Camera* testCamera_ = NULL;
    bool isWireframe_ = false;
    //BaseTerrain terrain_;
    FaultFormation terrain_;

    // CONTROL 
    bool editMode = false;

public:
    TerrainDemo1(){}

    virtual ~TerrainDemo1(){ delete gameCamera_; }
    
    void Init(){
        CreateWindow();
        InitCallbacks();
        InitCamera();
        InitTerrain();
        InitGUI();
    }

    void Run(){
        while (!glfwWindowShouldClose(window)){
            //RenderScene();
            //glfwSwapBuffers(window);
            //glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            static int   Iterations = 100;
            static float MaxHeight  = 200.0f;
            static float Filter     = 0.2f;
                
            ImGui::Begin("Generation Variables");

            ImGui::SliderInt("Iterations", &Iterations, 0, 1000);
            ImGui::SliderFloat("MaxHeight", &MaxHeight, 0.0f, 1000.0f);
            ImGui::SliderFloat("Filter", &Filter, 0.0f, 1.0f);

            if (ImGui::Button("Generate")) {
                terrain_.Destroy();
                int Size = 256;
                float MinHeight = 0.0f;
                terrain_.CreateFaultFormation(Size, Iterations, MinHeight, MaxHeight, Filter);
            }
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

            RenderScene(); // SCENE RENDER
            
            ImGui::Render();
            //int display_w, display_h;
            //glfwGetFramebufferSize(window, &display_w, &display_h);
            //glViewport(0, 0, display_w, display_h);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void RenderScene(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //terrain_.Render(*gameCamera_);
        terrain_.Render(*testCamera_);
    }

    void PassiveMouseCB(int x, int y){ 
        float xOffset = x - lastX;
        float yOffset = lastY - y;
        lastX = x;
        lastY = y;

        if (!editMode) testCamera_->ProcessMouseMovement(xOffset, yOffset);
        //gameCamera_->OnMouse(x, y); 
    }

    void KeyboardCB(u_int key, int state){
        if (state == GLFW_PRESS){
            switch (key){
                case GLFW_KEY_ESCAPE:
                case GLFW_KEY_Q:
                    glfwDestroyWindow(window);
                    glfwTerminate();
                    exit(0);

                case GLFW_KEY_C:
                    //gameCamera_->Print();
                    break;

                case GLFW_KEY_M:
                    isWireframe_ = !isWireframe_;
                   
                    if (isWireframe_) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;

                case GLFW_KEY_1: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); editMode = false;  break;
                case GLFW_KEY_2: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   editMode = true; break;

            }
        }
        //gameCamera_->OnKeyboard(key);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) testCamera_->ProcessKeyboard(FORWARD , 0.16);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) testCamera_->ProcessKeyboard(BACKWARD, 0.16);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) testCamera_->ProcessKeyboard(LEFT    , 0.16);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) testCamera_->ProcessKeyboard(RIGHT   , 0.16);
    }

    void MouseCB(int button, int action, int x, int y){}

private:
    void CreateWindow(){
        int majorVer = 0;
        int minorVer = 0;
        bool isFullScreen = false;
        window = core::glfwInit(majorVer, minorVer, WINDOW_WIDTH, WINDOW_HEIGHT, isFullScreen, "Terrain Rendering - Demo");
        glfwSetCursorPos(window, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f );
    }

    void InitCallbacks(){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    void InitCamera(){
        //cpm::Vec3f Pos(100.0f, 220.0f, -400.0f);
        cpm::Vec3f Pos(0.0f, 200.0f, -200.0f);
        cpm::Vec3f Target(0.0f, -0.25f, 1.0f);
        cpm::Vec3f Up(0.0f, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 0.1f;
        float zFar = 2000.0f;
        cpm::PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };
        //gameCamera_ = new BasicCamera(persProjInfo, Pos, Target, Up);
        testCamera_ = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar,Pos);
    }

    void InitTerrain(){ 
        float worldScale = 1.0f;
        terrain_.InitTerrain(worldScale);
        //terrain_.LoadFromFile("../../../projects/terrain_rendering/heightmap.save"); 
        
        int size = 512;
        int iterations = 100;
        float minHeight = 0.0f;
        float maxHeight = 100.0f;
        float filter = 0.8f;

        terrain_.CreateFaultFormation(size, iterations, minHeight, maxHeight, filter);
    }

    void InitGUI(){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
};

TerrainDemo1* app = NULL;

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    printf("RESIZE: %4d | %4d\n", width, height);
}
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
    //glFrontFace(GL_CW)
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    app->Run();

    delete app;
    return 0;
}
