//
// Created by jzy99 on 2020/12/4.
//
#include "mesh.h"

Eigen::Vector3f Mesh::getNorm(unsigned int indice,float u,float v) const {


    auto ind1 = indices[indice*3],ind2 = indices[indice*3+1],ind3 = indices[indice*3+2];
    Eigen::Vector3f a = normals[ind1],b = normals[ind2],c = normals[ind3];

//    float r = 1.0/3.0;
//    return (r*(a+b+c)).normalized();
    return (1-u-v)*a+u*b+v*c;
}
