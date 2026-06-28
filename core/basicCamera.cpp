#include "../vendor/glad/glad.h"
#include "math3D.h"
#include <GLFW/glfw3.h>

#include "basicCamera.h"

static int MARGIN = 40;
static float EDGE_STEP = 0.5f;

BasicCamera::BasicCamera(int windowWidth, int windowHeight){
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;
    pos_    = Vec3f(0.0f, 0.0f, 0.0f);
    target_ = Vec3f(0.0f, 0.0f, 0.0f);
    up_     = Vec3f(0.0f, 0.0f, 0.0f);
    InitInternal();
}

BasicCamera::BasicCamera(const PersProjInfo& persProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up){
    InitCamera(persProjInfo, pos, target, up);
}
BasicCamera::BasicCamera(const OrthoProjInfo& orthoProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up){
    InitCamera(orthoProjInfo, pos, target, up);
}

void BasicCamera::InitCamera(const PersProjInfo& persProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up){
    persProjInfo_ = persProjInfo;
    projection_.PerspectiveOpenGL(persProjInfo.FOV, persProjInfo.Height/ persProjInfo.Width, persProjInfo.zNear, persProjInfo.zFar); // TODO: OVERLOAD THIS FUNCTION TO ACCEPT DIRECT PROJ_INFO
    windowWidth_  = (int)persProjInfo.Width;
    windowHeight_ = (int)persProjInfo.Height;
    pos_ = pos;
    
    target_ = target;
    target_.Normalize();
    
    up_ = up;
    up_.Normalize();

    InitInternal();
}

void BasicCamera::InitCamera(const OrthoProjInfo& orthoProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up){
    projection_.OrthoOpenGL(orthoProjInfo.left, orthoProjInfo.right, orthoProjInfo.bottom, orthoProjInfo.top, orthoProjInfo.zNear, orthoProjInfo.zFar);
    windowWidth_  = (int)orthoProjInfo.Width;
    windowHeight_ = (int)orthoProjInfo.Height;
    pos_ = pos;
    
    target_ = target;
    target_.Normalize();
    
    up_ = up;
    up_.Normalize();

    InitInternal();
}

void BasicCamera::InitInternal(){
    Vec3f HTarget(target_.x, 0.0f, target_.z);
    HTarget.Normalize();

    angleH_ = -ToDegree(atan2(target_.z, target_.x));
    angleV_ = -ToDegree(asin(target_.y));

    onUpperEdge_ = false;
    onLowerEdge_ = false;
    onLeftEdge_  = false;
    onRigthEdge_ = false;
    mousePos_.x = windowWidth_  / 2;
    mousePos_.y = windowHeight_ / 2;
}

void BasicCamera::SetPosition(float x, float y, float z){ pos_.x = x, pos_.y = y; pos_.z = z; InitInternal(); }
void BasicCamera::SetPosition(const Vec3f& pos){ SetPosition(pos.x, pos.y, pos.z); }

void BasicCamera::SetTarget(float x, float y, float z){ target_.x = x; target_.y = y; target_.z = z; InitInternal(); }
void BasicCamera::SetTarget(const Vec3f& target){ SetTarget(target.x, target.y, target.z); }

bool BasicCamera::OnKeyboard(int key){
    bool cameraChangedPos = false;

    switch (key){
        case GLFW_KEY_W:
            pos_ += (target_ * speed_);
            cameraChangedPos = true;
            break;

        case GLFW_KEY_S:
            pos_ -= (target_ * speed_);
            cameraChangedPos = true;
            break;

        case GLFW_KEY_A:{
                Vec3f left = target_.Cross(up_);
                left.Normalize();
                left *= speed_;
                pos_ += left;
                cameraChangedPos = true;
                    
            }
            break;

        case GLFW_KEY_D:{
                Vec3f right = up_.Cross(target_);
                right.Normalize();
                right *= speed_;
                pos_ += right;
                cameraChangedPos = true;
            }
            break;

        case GLFW_KEY_UP:
            angleV_ += speed_;
            Update();
            break;

        case GLFW_KEY_DOWN:
            angleV_ -= speed_;
            Update();
            break;

        case GLFW_KEY_RIGHT:
            angleH_ += speed_;
            Update();
            break;

        case GLFW_KEY_LEFT:
            angleH_ -= speed_;
            Update();
            break;

        // TODO IMPLEMENT MORE CASES
    }
    return cameraChangedPos;
}

void BasicCamera::OnMouse(int x, int y){
    int deltaX = x - mousePos_.x;
    int deltaY = y - mousePos_.y;

    mousePos_.x = x;
    mousePos_.y = y;

    angleH_ += (float)deltaX / 20.0f;
    angleV_ += (float)deltaY / 20.0f;

    if (x <= MARGIN){
        onLeftEdge_  = true;
        onRigthEdge_ = false;
    } else if (x >= (windowWidth_ - MARGIN)){
        onRigthEdge_ = true;
        onLeftEdge_  = false;
    } else {
        onRigthEdge_ = false;
        onLeftEdge_  = false;
    }

    if (y <= MARGIN){
        onUpperEdge_ = true;
        onLowerEdge_ = false;
    } else if (y >= (windowHeight_ - MARGIN)){
        onUpperEdge_ = false;
        onLowerEdge_ = true;
    } else {
        onUpperEdge_ = false;
        onLowerEdge_ = false;
    }
    Update();
}

void BasicCamera::UpdateMousePosSilent(int x, int y){ mousePos_.x = x; mousePos_.y = y; }

void BasicCamera::OnRender(){
    bool shouldUpdate = false;

    if (onLeftEdge_) { angleH_ -= EDGE_STEP; shouldUpdate = true; }
    if (onRigthEdge_){ angleH_ += EDGE_STEP; shouldUpdate = true; }

    if (onUpperEdge_){
        if (angleV_ > -90.0f){ angleV_ -= EDGE_STEP; shouldUpdate = true; }
    }
    if (onLowerEdge_){
        if (angleV_ < 90.0f){ angleV_ += EDGE_STEP; shouldUpdate = true; }
    }

    if (shouldUpdate) Update();
}

void BasicCamera::Update(){
    Vec3f yAxis(0.0f, 1.0f, 0.0f);

    // Rotation of the view vector by the horizontal angle around the vertical axis 
    Vec3f view(1.0f, 0.0f, 0.0f);
    view.Rotate(angleH_, yAxis);
    view.Normalize();

    // Rotation of the view vector by the vertical angle around the horizontal axis 
    Vec3f u = yAxis.Cross(view);
    u.Normalize();
    view.Rotate(angleV_, u);

    target_ = view;
    target_.Normalize();

    up_ = target_.Cross(u);
    up_.Normalize();
}

//Mat4 BasicCamera::GetMatrix() const{
//    Mat4 cameraTransformation;
//    cameraTransformation.InitCameraTransform(pos_, target_, up_);
//    return cameraTransformation;
//}


