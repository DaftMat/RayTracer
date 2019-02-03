//
// Created by mathis on 02/02/19.
//

#ifndef RAYTRACING_RAYTRACER_H
#define RAYTRACING_RAYTRACER_H


#include "Scene.h"

bool hitSphere(const Ray &, const Sphere &, float &);
int hittedSphere(const Ray &, const Scene &, float &);

Ray segmentToLight(const Ray &, const Light &, const Vector3f &, const Vector3f &, float &);
bool isInShadow(const Ray &, const Scene &, float &);
void applyLight(Color &, const Color &cm, const Ray &, const Light &, const Vector3f &, float &);

Color rayTrace(const Ray &, const Scene &, float coef, int level);
void traceImage(const Scene &, std::string);

#endif //RAYTRACING_RAYTRACER_H
