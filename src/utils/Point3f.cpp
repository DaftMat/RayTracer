//
// Created by mathis on 02/02/19.
//

#include "Point3f.h"

std::ostream &operator<<(std::ostream &os, const Point3f &p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

Point3f &Point3f::operator+=(const Eigen::Vector3f &v) {
    this->x += v.x();
    this->y += v.y();
    this->z += v.z();
    return *this;
}

Point3f &Point3f::operator+=(float f) {
    this->x += f;
    this->y += f;
    this->z += f;
    return *this;
}

Point3f &Point3f::operator-=(const Eigen::Vector3f &v) {
    this->x -= v.x();
    this->y -= v.y();
    this->z -= v.z();
    return *this;
}

Eigen::Vector3f operator-(const Point3f &p1, const Point3f &p2) {
    Eigen::Vector3f ret(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
    return ret;
}

Point3f operator+(const Point3f &p, const Eigen::Vector3f &v) {
    Point3f ret(p.x+v.x(), p.y+v.y(), p.z+v.z());
    return ret;
}

Point3f operator+(const Point3f &p, float f) {
    Point3f ret(p.x+f, p.y+f, p.z+f);
    return ret;
}

Point3f operator-(const Point3f &p, const Eigen::Vector3f &v) {
    Point3f ret(p.x-v.x(), p.y-v.y(), p.z-v.z());
    return ret;
}
