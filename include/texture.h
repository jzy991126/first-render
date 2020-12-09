//
// Created by jzy99 on 2020/12/7.
//

#ifndef TESTASSIMP_TEXTURE_H
#define TESTASSIMP_TEXTURE_H

#include <memory>
#include "firstrender.h"
#include "utils.h"
#include<Eigen/Dense>
#include <iostream>

class Texture
{
public:
    virtual Color value(double u,double v, const Point3& p)const
    {
        return {0.8,0.8,0.8};
    };
};


class SolidColor : public Texture
{
private:
    Eigen::Vector3f color_value;
public:
    SolidColor(){}
    SolidColor(Eigen::Vector3f c):color_value(c){}
    SolidColor(float r,float g,float b):color_value(r,g,b){}

    Color value(double u,double v, const Point3& p)const override;


};

class CheckerTexture: public Texture
{
public:
    CheckerTexture() {}

    CheckerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd)
    : even(_even), odd(_odd) {}

    CheckerTexture(Color c1, Color c2)
    : even(make_shared<SolidColor>(c1)) , odd(make_shared<SolidColor>(c2)) {}

    Color value(double u, double v, const Point3& p) const override;

public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;
};


class ImageTexture : public Texture {

private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;
public:
    const static int bytes_per_pixel = 3;

    ImageTexture()
            : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

    ImageTexture(std::string filename);
    ImageTexture(unsigned char* _data,int width,int height,int bytes_per_scanline);

    ~ImageTexture() {
        /*delete data;*/
    }

    Color value(double u, double v, const Vec3& p) const override;


};

#endif //TESTASSIMP_TEXTURE_H
