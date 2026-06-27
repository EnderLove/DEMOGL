#ifndef VECTORS_LIB_H
#define VECTORS_LIB_H

#include <glm/glm.hpp>
#include <assert.h>
#include <math.h>

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

#endif // VECTORS_LIB_H!
