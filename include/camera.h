#pragma once
#include<Eigen/Dense>
#include"scene.h"

class Camera {
private:
	float viewport_height, viewport_width,aspect_ratio;
	Eigen::Vector3f orig, horizontal, vertical, lower_left_corner;

public:
	Camera(float _aspect_ratio, float _viewport_height,float _focal_length, Eigen::Vector3f _orig);
	Ray getRay(float u, float v);
};