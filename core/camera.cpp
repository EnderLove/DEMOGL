#include "camera.h"
#include "math3D.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>

Camera::Camera(float scrWidth, float scrHeight, float zNear, float zFar, cpm::Vec3f position, cpm::Vec3f up, float yaw, float pitch) : Front_(cpm::Vec3f(0.0f, 0.0f, -1.0f)), MovementSpeed_(SPEED), MouseSensitivity_(SENSITIVITY), Fov_(FOV){
    Position_ = position;
    WorldUp_  = up;
    Yaw_      = yaw;
    Pitch_    = pitch;
    scrHeight_ = scrHeight;
    scrWidth_  = scrWidth;
    zFar_ = zFar;
    zNear_ = zNear;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front_(cpm::Vec3f(0.0f, 0.0f, -1.0f)), MovementSpeed_(SPEED), MouseSensitivity_(SENSITIVITY), Fov_(FOV){
    Position_ = cpm::Vec3f(posX, posY, posZ);
    WorldUp_  = cpm::Vec3f(upX, upY, upZ);
    Yaw_      = yaw;
    Pitch_    = pitch;
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
cpm::Mat4 Camera::GetViewMatrix() const { return cpm::LookAt(Position_, Position_ + Front_, Up_); }
cpm::Mat4 Camera::GetProjMatrix() const { return cpm::PerspectiveOpenGL(Fov_, (float)scrWidth_ / (float)scrHeight_, zNear_, zFar_); }
cpm::Mat4 Camera::GetTopViewMatrix() const { return cpm::LookAt(Position_, Position_ + Front_, cpm::Vec3f(0.0f, 0.0f, 1.0f)); }

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
    float velocity = MovementSpeed_ * deltaTime;
    if (direction == FORWARD)
        Position_ += Front_ * velocity;
    if (direction == BACKWARD)
        Position_ -= Front_ * velocity;
    if (direction == LEFT)
        Position_ -= Right_ * velocity;
    if (direction == RIGHT)
        Position_ += Right_ * velocity;

    //Position.y = 3;
}

void Camera::processController(const float *axes, float deltaTime, float xOffset, float yOffset){
    //TODO: ADD ANSI SCAPE CODES TO SHOW CONSTANT OUTPUT IN TERMINAL 
    //printf("LEFT  STICK X AXIS %f\n", axes[0]);
    //printf("LEFT  STICK Y AXIS %f\n", axes[1]);
    //printf("RIGHT STICK X AXIS %f\n", axes[2]);
    //printf("RIGHT STICK Y AXIS %f\n", axes[4]);

    const float cameraSpeed = deltaTime * 10.0f;

    // CAMERA MOVEMENT 
    //
    if (!(axes[1] < 0.5f && axes[1] > -0.5f)){
        if (axes[1] > 0.5f) Position_ -= Front_ * (cameraSpeed * axes[1]); 
        if (axes[1] < 0.5f) Position_ += Front_ * (cameraSpeed * abs(axes[1])); 
    }
    if (!(axes[0] < 0.5f && axes[0] > -0.5f)){
        if (axes[0] > 0.5f) Position_ += cpm::Normalize(cpm::Cross(Front_, Up_)) * (cameraSpeed * axes[0]); 
        if (axes[0] < 0.5f) Position_ -= cpm::Normalize(cpm::Cross(Front_, Up_)) * (cameraSpeed * abs(axes[0])); 
    } 

    // CAMERA VIEW MOVEMENT
    xOffset *= SENSITIVITY * 2;
    yOffset *= SENSITIVITY * 2;
    Yaw_   += xOffset;
    Pitch_ += yOffset;

    if (Pitch_ >  89.0f) Pitch_ =  89.0f;
    if (Pitch_ < -89.0f) Pitch_ = -89.0f;
    
    //Position.y = 0.0f; // STAY AT XZ LEVEL
    updateCameraVectors();
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch){
    xoffset *= MouseSensitivity_;
    yoffset *= MouseSensitivity_;

    Yaw_   += xoffset;
    Pitch_ += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch){
        if (Pitch_ > 89.0f)
            Pitch_ = 89.0f;
        if (Pitch_ < -89.0f)
            Pitch_ = -89.0f;
    }
    // update Front, Right and Up Vectors using the updated Euler angles
    
    //printf("YAW: %f || PITCH: %f\n", Yaw_, Pitch_);

    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset){
    Fov_ -= (float)yoffset;
    if (Fov_ < 1.0f)
        Fov_ = 1.0f;
    if (Fov_ > 45.0f)
        Fov_ = 45.0f;
}

// AIM MODE WITH CONTROLLER
void Camera::triggerAimViewFov(const float *controllerAxes){
    if(controllerAxes[2] >=  -1.0f){
        Fov_ -= ((float)controllerAxes[2]) * 3;
        if (Fov_ < 20.0f) Fov_ = 20.0f;
        if (Fov_ > 45.0f) Fov_ = 45.0f;
    }
}

void Camera::updateCameraVectors(){
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(cpm::ToRadian(Yaw_)) * cos(cpm::ToRadian(Pitch_));
    front.y = sin(cpm::ToRadian(Pitch_));
    front.z = sin(cpm::ToRadian(Yaw_)) * cos(cpm::ToRadian(Pitch_));
    Front_ = cpm::Normalize(front);
    // re-calculate the Right and Up vector
    Right_ = cpm::Normalize(cpm::Cross(Front_, WorldUp_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up_    = cpm::Normalize(cpm::Cross(Right_, Front_));
}
