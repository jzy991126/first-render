//
// Created by jzy99 on 2020/12/4.
//
#include "mesh.h"

Eigen::Vector3f Mesh::getNorm(unsigned int indice,float u,float v) const {
    Eigen::Vector3f a = normals[indice*3],b = normals[indice*3+1],c = normals[indice*3+2];
    return (1-u-v)*a+u*b+v*c;
}
