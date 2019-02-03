//
// Created by mathis on 02/02/19.
//

#ifndef RAYTRACING_POINT3F_H
#define RAYTRACING_POINT3F_H

#include <ostream>
#include <Eigen/Dense>

class Point3f {
    float x;
    float y;
    float z;

public:
    Point3f() = default;
    explicit Point3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz) { }

    Point3f(const Point3f &cpy) = default;
    ~Point3f() = default;

    Point3f &operator=(const Point3f &) = default;

    friend std::ostream &operator<<(std::ostream &, const Point3f &);

    //operators
    Point3f &operator+=(const Eigen::Vector3f &);
    Point3f &operator+=(float);
    Point3f &operator-=(const Eigen::Vector3f &);

    friend Eigen::Vector3f operator-(const Point3f &, const Point3f &);
    friend Point3f operator+(const Point3f &, const Eigen::Vector3f &);
    friend Point3f operator+(const Point3f &, float);
    friend Point3f operator-(const Point3f &, const Eigen::Vector3f &);

};


#endif //RAYTRACING_POINT3F_H
