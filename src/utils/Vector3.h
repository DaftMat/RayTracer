//
// Created by mathis on 03/02/19.
//

#ifndef RAYTRACING_VECTOR3_H
#define RAYTRACING_VECTOR3_H

#include<ostream>
#include <cmath>

template<typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3() : x(T(0)), y(T(0)), z(T(0)) { }
    Vector3(T xx) : x(xx), y(xx), z(xx) { }
    Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { }

    Vector3& normalize(){
        T nor2 = length2();
        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }
    Vector3<T> operator * (const T &f) const { return Vector3<T>(x * f, y * f, z * f); }
    Vector3<T> operator * (const Vector3<T> &v) const { return Vector3<T>(x * v.x, y * v.y, z * v.z); }
    Vector3<T> cross(const Vector3<T> &v) const { return Vector3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    T dot(const Vector3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3<T> operator - (const Vector3<T> &v) const { return Vector3<T>(x - v.x, y - v.y, z - v.z); }
    Vector3<T> operator + (const Vector3<T> &v) const { return Vector3<T>(x + v.x, y + v.y, z + v.z); }
    Vector3<T>& operator += (const Vector3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vector3<T>& operator *= (const Vector3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }
    T operator [] (int i) const { return !i ? x : i==1 ? y : z; }
    T length2() const { return x * x + y * y + z * z; }
    T length() const { return sqrt(length2()); }
    friend std::ostream & operator << (std::ostream &os, const Vector3<T> &v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vector3<float> Vector3f;

#endif //RAYTRACING_VECTOR3_H
