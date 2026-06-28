#ifndef MATH_3D_H
#define MATH_3D_H

#include <assimp/config.h>
#include <glm/glm.hpp>
#include <assert.h>
#include <math.h>

#define ToRadian(x) (float)(x * 0.01745329252f)
#define ToDegree(x) (float)(x * 57.29577951308f)

struct PersProjInfo{
    float FOV    = 0.0f;
    float Width  = 0.0f;
    float Height = 0.0f;
    float zNear  = 0.0f;
    float zFar   = 0.0f;
};

struct OrthoProjInfo{
    float right;
    float left;
    float bottom;
    float top;
    float zNear;
    float zFar;
    
    float Width;
    float Height;
};

struct Vec2i{
    int x = 0;
    int y = 0;

    Vec2i(){}
    Vec2i(int x, int y) : x(x), y(y){}
};

struct Vec3i{
    int x = 0;
    int y = 0;
    int z = 0;
};

class Vec2f{
    public:
        union{float x; float u;};
        union{float y; float v;};

    public:
        Vec2f();
        Vec2f(const float value);
        Vec2f(const Vec2f &rhs);
        Vec2f(float X, float Y);
        Vec2f(const float *xy);
        Vec2f(const glm::vec2& v);
        Vec2f &operator = (const Vec2f &rhs);

        bool         operator == (const Vec2f &rhs) const;
        bool         operator != (const Vec2f &rhs) const;
        Vec2f        operator +  (const Vec2f &rhs) const;
        const Vec2f &operator += (const Vec2f &rhs);
        const Vec2f &operator -= (const Vec2f &rhs);
        Vec2f        operator -  (const Vec2f &rhs) const;
        Vec2f        operator *  (const float rhs) const;
        const Vec2f &operator *= (const float rhs);
        const Vec2f &operator /= (const float rhs);
        float        operator [] (const int   idx) const;
        float       &operator [] (const int   idx);

        const Vec2f &Normalize();
        float GetMagnitude() const;
        bool IsValid() const;
        float Dot(const Vec2f &rhs) const { return x * rhs.x + y * rhs.y; }
        const float *ToPtr() const { return &x; }
};

class Vec3f {
    public:
        union{float x; float r;};
        union{float y; float g;};
        union{float z; float b;};

    public:
        Vec3f();
        Vec3f(float value);
        Vec3f(const Vec3f &rhs);
        Vec3f(float X, float Y, float Z);
        Vec3f(const float *xyz);
        Vec3f(const glm::vec3& v);
        Vec3f &operator = (const Vec3f  &rhs);
        Vec3f &operator = (const float *rhs);

        bool         operator == (const Vec3f &rhs) const;
        bool         operator != (const Vec3f &rhs) const;
        Vec3f        operator +  (const Vec3f &rhs) const;
        const Vec3f &operator += (const Vec3f &rhs);
        const Vec3f &operator -= (const Vec3f &rhs);
        Vec3f        operator -  (const Vec3f &rhs) const;
        Vec3f        operator *  (const float rhs) const;
        Vec3f        operator /  (const float rhs) const;
        const Vec3f &operator *= (const float rhs);
        const Vec3f &operator /= (const float rhs);
        float        operator [] (const int   idx) const;
        float       &operator [] (const int   idx);

        void Zero() { x = 0.0f; y = 0.0f; z = 0.0f; }

        Vec3f Cross(const Vec3f &rhs) const;
        float Dot (const Vec3f &rhs) const;

        const Vec3f &Normalize();
        void Rotate(float angle, const Vec3f& v);
        float GetMagnitude() const;
        float GetLenghtSqr() const { return Dot(*this); }
        bool IsValid() const;
        void GetOrtho(Vec3f &u, Vec3f &v) const;

        const float * ToPtr() const { return &x; }
};

class Vec4f{
    public:
        float x;
        float y;
        float z;
        float w;

    public:
        Vec4f();
        Vec4f(const float value);
        Vec4f(const Vec4f &rhs);
        Vec4f(float X, float Y, float Z, float W);
        Vec4f(const float *rhs);
        Vec4f(const glm::vec4& v);
        Vec4f &operator = (const Vec4f &rhs);

        bool         operator == (const Vec4f &rhs) const;
        bool         operator != (const Vec4f &rhs) const;
        Vec4f        operator +  (const Vec4f &rhs) const;
        const Vec4f &operator += (const Vec4f &rhs);
        const Vec4f &operator -= (const Vec4f &rhs);
        const Vec4f &operator *= (const Vec4f &rhs);
        const Vec4f &operator /= (const Vec4f &rhs);
        Vec4f        operator -  (const Vec4f &rhs) const;
        Vec4f        operator *  (const float rhs) const;
        float        operator [] (const int idx) const;
        float       &operator [] (const int idx);

        float Dot(const Vec4f &rhs) const;
        const Vec4f &Normalize();
        float GetMagnitude() const;
        bool IsValid() const;
        void Zero() { x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; }

        const float *ToPtr() const { return &x; }
        float *ToPtr() { return &x; }
};

class Mat2{
    public:
        Vec2f rows[2];

    public:
        Mat2() {}
        Mat2(const Mat2 &rhs);
        Mat2(const float *mat);
        Mat2(const Vec2f &row0, const Vec2f &row1);
        Mat2 &operator = (const Mat2 & rhs);

        const Mat2 &operator *= (const float rhs);
        const Mat2 &operator += (const Mat2 &rhs);

        float Determinant() const { return rows[0].x * rows[1].y - rows[0].y * rows[1].x; }
};

class Mat3{
    public: 
        Vec3f rows[3];

    public:
        Mat3() {}
        Mat3(const Mat3 &rhs);
        Mat3(const float *mat);
        Mat3(const Vec3f &row0, const Vec3f &row1, const Vec3f &row2);
        Mat3 &operator = (const Mat3 &rhs);

        void Zero();
        void Identity();

        float Trace() const;
        float Determinant() const;
        Mat3 Transpose() const;
        Mat3 Inverse() const;
        Mat2 Minor(const int i, const int j) const;
        float Cofactor(const int i, const int j) const;

        Vec3f operator * (const Vec3f &rhs) const;
        Mat3  operator * (const float rhs) const;
        Mat3  operator * (const Mat3 &rhs) const;
        Mat3  operator + (const Mat3 &rhs) const;

        const Mat3 &operator *= (const float rhs);
        const Mat3 &operator += (const Mat3 &rhs);
};

class Mat4{
    public:
        Vec4f rows[4];

    public:
        Mat4() {}
        Mat4(const Mat4 &rhs);
        Mat4(const float *mat);
        Mat4(const Vec4f &row0, const Vec4f &row1, const Vec4f &row2, const Vec4f &row3);
        Mat4 &operator = (const Mat4 &rhs);
        ~Mat4() {}

        void Zero();
        void Identity();

        float Trace() const;
        float Determinant() const;
        Mat4 Transpose() const;
        Mat4 Inverse() const;
        Mat3 Minor(const int i, const int j) const;
        float Cofactor(const int i, const int j) const;

        void Orient(Vec3f pos, Vec3f fwd, Vec3f up);
        void LookAt(Vec3f pos, Vec3f lookAt, Vec3f up);
        void PerspectiveOpenGL(float fovy, float aspect_ratio, float near, float far);
        void PerspectiveVulkan(float fovy, float aspect_ratio, float near, float far);
        void OrthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
        void OrthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);

        const float *ToPtr() const { return rows[0].ToPtr(); }
        float *ToPtr() { return rows[0].ToPtr(); }

        Vec4f operator * (const Vec4f &rhs) const;
        Mat4  operator * (const float rhs) const;
        Mat4  operator * (const Mat4 &rhs) const;
        const Mat4 &operator *= (const float rhs);
};

class Quat{
    public:
        float w;
        float x;
        float y;
        float z;

    public:
        Quat();
        Quat(const Quat &rhs);
        Quat(float X, float Y, float Z, float W);
        Quat(Vec3f n, const float angleRadians);
        const Quat &operator = (const Quat &rhs);

        Quat &operator *= (const float &rhs);
        Quat &operator *= (const Quat &rhs);
        Quat  operator *  (const Quat &rhs) const;
        //Quat  operator *  (const Quat &rhs, const Vec3f &v) const;

        void Normalize();
        void Invert();
        Quat Conjugate() const;
        Quat Inverse() const;
        
        float MagnitudeSquared() const;
        float GetMagnitude() const;
        Vec3f RotatePoint(const Vec3f &rhs) const;
        Mat3 RotateMatrix(const Mat3 &rhs) const;
        Vec3f xyz() const { return Vec3f(x, y, z); }
        bool IsValid() const;

        Mat3 ToMat3() const;
        Vec4f ToVec4() const { return Vec4f(w, x, y, z); }
};

Quat operator * (const Quat &rhs, const Vec3f &v);

#endif // MATH_3D_H!
