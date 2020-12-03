//
// Created by jzy99 on 2020/12/3.
//

#ifndef TESTASSIMP_RAY_H
#define TESTASSIMP_RAY_H

#include <eigen3/Eigen/Dense>

struct Ray
{
    Eigen::Vector3f orig, dir;
    Ray(Eigen::Vector3f orig, Eigen::Vector3f dir):orig(std::move(orig)),dir(std::move(dir)){}
    Ray() = default;;
};

#endif //TESTASSIMP_RAY_H
