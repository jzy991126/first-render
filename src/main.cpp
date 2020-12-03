
#include <eigen3/Eigen/Dense>
#include<string>
#include <iostream>
#include <chrono>

#include "ppm.h"
#include "model.h"
#include "m_embree.h"
#include "camera.h"
#include "object.h"
#include "scene.h"
#include "utils.h"
#include "material.h"
using namespace std;

unsigned long long bounce;
const float russian = 0.9;

Eigen::Vector3f CastRay(const Ray& ray, const Scene& scene)
{

    if(random_float()>russian)
        return {0.0f,0.0f,0.0f};

    bounce++;
    My_Hit hit = scene.castRay(ray);


    if(hit.isHit){
        Ray scattered;
        Eigen::Vector3f attenuation;
        if(hit.material->scatter(ray,hit.normal,hit.point,scattered,attenuation))
        {
            return attenuation.cwiseProduct(CastRay(scattered,scene));
        }
        return {0.0f,0.0f,0.0f};
    }

    auto unit_direction = ray.dir.normalized();
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Eigen::Vector3f(1.0, 1.0, 1.0) + t*Eigen::Vector3f(0.5, 0.7, 1.0);

}

int main()
{

    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 500;

    bounce = 0;


    PPM ppm("test", image_width, image_height);
	string path("C:/Users/jzy99/Desktop/ball.fbx");




    Camera camera(aspect_ratio, 2.0f, 1.0f, Eigen::Vector3f(0.0f,0.0f,3.0f));
	Scene scene;

    Model ball_model(path);
    auto material_diffuse = make_shared<Lambertian>(Eigen::Vector3f(0.8f,.8f,.0f));
    auto metal_diffuse = make_shared<Metal>(Eigen::Vector3f(1.0f,1.0f,1.0f),0.5);

    Object ball1(ball_model,metal_diffuse),ball2(ball_model,material_diffuse),ball3(ball_model,metal_diffuse);
    Object plane2(ball_model,material_diffuse);

    plane2.pan(Eigen::Vector3f(0.0f,2.0f,0.0f));
    plane2.scale(Eigen::Vector3f(5.0f,1.0f,1.0f));
    plane2.update();

    ball1.pan(Eigen::Vector3f(3.f,0.f,0.f));
    ball1.update();

    ball2.pan(Eigen::Vector3f(-2.f,0.f,0.f));
    ball2.update();

//    ball.pan(Eigen::Vector3f(5.0f,5.0f,2.0f));
//    ball.update();


//    ball2.pan(Eigen::Vector3f(-4.0f,0.0f,0.0f));
//    ball2.update();
	
	/*ball.scale(Eigen::Vector3f(1.20f, 1.20f, 1.20f));
	ball.pan(Eigen::Vector3f(1.0f, 0.0f, 0.0f));
	ball.rotate(0.7, Eigen::Vector3f::UnitZ());



	ball.update();*/

	scene.addObject(ball1);
	scene.addObject(ball2);
	scene.addObject(ball3);
	scene.addObject(plane2);
	scene.endAdd();

    auto start = std::chrono::system_clock::now();

	for (int j = 0; j <image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << image_height-j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
            Eigen::Vector3f color(0.0f, 0.0f, 0.0f);
#pragma omp parallel
		    {
		        Eigen::Vector3f result(0.0f,0.0f,0.0f);
#pragma omp for nowait //fill result_private in parallel
            for (int s = 0; s < sample_per_pixel; s++) {
                auto u = (float(i) + random_float()) / (image_width - 1);
                auto v = (float(j) + random_float()) / (image_height - 1);

                Ray ray = camera.getRay(u, v);
                result += CastRay(ray, scene);
            }
#pragma omp critical
            color += result;
            }
			ppm.setpixel(i,j,color/sample_per_pixel);
		}
	}
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
    std::cout<<bounce<<endl;

	ppm.write_file();


}