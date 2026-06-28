#ifndef BASIC_CAMERA_H
#define BASIC_CAMERA_H

#include <assimp/postprocess.h>
#include <string>

#include "math3D.h"
#include "cameraAPI.h"

class BasicCamera : public CameraAPI{
private:
    void InitInternal();
    void Update();

    std::string name_;

    Vec3f pos_;
    Vec3f target_;
    Vec3f up_;

    float speed_ = 0.2f;
    int windowWidth_  = 0;
    int windowHeight_ = 0;
    
    float angleH_ = 0.0f;
    float angleV_ = 0.0f;

    bool onUpperEdge_ = false;
    bool onLowerEdge_ = false;
    bool onLeftEdge_  = false;
    bool onRigthEdge_ = false;

    Vec2i mousePos_ = Vec2i(0, 0);
    
    PersProjInfo persProjInfo_;
    Mat4 projection_;

public: 
    BasicCamera(){}
    BasicCamera(int windowWidth, int windowHeigth);
    BasicCamera(const PersProjInfo&  persProjInfo , const Vec3f& pos, const Vec3f& target, const Vec3f& up);
    BasicCamera(const OrthoProjInfo& orthoProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up);

    void InitCamera(const PersProjInfo&  persProjInfo , const Vec3f& pos, const Vec3f& target, const Vec3f& up);
    void InitCamera(const OrthoProjInfo& orthoProjInfo, const Vec3f& pos, const Vec3f& target, const Vec3f& up);

    void SetPosition(float x, float y, float z);
    void SetPosition(const Vec3f& pos);

    void SetTarget(float x, float y, float z);
    void SetTarget(const Vec3f& target);

    void SetUp(float x, float y, float z){ up_.x = x; up_.y = y; up_.z = z; }

    bool OnKeyboard(int key);
    void OnMouse(int x, int y);

    // Update the mouse position without moving the camera 
    void UpdateMousePosSilent(int x, int y);

    void OnRender();
    Mat4 GetMatrix() const;

    const Vec3f GetPos() const { return pos_; }
    const Vec3f& GetTarget() const { return target_; }
    const Vec3f& GetUp() const { return up_; }
    const Mat4 GetProjectionMat() const { return projection_; }
    const PersProjInfo& GetPersProjInfo() const { return persProjInfo_; }
    
    Mat4 GetViewProjMatrix() const;
    Mat4 GetViewMatrix() const { return GetMatrix(); }
    Mat4 GetViewportMatrix() const;

    void SetSpeed(float speed);
    void SetName(const std::string& name) { name_ = name; }
    const std::string& GetName() const { return name_; }
};

#endif // BASIC_CAMERA_H!
