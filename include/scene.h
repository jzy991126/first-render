#pragma once

#include <utility>
#include <vector>
#include <Eigen/Dense>
#include "object.h"
#include "m_embree.h"
#include <map>
#include <unordered_map>


#include "ray.h"
#include "hit.h"

class Scene
{

private:
	std::vector<Object> objects;
	std::unordered_map<unsigned int, Mesh> id2mesh;
	

public:
	Scene();
	void addObject(const Object& obj);
	void endAdd();
	My_Hit castRay(const Ray& ray) const;
	M_embree embree;
};