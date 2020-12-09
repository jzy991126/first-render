//
// Created by jzy99 on 2020/12/3.
//

#pragma once


#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "material.h"
#include "firstrender.h"


class ImageTexture;

struct Vertex {
    Point3 position;
    Vec3 normal;
    Vec2 texcoord;

    Vertex();

};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::shared_ptr<Material> material;
    shared_ptr<ImageTexture> texture;
    bool hasTexture;


public:
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, bool hasTexture) :
            vertices(std::move(vertices)), indices(std::move(indices)), hasTexture(hasTexture) {}

    Vec2 getTexcood(unsigned int indice,float u,float v) const;

    Mesh();
};




