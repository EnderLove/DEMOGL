#ifndef CAMERA_API_H
#define CAMERA_API_H

// INTERFACE TO CREATE CAMERAS 

#include "VectorsLib.h"

class CameraAPI{
public:
    virtual const Vec3 GetPos() const = 0;
    virtual Matrix4f GetViewportMatrix() const = 0;
    virtual Matrix4f GetMatrix() const = 0;
    virtual const Matrix4f GetProjectionMat() = 0;
};

#endif // CAMERA_API_H!
