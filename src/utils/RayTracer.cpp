//
// Created by mathis on 02/02/19.
//

#include <fstream>
#include <iostream>
#include "RayTracer.h"

bool hitSphere(const Ray &r, const Sphere &s, float &t) {
    Vector3f dist = s.centre - r.pos;
    float B = r.dir.dot(dist);
    float del = B*B - dist.dot(dist) + s.radius * s.radius;
    if (del > 0.f){
        float t0 = (B-sqrtf(del));
        if (t0 > 0.1f){
            t = t0;
            return true;
        }
        float t1 = (B+sqrtf(del));
        if (t1 > 0.1f){
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

Ray segmentToLight(const Ray & view, const Light & l, const Vector3f & start, const Vector3f &n, float &t) {
    Vector3f dist = (l.pos - start);
    if ((n.dot(dist)) <= 0.0f) return Ray{Vector3f(0,0,0),Vector3f(0,0,0)};
    float temp = sqrtf(dist.dot(dist));
    if (temp <= 0.0f)  return Ray{Vector3f(0,0,0),Vector3f(0,0,0)};

    t = temp;
    Ray ret;
    ret.pos = start;
    ret.dir = dist*(1/t);
    ret.dir.normalize();
    return ret;
}

bool isInShadow(const Ray & lr, const Scene & s, float &t) {
    for (const auto &sphere : s.spheres)
        if (hitSphere(lr, sphere, t))
            return true;
    return false;
}

void applyLight(Color & c, const Color &cm, const Ray & lr, const Light & l, const Vector3f &n, float & f) {
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
    Vector3f start = r.pos + r.dir * t;
    Vector3f n = start - s.spheres[sphereIndex].centre;
    float temp = n.dot(n);
    if (temp == 0.0f)   return ret;
    temp = 1.0f/sqrtf(temp);
    n = n * temp;
    n.normalize();

    //material recuperation
    Material mat = s.materials[s.spheres[sphereIndex].material];

    //find lighting color : more or less shadowed
    Color ltc = { 0 };
    for (int i = 0 ; i < s.lights.size() ; ++i){
        float tl = 0.f;
        Ray lr = segmentToLight(r, s.lights[i], start, n, tl);
        if (lr.dir.x || lr.dir.y || lr.dir.z)
            if (!isInShadow(lr, s, t)){
                applyLight(ltc, mat.color, lr, s.lights[i], n, coef);
            }
    }

    //Calculates reflect and trace reflect's ray
    float reflect = 2.f * (r.dir.dot(n));
    Ray reflectRay;
    reflectRay.pos = start;
    reflectRay.dir = r.dir-n * reflect;
    reflectRay.dir.normalize();
    Color rfc = rayTrace(reflectRay, s, coef*mat.reflection, level-1);

    //find final color of the pixel
    ret = ltc+rfc;

    return ret;
}

void traceImage(const Scene &s, std::string path) {
    Ray ray = {Vector3f(0,0,0),Vector3f(0,0,0)};
    Color c;
    Observator obs = s.obs;
    ray.pos = obs.obs;
    std::ofstream file;
    file.open(path);

    file << "P3\n" << obs.width <<  " " << obs.height << "\n255" << std::endl;
    for (int j = int(-obs.height/2) ; j < obs.height/2 ; ++j){
        for (int i = int(-obs.width/2) ; i < obs.width/2 ; ++i){
            //Calculate pixel position in 3D space
            Vector3f pixPoint(float(i)/obs.width, float(j)/obs.height, obs.pos.z);
            ray.dir = pixPoint - ray.pos;   // -> find the direction of the ray
            ray.dir.normalize();
            //trace and print the pixel to the file
            c = rayTrace(ray, s, 1.0f, 100);
            file << c << std::endl;
        }
    }

    file.close();
}

