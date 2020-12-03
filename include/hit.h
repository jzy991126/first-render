//
// Created by jzy99 on 2020/12/3.
//

#pragma once

#include "material.h"


struct My_Hit
{
    bool isHit;
    Eigen::Vector3f normal,point;
    std::shared_ptr<Material> material;
    float u, v;
};


