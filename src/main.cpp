#include <iostream>
#include <cstring>

#include "utils/RayTracer.h"

int main() {
    Scene s;
    s.materials.push_back(Material{Color{1.f,1.f,0.f},.9f,0.f});
    s.materials.push_back(Material{Color{0.f,1.f,1.f},.9f,0.f});
    s.materials.push_back(Material{Color{1.f,0.f,1.f},.9f,0.f});
    s.lights.push_back(Light{Color{0,1,1},Vector3f(0,-240, -50)});
    s.lights.push_back(Light{Color{1,0,1},Vector3f(240,240, -50)});
    s.lights.push_back(Light{Color{1,1,0},Vector3f(-240,240, -50)});
    s.lights.push_back(Light{Color{0.6,0.7,0.1},Vector3f(0,0, -1000)});
    s.spheres.push_back(Sphere{Vector3f(20,20,20),20,0});
    s.spheres.push_back(Sphere{Vector3f(-20,20,20),20,1});
    s.spheres.push_back(Sphere{Vector3f(0,-20,20),20,2});
    s.obs = createObservator(Vector3f(0, 0, -20), Vector3f(0, 0, 1), Vector3f(0, 1, 0), 140, 1920, 1080);
    traceImage(s, "out/example.ppm");
}