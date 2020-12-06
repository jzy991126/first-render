//
// Created by jzy99 on 2020/12/3.
//

#pragma once

#include "ray.h"

class Material {
public:
    virtual bool scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                         Eigen::Vector3f &attenuation) const = 0;

    virtual Eigen::Vector3f emitted(double u,double v,const Eigen::Vector3f& p)const{
        return {0,0,0};
    }

    bool needOrigNorm=false;

};

class Lambertian : public Material {
public:
    explicit Lambertian(Eigen::Vector3f color);

    bool scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;

public:
    const Eigen::Vector3f albedo;
};


class Metal : public Material {
public:
    Eigen::Vector3f albedo;
    float fuzz;
public:
    Metal(Eigen::Vector3f color, float fuzz);

    bool scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;
};


class Dielectric : public Material {
public:
    float ir;
public:
    Dielectric(double index_of_refraction);

    bool scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;

private:
    static double reflectance(double cosine, double ref_idx);
};

class Diffuse_light: public Material
{
public:
    Eigen::Vector3f color;
public:
    Diffuse_light(Eigen::Vector3f color);
    bool scatter(const Ray &r_in, const Eigen::Vector3f &normal, const Eigen::Vector3f &point, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;
    Eigen::Vector3f emitted(double u,double v,const Eigen::Vector3f& p)const override;
};