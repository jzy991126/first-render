//
// Created by jzy99 on 2020/12/3.
//

#include "material.h"

#include <utility>
#include <iostream>


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

Metal::Metal(Eigen::Vector3f color,float fuzz) :albedo(std::move(color)),fuzz(fuzz){
    needOrigNorm = false;
}

bool Metal::scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                    Eigen::Vector3f &attenuation) const {
    auto reflected = reflect(r_in.dir.normalized(),normal);
    scattered = Ray(point,reflected+fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return scattered.dir.dot(normal)>0.0f;
}

bool Dielectric::scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                         Eigen::Vector3f &attenuation) const {


    attenuation = Eigen::Vector3f(1,1,1);
    auto front = r_in.dir.dot(normal)<=0.0;

    if(front)
    {
        int a=1;
    }
    else{
        int b=2;
    }

    double refraction_ratio = (front)? 1.0/ir:ir;
    auto t_normal = front ? normal : -normal;
    t_normal.normalize();

    auto unit_direction = r_in.dir.normalized();

    double cos_theta = fmin((-unit_direction).dot(t_normal),1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Eigen::Vector3f direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
    {
        direction = reflect(unit_direction, t_normal);

    }
    else
    {
        direction = refract(unit_direction, t_normal, refraction_ratio);
//        std::cout<<"nnmd"<<std::endl;
    }

    scattered = Ray(point, direction);

    return true;
}

Dielectric::Dielectric(double index_of_refraction) : ir(index_of_refraction) {
    needOrigNorm = false;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Diffuse_light::Diffuse_light(Eigen::Vector3f color) :color(std::move(color)){}

Eigen::Vector3f Diffuse_light::emitted(double u, double v, const Eigen::Vector3f &p) const {
    return color;
}

bool Diffuse_light::scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
             Eigen::Vector3f &attenuation) const{
    return false;

}
