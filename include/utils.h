#pragma once

#include <algorithm>
#include <random>
#include <Eigen/Dense>
const double pi = 3.1415926535897932385;

float clamp(const float& lo, const float& hi, const float& v);

Eigen::Vector4f to_vec4(const Eigen::Vector3f& v3, float w);

Eigen::Vector3f random_vec3();
Eigen::Vector3f random_vec3(float min,float max);

float random_float();
float random_float(float min,float max);

double random_double();

Eigen::Vector3f random_in_unit_sphere();

Eigen::Vector3f random_unit_vector();

Eigen::Vector3f random_in_hemisphere(const Eigen::Vector3f& normal);

Eigen::Vector3f reflect(const Eigen::Vector3f& v,const Eigen::Vector3f& n);

Eigen::Vector3f refract(const Eigen::Vector3f &uv, const Eigen::Vector3f &n, double etai_over_etat);

double degree2radians(double deg);

Eigen::Vector3f random_in_unit_disk();