#include"model.h"
#include<iostream>

#include "stb_image.h"

Model::Model(const std::string& path)
{

    dir = path.substr(0, path.find_last_of('/'));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate|aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{

    Mesh result;
	std::vector<uint32_t> indices;
	std::vector<Vertex> vertices;
	bool hasTexture=false;



	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
	    Vertex vertex;
	    vertex.position = Point3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = Vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);


        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {

            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vertex.texcoord = Vec2(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
            // tangent
//            vector.x = mesh->mTangents[i].x;
//            vector.y = mesh->mTangents[i].y;
//            vector.z = mesh->mTangents[i].z;
//            vertex.Tangent = vector;
//            // bitangent
//            vector.x = mesh->mBitangents[i].x;
//            vector.y = mesh->mBitangents[i].y;
//            vector.z = mesh->mBitangents[i].z;
//            vertex.Bitangent = vector;
        }
        else
            vertex.texcoord = Vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
	}
	result.vertices = vertices;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	result.indices = indices;
	if(mesh->mMaterialIndex>=0)
    {
        auto material = scene->mMaterials[mesh->mMaterialIndex];
        if(material->GetTextureCount(aiTextureType_DIFFUSE)>0){
            hasTexture = true;
            auto  diffuseMaps = LoadMaterialTextures(material,
                                                     aiTextureType_DIFFUSE, "texture_diffuse", scene);
            result.texture = diffuseMaps;
        }
    }

	result.hasTexture = hasTexture;

	return result;
}

shared_ptr<ImageTexture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName,const aiScene* scene) {

    int c = mat->GetTextureCount(type);
    aiString name;
    mat->GetTexture(type,0,&name);
    std::string file_path = dir+'/'+std::string(name.C_Str());
    auto aitexture = scene->GetEmbeddedTexture(name.C_Str());
    unsigned char* image_data = nullptr;
    int width, height, nrChannels;
    if(aitexture!= nullptr)
    {
        if(aitexture->mHeight == 0)
        {
            image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aitexture->pcData), aitexture->mWidth, &width, &height, &nrChannels, 3);
        }
        else
        {
            image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aitexture->pcData), aitexture->mWidth * aitexture->mHeight, &width, &height, &nrChannels, 3);
        }
    }
    else{
        image_data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 3);
    }

    return make_shared<ImageTexture>(image_data,width,height,3*width);

}

