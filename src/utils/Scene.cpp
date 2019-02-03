//
// Created by daftmat on 01/02/19.
//

#include "Scene.h"

std::ostream & operator<<(std::ostream & os, Color c){
	return os << (unsigned short)std::min(c.b*255.f, 255.f) << " " << (unsigned short)std::min(c.g*255.f, 255.f) << " " << (unsigned short)std::min(c.r*255.f, 255.f);
}

Color operator+(const Color & c1, const Color & c2){
	Color ret = { 0 };
	ret.r = c1.r + c2.r;
	ret.g = c1.g + c2.g;
	ret.b = c1.b + c2.b;
	return ret;
}

Color operator*(const Color & c1, const Color & c2) {
    Color ret = { 0 };
    ret.r = c1.r*c2.r;
    ret.g = c1.g*c2.g;
    ret.b = c1.b*c2.b;
    return ret;
}

Color operator*(const Color & c, float f) {
	Color ret = { 0 };
	ret.r = c.r*f;
	ret.g = c.g*f;
	ret.b = c.b*f;
	return ret;
}

Observator createObservator(const Point3f & pos, const Eigen::Vector3f & zc, const Eigen::Vector3f & up, float fov, float width, float height){
	Observator observator;
	observator.z = zc;
	observator.x = zc.cross(up);
	observator.y = observator.x.cross(zc);
	observator.pos = pos;
	observator.obs = pos - (1.f/tanf(fov/2.f))*zc;
	observator.width = width;
	observator.height = height;
	return observator;
}

