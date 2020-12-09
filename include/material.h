//
// Created by jzy99 on 2020/12/3.
//

#pragma once

#include "ray.h"
#include "firstrender.h"
#include "texture.h"
#include "hit.h"
#include "material_factory.h"

#include <string>

class Material {
public:
    virtual bool scatter(const My_Hit& hit, Ray &scattered,
                         Eigen::Vector3f &attenuation) const = 0;

    virtual Eigen::Vector3f emitted(double u,double v,const Eigen::Vector3f& p)const{
        return {0,0,0};
    }

    virtual void setAlbedo(shared_ptr<Texture>)
    {

    }


};

class Lambertian : public Material {
public:
    Lambertian(const Color& a) : albedo(make_shared<SolidColor>(a)) {}
    Lambertian(shared_ptr<Texture> a) : albedo(a) {}
    Lambertian()=default;

    bool scatter(const My_Hit& hit, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;
    void setAlbedo(shared_ptr<Texture> now_albedo)override;


public:
    shared_ptr<Texture> albedo;
};

REGISTER_MATERIAL(Lambertian,"lambertian");


class Metal : public Material {
public:
    shared_ptr<Texture> albedo;
    float fuzz;
public:
    Metal()=default;
    Metal(Eigen::Vector3f color, float fuzz);

    bool scatter(const My_Hit& hit, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;
    void setAlbedo(shared_ptr<Texture> now_albedo)override;
};

REGISTER_MATERIAL(Metal,"metal");

class Dielectric : public Material {
public:
    float ir;
public:
    Dielectric()=default;
    Dielectric(float index_of_refraction);

    bool scatter(const My_Hit& hit, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;


private:
    static double reflectance(double cosine, double ref_idx);
};

REGISTER_MATERIAL(Dielectric,"dielectric");

class Diffuse_light: public Material
{
public:
    shared_ptr<Texture> color;
public:
    Diffuse_light()=default;
    Diffuse_light(Eigen::Vector3f color);
    Diffuse_light(shared_ptr<Texture> color);
    bool scatter(const My_Hit& hit, Ray &scattered,
                 Eigen::Vector3f &attenuation) const override;
    Eigen::Vector3f emitted(double u,double v,const Eigen::Vector3f& p)const override;

    void setAlbedo(shared_ptr<Texture> now_albedo)override;
};

REGISTER_MATERIAL(Diffuse_light,"diffuse_light");