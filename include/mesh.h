//
// Created by jzy99 on 2020/12/3.
//

#pragma once



#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "material.h"

class Mesh {
public:
    std::vector<Eigen::Vector3f> vertices;
    std::vector<uint32_t> indices;
    std::vector<Eigen::Vector3f> normals;
    std::shared_ptr<Material> material;


public:
    Mesh(std::vector<Eigen::Vector3f> vertices, std::vector<uint32_t> indices, std::vector<Eigen::Vector3f> normals):
            vertices(std::move(vertices)),indices(std::move(indices)),normals(std::move(normals)){}
    Mesh()= default;
    Eigen::Vector3f getNorm(unsigned int indice,float u,float v) const;
};




