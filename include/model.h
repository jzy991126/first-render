
#pragma once
#include<string>
#include <utility>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <eigen3/Eigen/Dense>
#include <unordered_map>
#include "material.h"
#include "mesh.h"

class ImageTexture;


class Model {
public:
	std::vector<Mesh> meshes;
	std::string dir;
	std::unordered_map<std::string,ImageTexture> textures_loaded;

public:
	explicit Model(const std::string& path);


private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	shared_ptr<ImageTexture> LoadMaterialTextures(aiMaterial *mat,aiTextureType type, std::string typeName,const aiScene* scene);

};