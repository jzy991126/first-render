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

class Pdf;

struct ScatterRecord {
    Ray specular_ray;
    bool is_specular;
    Color attenuation;
    shared_ptr<Pdf> pdf_ptr;
};

class Material {
public:
    virtual bool scatter(const My_Hit& hit, Ray &scattered,
                         ScatterRecord& srec ) const;

    virtual Eigen::Vector3f emitted(const My_Hit hit,double u,double v,const Eigen::Vector3f& p)const{
        return {0,0,0};
    }

    virtual double scattering_pdf(
            const My_Hit& hit,const Ray& scttered
            )const;

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
                 ScatterRecord& srec) const override;
    void setAlbedo(shared_ptr<Texture> now_albedo)override;

    double scattering_pdf(
            const My_Hit& hit,const Ray& scttered
    )const override;

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
                 ScatterRecord& srec ) const override;
    void setAlbedo(shared_ptr<Texture> now_albedo)override;
    double scattering_pdf(
            const My_Hit& hit,const Ray& scttered
    )const override;

};

REGISTER_MATERIAL(Metal,"metal");

class Dielectric : public Material {
public:
    float ir;
public:
    Dielectric()=default;
    Dielectric(float index_of_refraction);

    bool scatter(const My_Hit& hit, Ray &scattered,
                 ScatterRecord& srec ) const override;


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
                 ScatterRecord& srec ) const override;
    Eigen::Vector3f emitted(const My_Hit hit,double u,double v,const Eigen::Vector3f& p)const override;

    void setAlbedo(shared_ptr<Texture> now_albedo)override;
};

REGISTER_MATERIAL(Diffuse_light,"diffuse_light");