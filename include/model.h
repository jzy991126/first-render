
#pragma once
#include<string>
#include <utility>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <eigen3/Eigen/Dense>
#include "material.h"
#include "mesh.h"




class Model {
public:
	std::vector<Mesh> meshes;

public:
	explicit Model(const std::string& path);


private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};