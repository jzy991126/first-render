#pragma once

#include <string>
#include <Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include <vector>
#include "model.h"
#include "material.h"

class Object
{

private:
	Eigen::Affine3f transform;
public:
	Object(Model& model,bool enableTexture= false,std::string material="",shared_ptr<Texture> texture = nullptr);
	Object(Model& model,shared_ptr<Material> material);
	void pan(const Eigen::Vector3f& vec);
	void scale(const Eigen::Vector3f& vec);
	void rotate(float thera, const Eigen::Vector3f& vec);
	void update();
	Object() = default;

public:
	std::vector<Mesh> meshes;
	bool enableTexture;



};