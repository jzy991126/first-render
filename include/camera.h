#pragma once
#include<Eigen/Dense>
#include"scene.h"
using vec3 = Eigen::Vector3f;

class Camera {
private:
    vec3 orig,lower_left_corner,horizontal,vertical;
    vec3 u,v,w;
    double lens_radius;

public:
	Camera(const vec3& lookfrom,const vec3& lookat,const vec3& vup,double vfov,double aspect_ratio,double aperture,double focus_dist);
	Ray getRay(float u, float v);
};