#include <iostream>

#include "utils/RayTracer.h"

int main() {
    Scene s;
    s.materials.push_back(Material{Color{1.f,1.f,0.f},0.5f,0.f});
    s.materials.push_back(Material{Color{0.f,1.f,1.f},0.5f,0.f});
    s.materials.push_back(Material{Color{1.f,0.f,1.f},0.5f,0.f});
    s.lights.push_back(Light{Color{1,1,1},Point3f(0,240, -100)});
    s.lights.push_back(Light{Color{0.6,0.7,0.1},Point3f(640,240, -10000)});
    s.spheres.push_back(Sphere{Point3f(233,290,0),100,0});
    s.spheres.push_back(Sphere{Point3f(407,290,0),100,1});
    s.spheres.push_back(Sphere{Point3f(320,140,0),100,2});
    s.obs = createObservator(Point3f(0,0,0), Eigen::Vector3f(0,0,1), Eigen::Vector3f(0,1,0), 0.3, 640, 480);

    traceImage(s, const_cast<char *>("example.ppm"));

    return 0;
}