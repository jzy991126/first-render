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

Eigen::Vector3f refract(const Eigen::Vector3f &uv, const Eigen::Vector3f &n, double etai_over_etat) {
    auto cos_theta = fmin((-uv).dot(n), 1.0);
    Eigen::Vector3f r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Eigen::Vector3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squaredNorm())) * n;
    return r_out_perp + r_out_parallel;
}

double degree2radians(double deg) {
    return deg * pi / 180.0;
}


Eigen::Vector3f random_in_unit_disk() {
    while (true) {
        auto p = Eigen::Vector3f(random_float(-1,1), random_float(-1,1), 0);
        if (p.squaredNorm() >= 1) continue;
        return p;
    }
}

Eigen::Vector3f random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = sqrt(1-r2);

    auto phi = 2*pi*r1;
    auto x = cos(phi)*sqrt(r2);
    auto y = sin(phi)*sqrt(r2);

    return Eigen::Vector3f(x, y, z);
}
