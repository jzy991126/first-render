//
// Created by jzy99 on 2020/12/4.
//
#include "mesh.h"


Vec2 Mesh::getTexcood(unsigned int indice,float u,float v) const {


    auto ind1 = indices[indice*3],ind2 = indices[indice*3+1],ind3 = indices[indice*3+2];
    auto coord1 = vertices[ind1].texcoord,coord2 = vertices[ind2].texcoord,coord3 = vertices[ind3].texcoord;
    return (1-u-v)*coord1+u*coord2+v*coord3;
}

Mesh::Mesh() {
    material = nullptr;
    hasTexture = false;
}

Vertex::Vertex() {
    position = Point3 ::Zero();
    normal = Vec3::Zero();
    texcoord = Vec2::Zero();
}
