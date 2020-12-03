#pragma once

#include <algorithm>
#include <random>
#include <Eigen/Dense>


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

Eigen::Vector3f refract(const Eigen::Vector3f& uv, const Eigen::Vector3f& n, double etai_over_etat) {
    auto cos_theta = fmin((-uv).dot(n), 1.0);
    Eigen::Vector3f r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Eigen::Vector3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squaredNorm())) * n;
    return r_out_perp + r_out_parallel;
}