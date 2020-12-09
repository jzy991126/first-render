//
// Created by jzy99 on 2020/12/3.
//

#pragma once
#include "firstrender.h"

class Material;
class Ray;


struct My_Hit
{
    bool isHit;
    Ray ray;
    Eigen::Vector3f normal,point;
    std::shared_ptr<Material> material;
    std::shared_ptr<Texture> texture;
    float u, v;
    Vec2 texcoord;
};


