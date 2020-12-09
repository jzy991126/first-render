#include "object.h"
#include "utils.h"
#include "material_factory.h"


Object::Object(Model& model,bool enableTexture,std::string material,shared_ptr<Texture> texture)
{
	transform = Eigen::Affine3f::Identity();
	meshes = model.meshes;

	this->enableTexture= enableTexture;
	if(enableTexture)
    {
        for(auto & mesh : meshes)
        {
            auto temp = MaterialFactory::get().produce_shared(material);
            if(mesh.hasTexture)
            {

                temp->setAlbedo(mesh.texture);
//                auto temp = std::make_shared<Material>(*material);
            }
            else{
                temp->setAlbedo(texture);
            }
            mesh.material=temp;
        }
    }
	else{
        auto temp = MaterialFactory::get().produce_shared(material);
        temp->setAlbedo(texture);
        for(auto & mesh : meshes)
        {
            mesh.material=temp;
        }
	}

	enableTexture = false;
}

void Object::pan(const Eigen::Vector3f& vec)
{	
//	transform = transform.pretranslate(vec);

	transform.translate(vec);
}

void Object::scale(const Eigen::Vector3f& vec)
{
	transform.scale(vec);
}

void Object::update()
{
    Eigen::Matrix3f trans2 = transform.matrix().transpose().inverse().topLeftCorner<3,3>();
	for (auto & mesh : meshes)
	{
		for(auto & vertice : mesh.vertices)
        {
//            vertice = transform.linear()*vertice;
            vertice.position = transform*vertice.position;
            vertice.normal = (trans2*vertice.normal).normalized();

        }

	}
}
void Object::rotate(float theta, const Eigen::Vector3f& vec)
{
	Eigen::AngleAxisf trans(theta, vec);
	transform.rotate(trans);
}

Object::Object(Model& model,shared_ptr<Material> material) {
    transform = Eigen::Affine3f::Identity();
    meshes = model.meshes;

    for(auto & mesh : meshes)
    {
        mesh.material=material;
    }
}
