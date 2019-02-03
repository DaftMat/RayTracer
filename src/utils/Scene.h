//
// Created by daftmat on 01/02/19.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Point3f.h"
#include <vector>

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
	Point3f centre;
	float radius;
	int material;
}Sphere;

typedef struct Light{
	Color color;
	Point3f pos;
}Light;

typedef struct Ray{
	Point3f pos;
	Eigen::Vector3f dir;
}Ray;

typedef struct Observator{
	Point3f obs;
	Point3f pos;
	Eigen::Vector3f x, y, z;
	float width;
	float height;
}Observator;

/* obervator's constructor */
Observator createObservator(const Point3f &, const Eigen::Vector3f &, const Eigen::Vector3f &, float, float, float);

typedef struct Scene {
	std::vector<Light> lights;
	std::vector<Sphere> spheres;
	std::vector<Material> materials;
	Observator obs;
}Scene;



#endif //RAYTRACER_SCENE_H
