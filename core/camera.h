#ifndef CAMERA_H
#define CAMERA_H

#include "../vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <stdio.h>

#include "cameraAPI.h"
#include "math3D.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =   0.0f;
const float SPEED       =   8.5f;
const float SENSITIVITY =   0.1f;
const float FOV         =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera{
public:
    // camera Attributes
    cpm::Vec3f Position_;
    cpm::Vec3f Front_;
    cpm::Vec3f Up_;
    cpm::Vec3f Right_;
    cpm::Vec3f WorldUp_;
   
    // euler Angles
    float Yaw_;
    float Pitch_;

    // camera options
    float MovementSpeed_;
    float MouseSensitivity_;
    float Fov_;

    float scrWidth_;
    float scrHeight_;
    float zNear_;
    float zFar_;

    // constructor with vectors
    Camera(float scrWidth, float scrHeight, float zNear, float zFar, cpm::Vec3f position = cpm::Vec3f(0.0f, 0.0f, 0.0f), cpm::Vec3f up = cpm::Vec3f(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    cpm::Mat4 GetViewMatrix() const;
    cpm::Mat4 GetTopViewMatrix() const;
    cpm::Mat4 GetProjMatrix() const; 
   
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
    
    void processController(const float *axes, float deltaTime, float xOffset, float yOffset);
    void triggerAimViewFov(const float *controllerAxes);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
#endif
