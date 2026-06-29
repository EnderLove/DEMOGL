#ifndef CAMERA_API_H
#define CAMERA_API_H

// INTERFACE TO CREATE CAMERAS 

#include "math3D.h"

class CameraAPI{
public:
    virtual const Vec3f GetPos() const = 0;
    //virtual Mat4 GetViewportMatrix() const = 0;
    virtual Mat4 GetMatrix() const = 0;
    //virtual const Mat4 GetProjectionMat() = 0;
};

#endif // CAMERA_API_H!
