#ifndef MATH_3D_H
#define MATH_3D_H

#include <assimp/config.h>
#include <glm/glm.hpp>
#include <assert.h>
#include <math.h>
#include <queue>

namespace cpm{
    
    constexpr float ToRadian(float degree) noexcept { return degree *  0.01745329252f; }
    constexpr float ToDegree(float radian) noexcept { return radian * 57.29577951308f; }

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
            Mat4(const float val);
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
        
            void PerspectiveOpenGL(float fovy, float aspect_ratio, float near, float far); // This takes fovy as degree 
            void PerspectiveVulkan(float fovy, float aspect_ratio, float near, float far);
            void OrthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
            void OrthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);

            void InitCameraTransform(const Vec3f &target, const Vec3f &up);
            void InitCameraTransform(const Vec3f &pos, const Vec3f &target, const Vec3f &up);

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
    inline Quat operator * (const Quat &rhs, const Vec3f &v);

    /*
    * ==============================================================
    * VEC2
    * ==============================================================
    */

    inline Vec2f::Vec2f() : x(0), y(0) {}
    inline Vec2f::Vec2f(const float value) : x(value), y(value) {}
    inline Vec2f::Vec2f(const Vec2f &rhs) : x(rhs.x), y(rhs.y) {}
    inline Vec2f::Vec2f(float X, float Y) : x(X), y(Y) {}
    inline Vec2f::Vec2f(const float *xy) : x(xy[0]), y(xy[1]) {}
    inline Vec2f::Vec2f(const glm::vec2& v) : x(v.x), y(v.y) {}

    inline Vec2f &Vec2f::operator = (const Vec2f &rhs){
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    inline bool Vec2f::operator == (const Vec2f & rhs) const {
        if (x != rhs.x) return false;
        if (y != rhs.y) return false;
        return true;
    }

    inline bool Vec2f::operator != (const Vec2f &rhs) const {
        if (*this == rhs) return false;
        return true;
    }

    inline Vec2f Vec2f::operator + (const Vec2f &rhs) const {
        Vec2f temp;
        temp.x = x + rhs.x;
        temp.y = y + rhs.y;
        return temp;
    }

    inline const Vec2f &Vec2f::operator += (const Vec2f &rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    inline const Vec2f &Vec2f::operator -= (const Vec2f &rhs){
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    inline Vec2f Vec2f::operator - (const Vec2f &rhs) const {
        Vec2f temp;
        temp.x = x - rhs.x;
        temp.y = y - rhs.y;
        return temp;
    }

    inline Vec2f Vec2f::operator * (const float rhs) const {
        Vec2f temp;
        temp.x = x * rhs;
        temp.y = y * rhs;
        return temp;
    }

    inline const Vec2f &Vec2f::operator *= (const float rhs){
        x *= rhs;
        y *= rhs;
        return *this;
    }

    inline const Vec2f &Vec2f::operator /= (const float rhs){
        x /= rhs;
        y /= rhs;
        return *this;
    }

    inline float Vec2f::operator [] (const int idx) const {
        assert( idx >= 0 && idx < 2 );
        return (&x)[idx];
    }

    inline float &Vec2f::operator [] (const int idx){
        assert( idx >= 0 && idx < 2 );
        return (&x)[idx];
    }

    inline const Vec2f &Vec2f::Normalize(){
        float mag = GetMagnitude();
        float invMag = 1.0f / mag;
        if (0.0f * invMag == 0.0f * invMag){
            x = x * invMag;
            y = y * invMag;
        }
        return *this;
    }

    inline float Vec2f::GetMagnitude() const {
        float mag;

        mag = x * x + y * y;
        mag = sqrtf(mag);

        return mag;
    }

    inline bool Vec2f::IsValid() const {
        if (x * 0.0f != x * 0.0f) return false;
        if (y * 0.0f != y * 0.0f) return false;
        return true;
    }

    /*
    * ==============================================================
    * VEC3
    * ==============================================================
    */

    inline Vec3f::Vec3f() : x(0), y(0), z(0) {}

    inline Vec3f::Vec3f(float value) : x(value), y(value), z(value) {}

    inline Vec3f::Vec3f(const Vec3f &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

    inline Vec3f::Vec3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    inline Vec3f::Vec3f(const float *xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) {}

    inline Vec3f::Vec3f(const glm::vec3& v) : x(v.x), y(v.y), z(v.z) {}

    inline Vec3f &Vec3f::operator = (const Vec3f &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    inline Vec3f &Vec3f::operator = (const float *rhs) {
        x = rhs[0];
        y = rhs[1];
        z = rhs[2];
        return *this;
    }

    inline bool Vec3f::operator == (const Vec3f &rhs) const {
        if (x != rhs.x) return false;
        if (y != rhs.y) return false;
        if (z != rhs.z) return false;
        return true;
    }

    inline bool Vec3f::operator != (const Vec3f &rhs) const {
        if (*this == rhs) return false;
        return true;
    }

    inline Vec3f Vec3f::operator + (const Vec3f &rhs) const {
        Vec3f temp;
        temp.x = x + rhs.x;
        temp.y = y + rhs.y;
        temp.z = z + rhs.z;
        return temp;
    }

    inline const Vec3f &Vec3f::operator += (const Vec3f &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    inline const Vec3f &Vec3f::operator -= (const Vec3f &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    inline Vec3f Vec3f::operator - (const Vec3f &rhs) const {
        Vec3f temp;
        temp.x = x - rhs.x;
        temp.y = y - rhs.y;
        temp.z = z - rhs.z;
        return temp;
    }

    inline Vec3f Vec3f::operator * (const float rhs) const {
        Vec3f temp;
        temp.x = x * rhs;
        temp.y = y * rhs;
        temp.z = z * rhs;
        return temp;
    }

    inline Vec3f Vec3f::operator / (const float rhs) const {
        Vec3f temp;
        temp.x = x / rhs;
        temp.y = y / rhs;
        temp.z = z / rhs;
        return temp;
    }

    inline const Vec3f &Vec3f::operator *= (const float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    inline const Vec3f &Vec3f::operator /= (const float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    inline float Vec3f::operator [] (const int idx) const {
        assert( idx >= 0 && idx < 3 );
        return (&x)[idx];
    }

    inline float &Vec3f::operator [] (const int idx) {
        assert( idx >= 0 && idx < 3 );
        return (&x)[idx];
    }

    inline Vec3f Vec3f::Cross(const Vec3f &rhs) const {
        // this is A and rhs is B (A x B)
        Vec3f temp;
        temp.x = (y * rhs.z) - (rhs.y * z);
        temp.y = (z * rhs.x) - (rhs.z * x);
        temp.z = (x * rhs.y) - (rhs.x * y);
        return temp;
    }

    inline float Vec3f::Dot(const Vec3f &rhs) const {
        float temp = (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
        return temp;
    }

    inline const Vec3f &Vec3f::Normalize() {
        float mag = GetMagnitude();
        float invMag = 1.0f / mag;
        if (0.0f * invMag == 0.0f * invMag){
            x *= invMag;
            y *= invMag;
            z *= invMag;
        }
        return *this;
    }

    inline void Vec3f::Rotate(float angle, const Vec3f& v){
        
        Quat rotationQ(v, ToRadian(angle)); // TODO REVIEW THIS IMPLEMENTATION
        Quat conjugateQ = rotationQ.Conjugate();

        Quat w = rotationQ * (*this) * conjugateQ;
        
        //Quat rotationQ(v, ToRadian(angle));
        //Vec3f w = rotationQ.RotatePoint(*this);

        x = w.x;
        y = w.y;
        z = w.z;
    }

    inline float Vec3f::GetMagnitude() const {
        float mag;
        mag = x * x + y * y + z * z;
        mag = sqrtf(mag);
        return mag;
    }

    inline bool Vec3f::IsValid() const {
        if (x * 0.0f != x * 0.0f) return false;
        if (y * 0.0f != y * 0.0f) return false;
        if (z * 0.0f != z * 0.0f) return false;
        return true;
    }

    inline void Vec3f::GetOrtho(Vec3f &u, Vec3f &v) const {
        Vec3f n = *this;
        n.Normalize();

        const Vec3f w = (n.z * n.z > 0.9f * 0.9f) ? Vec3f(1.0f, 0.0f, 0.0f) : Vec3f(0.0f, 0.0f, 1.0f);
        u = w.Cross(n);
        u.Normalize();

        v = n.Cross(u);
        v.Normalize();
        u = v.Cross(n);
        u.Normalize();
    }

    /*
    * ==============================================================
    * VEC4
    * ==============================================================
    */

    inline Vec4f::Vec4f() : x(0), y(0), z(0), w(0) {};

    inline Vec4f::Vec4f(const float value) : x(value), y(value), z(value), w(value) {}

    inline Vec4f::Vec4f(const Vec4f &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

    inline Vec4f::Vec4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

    inline Vec4f::Vec4f(const glm::vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    inline Vec4f::Vec4f(const float *rhs) {
        x = rhs[0];
        y = rhs[1];
        z = rhs[2];
        w = rhs[3];
    }

    inline Vec4f &Vec4f::operator = (const Vec4f &rhs){
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }

    inline bool Vec4f::operator == (const Vec4f &rhs) const {
        if (x != rhs.x) return false;
        if (y != rhs.y) return false;
        if (z != rhs.z) return false;
        if (w != rhs.w) return false;
        return true;
    }

    inline bool Vec4f::operator != (const Vec4f &rhs) const {
        if (*this == rhs) return false;
        return true;
    }

    inline Vec4f Vec4f::operator + (const Vec4f &rhs) const {
        Vec4f temp;
        temp.x = x + rhs.x;
        temp.y = y + rhs.y;
        temp.z = z + rhs.z;
        temp.w = w + rhs.w;
        return temp;
    }

    inline const Vec4f &Vec4f::operator += (const Vec4f &rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    inline const Vec4f &Vec4f::operator -= (const Vec4f &rhs){
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    inline const Vec4f &Vec4f::operator *= (const Vec4f &rhs){
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    inline Vec4f Vec4f::operator - (const Vec4f &rhs) const {
        Vec4f temp;
        temp.x = x - rhs.x;
        temp.y = y - rhs.y;
        temp.z = z - rhs.z;
        temp.w = w - rhs.w;
        return temp;
    }

    inline Vec4f Vec4f::operator * (const float rhs) const {
        Vec4f temp;
        temp.x = x * rhs;
        temp.y = y * rhs;
        temp.z = z * rhs;
        temp.w = w * rhs;
        return temp;
    }

    inline float Vec4f::operator [] (const int idx) const {
        assert( idx >= 0 && idx < 4 );
        return (&x)[idx];
    }

    inline float &Vec4f::operator [] (const int idx){
        assert( idx >= 0 && idx < 4 );
        return (&x)[idx];
    }

    inline float Vec4f::Dot(const Vec4f &rhs) const {
        float xx = x + rhs.x;
        float yy = y + rhs.y;
        float zz = z + rhs.z;
        float ww = w + rhs.w;
        return (xx + yy + zz + ww);
    }

    inline const Vec4f &Vec4f::Normalize() {
        float mag = GetMagnitude();
        float invMag = 1.0f / mag;
        if (0.0f * invMag == 0.0f * invMag) {
            x *= invMag;
            y *= invMag;
            z *= invMag;
            w *= invMag;
        }
        return *this;
    }

    inline float Vec4f::GetMagnitude() const {
        float mag;
        mag = x * x + y * y + z * z + w * w;
        mag = sqrtf(mag);
        return mag;
    }

    inline bool Vec4f::IsValid() const {
        if (x * 0.0f != x * 0.0f) return false;
        if (y * 0.0f != y * 0.0f) return false;
        if (z * 0.0f != z * 0.0f) return false;
        if (w * 0.0f != w * 0.0f) return false;
        return true;
    }

    /*
    ==============================================
    MAT2
    ==============================================
    */

    inline Mat2::Mat2(const Mat2 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
    }

    inline Mat2::Mat2(const float *mat){
        rows[0] = mat + 0;
        rows[1] = mat + 1;
    }

    inline Mat2::Mat2(const Vec2f &row0, const Vec2f &row1){
        rows[0] = row0;
        rows[1] = row1;
    }

    inline Mat2 &Mat2::operator = (const Mat2 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
        return *this;
    }

    inline const Mat2 &Mat2::operator *= (const float rhs){
        rows[0] *= rhs;
        rows[1] *= rhs;
        return *this;
    }

    inline const Mat2 &Mat2::operator += (const Mat2 &rhs){
        rows[0] += rhs.rows[0];
        rows[1] += rhs.rows[1];
        return *this;
    }

    /*
    ==============================================
    MAT3
    ==============================================
    */

    inline Mat3::Mat3(const Mat3 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
        rows[2] = rhs.rows[2];
    }

    inline Mat3::Mat3(const float *mat){
        rows[0] = mat + 0;
        rows[1] = mat + 3;
        rows[2] = mat + 6;
    }

    inline Mat3::Mat3(const Vec3f &row0, const Vec3f &row1, const Vec3f &row2){
        rows[0] = row0;
        rows[1] = row1;
        rows[2] = row2;
    }

    inline Mat3 &Mat3::operator = (const Mat3 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
        rows[2] = rhs.rows[2];
        return *this;
    }

    inline const Mat3 &Mat3::operator *= (const float rhs){
        rows[0] *= rhs;
        rows[1] *= rhs;
        rows[2] *= rhs;
        return *this;
    }

    inline const Mat3 &Mat3::operator += (const Mat3 &rhs){
        rows[0] += rhs.rows[0];
        rows[1] += rhs.rows[1];
        rows[2] += rhs.rows[2];
        return *this;
    }

    inline void Mat3::Zero(){
        rows[0].Zero();
        rows[1].Zero();
        rows[2].Zero();
    }

    inline void Mat3::Identity(){
        rows[0] = Vec3f(1.0f, 0.0f, 0.0f);
        rows[1] = Vec3f(0.0f, 1.0f, 0.0f);
        rows[2] = Vec3f(0.0f, 0.0f, 1.0f);
    }

    inline float Mat3::Trace() const {
        const float xx = rows[0][0] * rows[0][0];
        const float yy = rows[1][1] * rows[1][1];
        const float zz = rows[2][2] * rows[2][2];
        return (xx + yy + zz);
    }

    inline float Mat3::Determinant() const {
        const float i = rows[0][0] * (rows[1][1] * rows[2][2] - rows[1][2] * rows[2][1]);
        const float j = rows[0][1] * (rows[1][0] * rows[2][2] - rows[1][2] * rows[2][0]);
        const float k = rows[0][2] * (rows[1][0] * rows[2][1] - rows[1][1] * rows[2][0]);
        return (i - j + k);
    }

    inline Mat3 Mat3::Transpose() const {
        Mat3 transpose;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                transpose.rows[i][j] = rows[j][i];
            }
        }
        return transpose;
    }

    inline Mat3 Mat3::Inverse() const {
        Mat3 inv;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                inv.rows[j][i] = Cofactor(i, j);
            }
        }
        float det = Determinant();
        float invDet = 1.0f / det;
        inv *= invDet;
        return inv;
    }

    inline Mat2 Mat3::Minor(const int i, const int j) const {
        Mat2 minor;

        int yy = 0;
        for (int y = 0; y < 3; y++){
            if (y == j) continue;

            int xx = 0;
            for (int x = 0; x < 3; x++){
                if(x == i) continue;

                minor.rows[xx][yy] = rows[x][y];
                xx++;
            }
            yy++;
        }
        return minor;
    }

    inline float Mat3::Cofactor(const int i, const int j) const {
        const Mat2 minor = Minor(i, j);
        const float C = float(pow(-1, i + 1 + j + 1)) * minor.Determinant();
        return C;
    }

    inline Vec3f Mat3::operator * (const Vec3f &rhs) const {
        Vec3f temp;
        temp[0] = rows[0].Dot(rhs);
        temp[1] = rows[1].Dot(rhs);
        temp[2] = rows[2].Dot(rhs);
        return temp;
    }

    inline Mat3 Mat3::operator * (const float rhs) const {
        Mat3 temp;
        temp.rows[0] = rows[0] * rhs;
        temp.rows[1] = rows[1] * rhs;
        temp.rows[2] = rows[2] * rhs;
        return temp;
    }

    inline Mat3 Mat3::operator * (const Mat3 &rhs) const {
        Mat3 temp;
        for (int i = 0; i < 3; i++){
            temp.rows[i].x = rows[i].x * rhs.rows[0].x + rows[i].y * rhs.rows[1].x + rows[i].z * rhs.rows[2].x;
            temp.rows[i].y = rows[i].x * rhs.rows[0].y + rows[i].y * rhs.rows[1].y + rows[i].z * rhs.rows[2].y;
            temp.rows[i].z = rows[i].x * rhs.rows[0].z + rows[i].y * rhs.rows[1].z + rows[i].z * rhs.rows[2].z;
        }
        return temp;
    }

    inline Mat3 Mat3::operator + (const Mat3 &rhs) const {
        Mat3 temp;
        for (int i = 0; i < 3; i++){
            temp.rows[i] = rows[i] + rhs.rows[i];
        }
        return temp;
    }

    /*
    ==============================================
    MAT4
    ==============================================
    */

    inline Mat4::Mat4(const Mat4 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
        rows[2] = rhs.rows[2];
        rows[3] = rhs.rows[3];
    }

    inline Mat4::Mat4(const float *mat){
        rows[0] = mat + 0;
        rows[1] = mat + 4;
        rows[2] = mat + 8;
        rows[3] = mat + 12;
    }

    inline Mat4::Mat4(const float val){
        rows[0] = Vec4f(0.0f);
        rows[1] = Vec4f(0.0f);
        rows[2] = Vec4f(0.0f);
        rows[3] = Vec4f(0.0f);
    }

    inline Mat4::Mat4(const Vec4f &row0, const Vec4f &row1, const Vec4f &row2, const Vec4f &row3){
        rows[0] = row0;
        rows[1] = row1;
        rows[2] = row2;
        rows[3] = row3;
    }

    inline Mat4 &Mat4::operator = (const Mat4 &rhs){
        rows[0] = rhs.rows[0];
        rows[1] = rhs.rows[1];
        rows[2] = rhs.rows[2];
        rows[3] = rhs.rows[3];
        return *this;
    }

    inline const Mat4 &Mat4::operator *= (const float rhs){
        rows[0] *= rhs;
        rows[1] *= rhs;
        rows[2] *= rhs;
        rows[3] *= rhs;
        return *this;
    }

    inline void Mat4::Zero(){
        rows[0].Zero();
        rows[1].Zero();
        rows[2].Zero();
        rows[3].Zero();
    }

    inline void Mat4::Identity(){
        rows[0] = Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
        rows[1] = Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
        rows[2] = Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
        rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    }

    inline float Mat4::Trace() const {
        const float xx = rows[0][0] * rows[0][0];
        const float yy = rows[1][1] * rows[1][1];
        const float zz = rows[2][2] * rows[2][2];
        const float ww = rows[3][3] * rows[3][3];
        return (xx + yy + zz + ww);
    }

    inline float Mat4::Determinant() const {
        float det = 0.0f;
        float sign = 1.0f;
        for (int j = 0; j < 4; j++){
            Mat3 minor = Minor(0, j);

            det += rows[0][j] * minor.Determinant() * sign;
            sign = sign * -1.0f;
        }
        return det;
    }

    inline Mat4 Mat4::Transpose() const {
        Mat4 transpose;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                transpose.rows[i][j] = rows[j][i];
            }
        }
        return transpose;
    }

    inline Mat4 Mat4::Inverse() const {
        Mat4 inv;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                inv.rows[j][i] = Cofactor(i, j);
            }
        }
        float det = Determinant();
        float invDet = 1.0f / det;
        inv *= invDet;
        return inv;
    }

    inline Mat3 Mat4::Minor(const int i, const int j) const {
        Mat3 minor;

        int yy = 0;
        for (int y = 0; y < 4; y++){
            if (y == j) continue;

            int xx = 0;
            for (int x = 0; x < 4; x++){
                if (x == i) continue;

                minor.rows[xx][yy] = rows[x][y];
                xx++;
            }
            yy++;
        }
        return minor;
    }

    inline float Mat4::Cofactor(const int i, const int j) const {
        const Mat3 minor = Minor(i, j);
        const float C = float(pow(-1, i + 1 + j + 1)) * minor.Determinant();
        return C;
    }

    inline void Mat4::Orient(Vec3f pos, Vec3f fwd, Vec3f up){
        Vec3f left = up.Cross(fwd);

        // For coordinate system where:
        // +x-axis = fwd
        // +y-axis = left
        // +z-axis = up
        rows[0] = Vec4f(fwd.x, left.x, up.x, pos.x);
        rows[1] = Vec4f(fwd.y, left.y, up.y, pos.y);
        rows[2] = Vec4f(fwd.z, left.z, up.z, pos.z);
        rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    }

    inline void Mat4::LookAt(Vec3f pos, Vec3f lookAt, Vec3f up){
        Vec3f fwd = pos - lookAt;
        fwd.Normalize();

        Vec3f right = up.Cross(fwd);
        right.Normalize();

        up = fwd.Cross(right);
        up.Normalize();

        // For NDC coordinate system where:
        // +x-axis = right;
        // +y-axis = up
        // +z-axis = fwd
        rows[0] = Vec4f(right.x, right.y, right.z, -pos.Dot(right));
        rows[1] = Vec4f(up.x, up.y, up.z, -pos.Dot(up));
        rows[2] = Vec4f(fwd.x, fwd.y, fwd.z, -pos.Dot(fwd));
        rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    }

    inline void Mat4::PerspectiveOpenGL(float fovy, float aspect_ratio, float near, float far){
        fovy = ToRadian(fovy);

        const float f = 1.0f / tanf(fovy * 0.5f);
        const float xscale = f;
        const float yscale = f / aspect_ratio;

        rows[0] = Vec4f(xscale, 0.0f, 0.0f, 0.0f);
        rows[1] = Vec4f(0.0f, yscale, 0.0f, 0.0f);
        rows[2] = Vec4f(0.0f, 0.0f, (far + near) / (near - far), (2.0f * far *near) / (near - far));
        rows[3] = Vec4f(0.0f, 0.0f, -1.0f, 0.0f);
    }

    inline void Mat4::PerspectiveVulkan(float fovy, float aspect_ratio, float near, float far){
        // Vulkan changed its NDC. It switch from a left handed coordinate system to a right handed one
        // +x points to the right
        // +z points into the screen
        // +y points down (it used to point up, in OpenGL)
        // It also changed the range from [-1, 1] to [0, 1] for the z
        // Clip space remains [-1, 1] for x and y
        // Check section 23 of the specification
        Mat4 matVulkan;
        matVulkan.rows[0] = Vec4f(1.0f,  0.0f, 0.0f, 0.0f);
        matVulkan.rows[1] = Vec4f(0.0f, -1.0f, 0.0f, 0.0f);
        matVulkan.rows[2] = Vec4f(0.0f,  0.0f, 0.5f, 0.5f);
        matVulkan.rows[3] = Vec4f(0.0f,  0.0f, 0.0f, 1.0f);

        Mat4 matOpenGL;
        matOpenGL.PerspectiveOpenGL(fovy, aspect_ratio, near, far);
        *this = matVulkan * matOpenGL;
    }

    inline void Mat4::OrthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar){
        const float width  = xmax - xmin;
        const float height = ymax - ymin;
        const float depth  = zfar - znear;

        const float tx = -(xmax + xmin) / width; 
        const float ty = -(ymax + ymin) / height;
        const float tz = -(zfar + znear) / depth;

        rows[0] = Vec4f(2.0f / width, 0.0f, 0.0f, tx);
        rows[1] = Vec4f(0.0f, 2.0f / height, 0.0f, ty);
        rows[2] = Vec4f(0.0f, 0.0f, -2.0f / depth, tz);
        rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    }

    inline void Mat4::OrthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar){
        Mat4 matVulkan;
        matVulkan.rows[0] = Vec4f(1.0f,  0.0f, 0.0f, 0.0f);
        matVulkan.rows[1] = Vec4f(0.0f, -1.0f, 0.0f, 0.0f);
        matVulkan.rows[2] = Vec4f(0.0f,  0.0f, 0.5f, 0.5f);
        matVulkan.rows[3] = Vec4f(0.0f,  0.0f, 0.0f, 1.0f);

        Mat4 matOpenGL;
        matOpenGL.OrthoOpenGL(xmin, xmin, ymin, ymax, znear, zfar);

        *this = matVulkan * matOpenGL;
    }

    inline Vec4f Mat4::operator * (const Vec4f &rhs) const {
        Vec4f temp;
        temp[0] = rows[0].Dot(rhs);
        temp[1] = rows[1].Dot(rhs);
        temp[2] = rows[2].Dot(rhs);
        temp[3] = rows[3].Dot(rhs);
        return temp;
    }

    inline Mat4 Mat4::operator * (const float rhs) const {
        Mat4 temp;
        temp.rows[0] = rows[0] * rhs;
        temp.rows[1] = rows[1] * rhs;
        temp.rows[2] = rows[2] * rhs;
        temp.rows[3] = rows[3] * rhs;
        return temp;
    }

    inline Mat4 Mat4::operator * (const Mat4 &rhs) const {
        Mat4 temp;
        for (int i = 0; i < 4; i++){
            temp.rows[i].x = rows[i].x * rhs.rows[0].x + rows[i].y * rhs.rows[1].x + rows[i].z * rhs.rows[2].x + rows[i].w * rhs.rows[3].x;
            temp.rows[i].y = rows[i].x * rhs.rows[0].y + rows[i].y * rhs.rows[1].y + rows[i].z * rhs.rows[2].y + rows[i].w * rhs.rows[3].y;
            temp.rows[i].z = rows[i].x * rhs.rows[0].z + rows[i].y * rhs.rows[1].z + rows[i].z * rhs.rows[2].z + rows[i].w * rhs.rows[3].z;
            temp.rows[i].w = rows[i].x * rhs.rows[0].w + rows[i].y * rhs.rows[1].w + rows[i].z * rhs.rows[2].w + rows[i].w * rhs.rows[3].w;
        }
        return temp;
    }

    /*
    ==============================================
    QUAT
    ==============================================
    */

    inline Quat::Quat() : x(0), y(0), z(0), w(1) {}

    inline Quat::Quat(const Quat &rhs) : x(rhs.x), y(rhs.y), z(rhs.w), w(rhs.w) {}

    inline Quat::Quat(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

    inline Quat::Quat(Vec3f n, const float angleRadians) {
        const float halfAngleRadians = 0.5f * angleRadians;

        w = cosf(halfAngleRadians);

        const float halfSine = sinf(halfAngleRadians);
        n.Normalize();
        x = n.x * halfSine;
        y = n.y * halfSine;
        z = n.z * halfSine;
        // TODO COS_HALF??
    }

    inline const Quat &Quat::operator = (const Quat &rhs){
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }

    inline Quat &Quat::operator *= (const float &rhs){
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    inline Quat &Quat::operator *= (const Quat &rhs) {
        Quat temp = *this * rhs;
        w = temp.w;
        x = temp.x;
        y = temp.y;
        z = temp.z;
        return *this;
    }

    inline Quat Quat::operator * (const Quat &rhs) const {
        Quat temp;
        temp.w = (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z);
        temp.x = (x * rhs.w) + (w * rhs.x) + (y * rhs.z) - (z * rhs.y);
        temp.y = (y * rhs.w) + (w * rhs.y) + (z * rhs.x) - (x * rhs.z);
        temp.z = (z * rhs.w) + (w * rhs.z) + (x * rhs.y) - (y * rhs.x);
        return temp;
    }

    inline void Quat::Normalize() {
        float invMag = 1.0f / GetMagnitude();

        if (0.0f * invMag == 0.0f * invMag){
            x = x * invMag;
            y = y * invMag;
            z = z * invMag;
            w = w * invMag;
        }
    }

    inline Quat Quat::Conjugate() const {
        Quat ret(-x, -y, -z, w);
        return ret;
    }

    inline void Quat::Invert() {
        *this *= 1.0f / MagnitudeSquared();
        x = -x;
        y = -y;
        z = -z;
    }

    inline Quat Quat::Inverse() const {
        Quat val(*this);
            val.Invert();
        return val;
    }

    inline float Quat::MagnitudeSquared() const {
        return ( (x * x) + (y * y) + (z * z) + (w * w) );
    }

    inline float Quat::GetMagnitude() const {
        return sqrtf(MagnitudeSquared());
    }

    inline Vec3f Quat::RotatePoint(const Vec3f &rhs) const {
        Quat vector(rhs.x, rhs.y, rhs.z, 0.0f);
        Quat final = *this * vector * Inverse();
        return Vec3f(final.x, final.y, final.z);
    }

    inline bool Quat::IsValid() const {
        if (x * 0 != x * 0) return false;
        if (y * 0 != y * 0) return false;
        if (z * 0 != z * 0) return false;
        if (w * 0 != w * 0) return false;
        return true;
    }

    inline Mat3 Quat::RotateMatrix(const Mat3 &rhs) const {
        Mat3 mat;
        mat.rows[0] = RotatePoint(rhs.rows[0]);
        mat.rows[1] = RotatePoint(rhs.rows[1]);
        mat.rows[2] = RotatePoint(rhs.rows[2]);
        return mat;
    }

    inline Mat3 Quat::ToMat3() const {
        Mat3 mat;
        mat.Identity();

        mat.rows[0] = RotatePoint(mat.rows[0]);
        mat.rows[1] = RotatePoint(mat.rows[1]);
        mat.rows[2] = RotatePoint(mat.rows[2]);
        return mat;
    }

    inline Quat operator * (const Quat &rhs, const Vec3f &v){
        float w = -(rhs.x * v.x) - (rhs.y * v.y) - (rhs.z * v.z); 
        float x =  (rhs.w * v.x) + (rhs.y * v.z) - (rhs.z * v.y); 
        float y =  (rhs.w * v.y) + (rhs.z * v.x) - (rhs.x * v.z); 
        float z =  (rhs.w * v.z) + (rhs.x * v.y) - (rhs.y * v.x); 
        Quat ret(x, y, z, w);
        return ret;
    }

    /*
    ==============================================
    EXTERNAL 
    ==============================================
    */
        inline Vec3f Cross(const Vec3f &v1, const Vec3f &v2);
        inline Mat4 PerspectiveOpenGL(float fovy, float aspect_ratio, float near, float far);
        inline Vec3f Normalize(const Vec3f &vec);
        inline Mat4 LookAt(Vec3f pos, Vec3f lookAt, Vec3f up);


        inline Mat4 LookAt(Vec3f pos, Vec3f lookAt, Vec3f up){

        /*
        Vec3f fwd = pos - lookAt;
        fwd.Normalize();

        Vec3f right = up.Cross(fwd);
        right.Normalize();

        up = fwd.Cross(right);
        up.Normalize();

        Mat4 result;

        // For NDC coordinate system where:
        // +x-axis = right;
        // +y-axis = up
        // +z-axis = fwd
        result.rows[0] = Vec4f(right.x, right.y, right.z, -pos.Dot(right));
        result.rows[1] = Vec4f(up.x, up.y, up.z, -pos.Dot(up));
        result.rows[2] = Vec4f(fwd.x, fwd.y, fwd.z, -pos.Dot(fwd));
        result.rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        */ 

        Vec3f f = Normalize(lookAt - pos);
        Vec3f s = Normalize(Cross(f, up));
        Vec3f u = Cross(s, f);

        Mat4 result;

        result.rows[0] = Vec4f(s.x, s.y, s.z, -s.Dot(pos));
        result.rows[1] = Vec4f(u.x, u.y, u.z, -u.Dot(pos));
        result.rows[2] = Vec4f(-f.x, -f.y, -f.z, f.Dot(pos));
        result.rows[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

        return result; 
    }

    inline Vec3f Cross(const Vec3f &v1, const Vec3f &v2) {
        // this is A and rhs is B (A x B)
        Vec3f temp;
        temp.x = (v1.y * v2.z) - (v2.y * v1.z);
        temp.y = (v1.z * v2.x) - (v2.z * v1.x);
        temp.z = (v1.x * v2.y) - (v2.x * v1.y);
        return temp;
    }

    inline Vec3f Normalize(const Vec3f &vec) {
       
        float mag;
        mag = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
        mag = sqrtf(mag);

        Vec3f result = vec;

        float invMag = 1.0f / mag;
        if (0.0f * invMag == 0.0f * invMag){
            result.x *= invMag;
            result.y *= invMag;
            result.z *= invMag;
        }
        return result;
    }

    inline Mat4 PerspectiveOpenGL(float fovy, float aspect_ratio, float near, float far){
        fovy = ToRadian(fovy);

        const float f = 1.0f / tanf(fovy * 0.5f);
        //const float xscale = f;
        //const float yscale = f / aspect_ratio;

        const float xscale = f * aspect_ratio;
        const float yscale = f;

        Mat4 result(0.0f);

        result.rows[0] = Vec4f(xscale, 0.0f, 0.0f, 0.0f);
        result.rows[1] = Vec4f(0.0f, yscale, 0.0f, 0.0f);
        result.rows[2] = Vec4f(0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far));
        result.rows[3] = Vec4f(0.0f, 0.0f, -1.0f, 0.0f);

        return result;
    }
}
#endif // MATH_3D_H!
