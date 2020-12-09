//
// Created by jzy99 on 2020/12/3.
//

#include "material.h"

#include <iostream>
#include "utils.h"



bool Lambertian::scatter(const My_Hit& hit,Ray& scattered,Eigen::Vector3f& attenuation) const {
    Eigen::Vector3f scatter_direction = hit.normal + random_unit_vector();
    if(scatter_direction.isApprox(Eigen::Vector3f::Zero(),1e-8))
        scatter_direction = hit.normal;

    scattered = Ray(hit.point, scatter_direction);
    attenuation = albedo->value(hit.texcoord.x(),hit.texcoord.y(),hit.point);
    return true;

}

void Lambertian::setAlbedo(shared_ptr<Texture> now_albedo) {
    albedo = now_albedo;
}

Metal::Metal(Eigen::Vector3f color,float fuzz) :fuzz(fuzz){
    albedo = make_shared<SolidColor>(color);
}

bool Metal::scatter(const My_Hit& hit, Ray &scattered,
                    Eigen::Vector3f &attenuation) const {
    auto reflected = reflect(hit.ray.dir.normalized(),hit.normal);
    scattered = Ray(hit.point,reflected+fuzz*random_in_unit_sphere());
    attenuation = albedo->value(hit.texcoord.x(),hit.texcoord.y(),hit.point);
    return scattered.dir.dot(hit.normal)>0.0f;
}

void Metal::setAlbedo(shared_ptr<Texture> now_albedo) {
    albedo = now_albedo;
}

bool Dielectric::scatter(const My_Hit& hit, Ray &scattered,
                         Eigen::Vector3f &attenuation) const {


    attenuation = Eigen::Vector3f(1,1,1);
    auto front = hit.ray.dir.dot(hit.normal)<=0.0;


    double refraction_ratio = (front)? 1.0/ir:ir;
    auto t_normal = front ? hit.normal : -hit.normal;
    t_normal.normalize();

    auto unit_direction = hit.ray.dir.normalized();

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

    scattered = Ray(hit.point, direction);

    return true;
}

Dielectric::Dielectric(float index_of_refraction) : ir(index_of_refraction) {
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Diffuse_light::Diffuse_light(Eigen::Vector3f color){
    this->color = make_shared<SolidColor>(color);
}

Eigen::Vector3f Diffuse_light::emitted(double u, double v, const Eigen::Vector3f &p) const {
    return color->value(u,v,p);
}

bool Diffuse_light::scatter(const My_Hit& hit, Ray &scattered,
             Eigen::Vector3f &attenuation) const{
    return false;

}

void Diffuse_light::setAlbedo(shared_ptr<Texture> now_albedo) {
    color = now_albedo;
}

Diffuse_light::Diffuse_light(shared_ptr<Texture> color) :color(color){}
