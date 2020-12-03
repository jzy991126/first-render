#include "scene.h"
#include <iostream>
Scene::Scene()
= default;

void Scene::addObject(const Object& obj)
{
	objects.push_back(obj);
	auto last_obj = objects.end() - 1;

	for (auto & meshe : last_obj->meshes)
	{
		unsigned int id = embree.addMesh(meshe.vertices, meshe.indices);
		id2mesh[id] = meshe;
	}
	
}

void Scene::endAdd()
{
	embree.endAdd();
}

My_Hit Scene::castRay(const Ray& ray) const
{

	My_Hit result;
	RTCRayHit hit = embree.castRay(ray.orig, ray.dir);
	result.isHit = !(hit.hit.geomID == RTC_INVALID_GEOMETRY_ID);

	if (!result.isHit)
		return result;
	result.normal = Eigen::Vector3f(hit.hit.Ng_x, hit.hit.Ng_y, hit.hit.Ng_z).normalized();
	unsigned int geoid = hit.hit.geomID;
	unsigned int priid = hit.hit.primID;
	result.material = id2mesh.at(geoid).material;

//    auto mesh  = id2mesh.at(geoid);
//	auto resa = mesh.getPoint(static_cast<int>(priid),hit.hit.u,hit.hit.v);

    auto resb = ray.orig+hit.ray.tfar*ray.dir;


//    if(!resa.isApprox(resb,1e-5))
//        std::cout<< resa<<" \n --- "<<resb<<std::endl;

    result.point = resb;

//    if(result.normal.dot(ray.dir)>=(-1e-5))
//        result.normal = -result.normal;

	return result;

}