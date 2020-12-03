//
// Created by jzy99 on 2020/12/3.
//

#pragma once

#include "ray.h"

class Material {
public:
    virtual bool scatter(const Ray& r_in,const Eigen::Vector3f& normal,const Eigen::Vector3f& point,Ray& scattered,Eigen::Vector3f& attenuation) const = 0;

};

class Lambertian : public Material {
public:
    explicit Lambertian(Eigen::Vector3f color);

    bool scatter(const Ray& r_in,const Eigen::Vector3f& normal,const Eigen::Vector3f& point,Ray& scattered,Eigen::Vector3f& attenuation) const override;

public:
    const Eigen::Vector3f albedo;
};


class Metal: public Material{
public:
    Eigen::Vector3f albedo;
    float fuzz;
public:
    Metal(Eigen::Vector3f color,float fuzz);

    bool scatter(const Ray& r_in,const Eigen::Vector3f& normal,const Eigen::Vector3f& point,Ray& scattered,Eigen::Vector3f& attenuation) const override;
};




