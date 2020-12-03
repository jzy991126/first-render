#include "object.h"
#include "utils.h"


Object::Object(Model& model,const std::shared_ptr<Material>& material)
{
	transform = Eigen::Affine3f::Identity();
	meshes = model.meshes;
	for(auto & mesh : meshes)
    {
	    mesh.material=material;
    }


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
	for (auto & mesh : meshes)
	{
		for(auto & vertice : mesh.vertices)
        {
//            vertice = transform.linear()*vertice;
            vertice = transform*vertice;
        }

//            vertice =  transform.linear()*vertice;

	}
}
void Object::rotate(float theta, const Eigen::Vector3f& vec)
{
	Eigen::AngleAxisf trans(theta, vec);
	transform.rotate(trans);
}