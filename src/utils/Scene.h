//
// Created by daftmat on 01/02/19.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Vector3.h"
#include <vector>

const auto PI = 3.141592653589793238462643383279502884197169399375105820974944f;

typedef struct Color{
	float r;
	float g;
	float b;
}Color;

std::ostream & operator<<(std::ostream &, Color c);
Color operator+(const Color &, const Color &);
Color operator*(const Color &, const Color &);
Color operator*(const Color &, float);

typedef struct Material {
	Color color;
	float reflection;
	float transparency;
}Material;

typedef struct Sphere {
    Vector3f centre;
	float radius;
	int material;
}Sphere;

typedef struct Light{
	Color color;
    Vector3f pos;
}Light;

typedef struct Ray{
    Vector3f pos;
	Vector3f dir;
}Ray;

typedef struct Observator{
    Vector3f obs;
    Vector3f pos;
	Vector3f x, y, z;
	float width;
	float height;
}Observator;

/* obervator's constructor */
Observator createObservator(const Vector3f &, const Vector3f &, const Vector3f &, float, float, float);

typedef struct Scene {
	std::vector<Light> lights;
	std::vector<Sphere> spheres;
	std::vector<Material> materials;
	Observator obs;
}Scene;



#endif //RAYTRACER_SCENE_H
