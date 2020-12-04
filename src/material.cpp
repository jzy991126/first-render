//
// Created by jzy99 on 2020/12/3.
//

#include "material.h"

#include <utility>

#include "utils.h"

Lambertian::Lambertian(Eigen::Vector3f color) : albedo(std::move(color)) {}

bool Lambertian::scatter(const Ray& r_in,const Eigen::Vector3f& normal,const Eigen::Vector3f& point,Ray& scattered,Eigen::Vector3f& attenuation) const {
    Eigen::Vector3f scatter_direction = normal + random_unit_vector();
    if(scatter_direction.isApprox(Eigen::Vector3f::Zero(),1e-8))
        scatter_direction = normal;

    scattered = Ray(point, scatter_direction);
    attenuation = albedo;
    return true;

}

Metal::Metal(Eigen::Vector3f color,float fuzz) :albedo(std::move(color)),fuzz(fuzz){}

bool Metal::scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                    Eigen::Vector3f &attenuation) const {
    auto reflected = reflect(r_in.dir.normalized(),normal);
    scattered = Ray(point,reflected+fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return scattered.dir.dot(normal)>0.0f;
}

bool Dielectric::scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                         Eigen::Vector3f &attenuation) const {
    attenuation = Eigen::Vector3f(1.f,1.f,1.f);


    double refraction_ratio = r_in.dir.dot(normal)>=0.0? 1.0/ir:ir;

    auto unit_direction = r_in.dir.normalized();
    auto refracted = refract(unit_direction,normal,refraction_ratio);

    scattered = Ray(point,r_in.dir);
    return true;
}
