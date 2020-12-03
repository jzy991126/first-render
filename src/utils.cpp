#include "utils.h"


Eigen::Vector4f to_vec4(const Eigen::Vector3f &v3, float w) {
    return {v3.x(), v3.y(), v3.z(), w};
}

float clamp(const float &lo, const float &hi, const float &v) {
    return std::max(lo, std::min(hi, v));
}

double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}



Eigen::Vector3f random_vec3() {
    return {random_float(),random_float(),random_float()};
}

float random_float() {
    static thread_local std::random_device dev;
    static thread_local std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.f, 1.f); // distribution in range [1, 6]

    return dist(rng);
}

Eigen::Vector3f random_vec3(float min, float max) {
    return {random_float(min,max),random_float(min,max),random_float(min,max)};
}

float random_float(float min, float max) {
    static thread_local std::random_device dev;
    static thread_local std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(min, max); // distribution in range [1, 6]

    return dist(rng);
}

Eigen::Vector3f random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1,1);
        if (p.squaredNorm() >= 1.0) continue;
        return p;
    }
}

Eigen::Vector3f random_unit_vector() {
    return random_in_unit_sphere().normalized();
}

Eigen::Vector3f random_in_hemisphere(const Eigen::Vector3f &normal) {
    Eigen::Vector3f in_unit_sphere = random_in_unit_sphere();
    if (in_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

Eigen::Vector3f reflect(const Eigen::Vector3f &v, const Eigen::Vector3f &n) {
    return v - 2*v.dot(n)*n;
}
