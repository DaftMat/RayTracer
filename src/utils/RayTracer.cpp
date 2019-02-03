//
// Created by mathis on 02/02/19.
//

#include <fstream>
#include <iostream>
#include "RayTracer.h"

bool hitSphere(const Ray &r, const Sphere &s, float &t) {
    float a = r.dir.dot(r.dir);
    float b = 2.f * (r.pos-s.centre).dot(r.dir);
    Eigen::Vector3f temp = r.pos-s.centre;
    float c = temp.dot(temp) - s.radius*s.radius;
    float del = b*b - 4.f*a*c;
    if (del > 0){
        float t0 = (-b-std::sqrt(del))/2*a;
        if (t0 >= 0.0f){
            t = t0;
            return true;
        }
        float t1 = (-b+std::sqrt(del))/2*a;
        if (t1 >= 0.0f){
            t = t1;
            return true;
        }
    }
    return false;
}

int hittedSphere(const Ray &r, const Scene &s, float &t) {
    for (int i = 0 ; i < s.spheres.size() ; ++i)
        if (hitSphere(r, s.spheres[i], t))
            return i;
    return -1;
}

Ray segmentToLight(const Ray & view, const Light & l, const Point3f & start, const Eigen::Vector3f &n, float &t) {
    Eigen::Vector3f dist = (l.pos - start);
    if ((n.dot(dist)) <= 0.0f) return Ray{Point3f(0,0,0),Eigen::Vector3f(0,0,0)};
    float temp = sqrtf(dist.dot(dist));
    if (temp <= 0.0f)  return Ray{Point3f(0,0,0),Eigen::Vector3f(0,0,0)};

    t = temp;
    Ray ret;
    ret.pos = start;
    ret.dir = (1/t)*dist;
    ret.dir.normalize();
    return ret;
}

bool isInShadow(const Ray & lr, const Scene & s, float &t) {
    for (const auto &sphere : s.spheres)
        if (hitSphere(lr, sphere, t))
            return true;
    return false;
}

void applyLight(Color & c, const Color &cm, const Ray & lr, const Light & l, const Eigen::Vector3f &n, float & f) {
    float lambert = (lr.dir.dot(n)) * f;
    c = c + (l.color * cm * lambert);
}

Color rayTrace(const Ray &r, const Scene &s, float coef, int level) {
    Color ret = { 0 };
    if (!level || coef == 0.f)
        return ret;
    float t;
    int sphereIndex = hittedSphere(r, s, t);
    if (sphereIndex == -1)
        return ret; //no object found

    //n calculation
    Point3f start = r.pos + t*r.dir;
    //std::cout << start << std::endl;
    Eigen::Vector3f n = start - s.spheres[sphereIndex].centre;
    float temp = n.dot(n);
    if (temp == 0.0f)   return ret;
    temp = 1.0f / sqrtf(temp);
    n = temp * n;
    n.normalize();

    Material mat = s.materials[s.spheres[sphereIndex].material];

    float reflect = 2.f * (r.dir.dot(n));
    Ray reflectRay{start, r.dir-reflect*n};
    std::cout << coef << " " << level << std::endl;
    ret = ret + rayTrace(reflectRay, s, coef*mat.reflection, level-1);

    for (int i = 0 ; i < s.lights.size() ; ++i){
        float tl = 0.f;
        Ray lr = segmentToLight(r, s.lights[i], start, n, tl);
        if (lr.dir.x() || lr.dir.y() || lr.dir.z())
            if (!isInShadow(lr, s, t)){
                applyLight(ret, mat.color, lr, s.lights[i], n, coef);
            }
    }

    return ret;
}

void traceImage(const Scene &s, char *path) {
    Ray ray = {Point3f(0,0,0),Eigen::Vector3f(0,0,0)};
    Color c;
    Observator obs = s.obs;
    std::ofstream file;
    file.open(path);

    file << "P3\n" << obs.width <<  " " << obs.height << "\n255" << std::endl;
    for (int i = 0 ; i < obs.height ; ++i){
        for (int j = 0 ; j < obs.width ; ++j){
            ray.pos = Point3f{float(j), float(i), -10000};
            ray.dir = Eigen::Vector3f{0.f,0.f,1.f};
            ray.dir.normalize();
            //std::cout << ray.pos << "\n" << ray.dir << std::endl;
            c = rayTrace(ray, s, 1.0f, 20);
            file << c << std::endl;
        }
    }

    file.close();
}

