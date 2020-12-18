
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
#include "texture.h"
#include "firstrender.h"
#include "material_factory.h"
#include "pdf.h"

using namespace std;

unsigned long long bounce;
const float russian = 0.95;

Eigen::Vector3f CastRay(const Ray &ray, const Scene &scene) {

    bounce++;
    My_Hit hit = scene.castRay(ray);


    if (hit.isHit) {
        Ray scattered;
        auto emited = hit.material->emitted(hit,hit.u, hit.v, hit.point);

        double pdf;
        ScatterRecord srec;

        Eigen::Vector3f ref(0, 0, 0);
        if (random_float() < russian && hit.material->scatter(hit, scattered, srec)) {

            if(srec.is_specular){
                return srec.attenuation.cwiseProduct(CastRay(scattered, scene)) / russian;
            }

            scattered = Ray(hit.point,srec.pdf_ptr->generate());
            pdf = srec.pdf_ptr->value(scattered.dir);
            ref = srec.attenuation.cwiseProduct(CastRay(scattered, scene))*hit.material->scattering_pdf(hit,scattered) / russian / pdf;
        }
        return ref + emited;
    }
    return {.7, .0, .0};
    //auto unit_direction = ray.dir.normalized();
    //auto t = 0.5*(unit_direction.y() + 1.0);
    //return (1.0-t)*Eigen::Vector3f(1.0, 1.0, 1.0) + t*Eigen::Vector3f(0.5, 0.7, 1.0);

}

int main() {

    const float aspect_ratio = 1.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 300;

    Eigen::Vector3f lookfrom(0, 0, 20);
    Eigen::Vector3f lookat(0, 0, 0);
    vec3 vup(0, -1, 0);
    auto dist_to_focus = (lookfrom - lookat).norm();
    auto aperture = 0;

    bounce = 0;


    PPM ppm("test", image_width, image_height);



    Camera camera(lookfrom, lookat, vup, 70, aspect_ratio, aperture, dist_to_focus);
    Scene scene;

    auto white_texture = make_shared<SolidColor>(1, 1, 1);
    auto red_texture = make_shared<SolidColor>(.65, .05, .05);
    auto green_texture = make_shared<SolidColor>(.12, .45, .15);

    auto white_mate = make_shared<Lambertian>(white_texture);
    auto green_mate = make_shared<Lambertian>(green_texture);
    auto red_mate = make_shared<Lambertian>(red_texture);
    auto dia_mate = make_shared<Dielectric>(1.5);
    auto metal_mate = make_shared<Metal>(Color(0.8, 0.85, 0.88), 0.0);

    auto light_mate = make_shared<Diffuse_light>(Vec3(15, 15, 15));


    string dragon_path("C:/Users/jzy99/Desktop/ajax.obj");

    Model dragon_model(dragon_path);


    Object dragon(dragon_model,green_mate);

    scene.addObject(dragon);
    scene.endAdd();

   


    auto start = std::chrono::system_clock::now();

    for (int j = 0; j < image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << image_height - j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Eigen::Vector3f color(0.0f, 0.0f, 0.0f);
#pragma omp parallel
            {
                Eigen::Vector3f result(0.0f, 0.0f, 0.0f);
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
            ppm.setpixel(i, j, color / sample_per_pixel);
        }
    }
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count()
              << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()
              << " seconds\n";
    std::cout << bounce << endl;

    ppm.write_file();


}


//cornell
//
//Eigen::Vector3f lookfrom(3, 3, -5);
//Eigen::Vector3f lookat(3, 3, 0);
//vec3 vup(0, -1, 0);

//string dragon_path("C:/Users/jzy99/Desktop/fbx/dragon.fbx");
//string ball_path("C:/Users/jzy99/Desktop/ball.fbx");
//string bunny_path("C:/Users/jzy99/Desktop/test2.fbx");
//
//auto white_texture = make_shared<SolidColor>(1, 1, 1);
//auto red_texture = make_shared<SolidColor>(.65, .05, .05);
//auto green_texture = make_shared<SolidColor>(.12, .45, .15);
//
//auto white_mate = make_shared<Lambertian>(white_texture);
//auto green_mate = make_shared<Lambertian>(green_texture);
//auto red_mate = make_shared<Lambertian>(red_texture);
//auto dia_mate = make_shared<Dielectric>(1.5);
//auto metal_mate = make_shared<Metal>(Color(0.8, 0.85, 0.88), 0.0);
//
//auto light_mate = make_shared<Diffuse_light>(Vec3(15, 15, 15));
//
//string cornell_dir("C:/Users/jzy99/Desktop/cornellbox/");
//
//Model left_model(cornell_dir + "left.obj"), right_model(cornell_dir + "right.obj"), floor_model(
//    cornell_dir + "floor.obj"), light_model(cornell_dir + "light.obj"), shortbox_model(cornell_dir + "shortbox.obj"), tallbox_model(
//        cornell_dir + "tallbox.obj");
//Object left(left_model, green_mate), right(right_model, red_mate), floor(floor_model, white_mate), light(
//    light_model, light_mate), shortbox(shortbox_model, white_mate), tallbox(tallbox_model, dia_mate);
//
//Vec3 scale(0.01, 0.01, 0.01);
//
//left.scale(scale);
//left.update();
//right.scale(scale);
//right.update();
//floor.scale(scale);
//floor.update();
//light.scale(scale);
//light.update();
//shortbox.scale(scale);
//shortbox.update();
//tallbox.scale(scale);
//tallbox.update();
//
//scene.addObject(left);
//scene.addObject(right);
//scene.addObject(floor);
//scene.addObject(light);
//scene.addObject(shortbox);
//scene.addObject(tallbox);
//scene.endAdd();


//	auto checker_texture = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
//	auto erth_texture = make_shared<ImageTexture>("C:/Users/jzy99/Desktop/earthmap.jpg");
//	auto test1  = MaterialFactory::get().produce_shared("lambertian");
//	test1->setAlbedo(erth_texture);
//
//    Model dragen_model(dragon_path),ball_model(ball_path),bunny_model(bunny_path);
//    auto material_diffuse = make_shared<Lambertian>(erth_texture);
//    auto material_metal = make_shared<Metal>(Eigen::Vector3f(1.0f,1.0f,1.0f),0.0);
//    auto meterial_dielectric = make_shared<Dielectric>(1.5);
//    auto material_light = make_shared<Diffuse_light>(Eigen::Vector3f(1,1,1));
//
//    Object dragon(dragen_model,false,"lambertian",erth_texture),light(ball_model,material_light);
//    Object ball1(ball_model, meterial_dielectric);
//    Object plane(ball_model, material_light);
//    Object bunny(bunny_model, true,"lambertian");
//
////    light.scale(Eigen::Vector3f(50,50,50));
////    light.pan(Eigen::Vector3f(.0f,0.f,100.f));
////    light.update();
//
//    plane.scale(Eigen::Vector3f(100,100,1));
//    plane.pan(Eigen::Vector3f(0,0,-8));
//    plane.update();
//
//    dragon.scale(Eigen::Vector3f(0.2,0.2,0.2));
//    /*dragon.rotate(1.57,Eigen::Vector3f::UnitX());*/
//    /*dragon.pan(Eigen::Vector3f(0,3,0));*/
//    dragon.update();
//
//    light.scale(Eigen::Vector3f(10,10,10));
//    light.pan(Eigen::Vector3f(0,0,30));
//    light.update();
//
//
//    bunny.rotate(4.71,Eigen::Vector3f::UnitX());
//    bunny.update();
////    ball3.rotate(1.57,Eigen::Vector3f::UnitX());
////    ball3.update();
//
////    ball.pan(Eigen::Vector3f(5.0f,5.0f,2.0f));
////    ball.update();
//
//
////    ball2.pan(Eigen::Vector3f(-4.0f,0.0f,0.0f));
////    ball2.update();
//
//	/*ball.scale(Eigen::Vector3f(1.20f, 1.20f, 1.20f));
//	ball.pan(Eigen::Vector3f(1.0f, 0.0f, 0.0f));
//	ball.rotate(0.7, Eigen::Vector3f::UnitZ());
//
//
//
//	ball.update();*/
//
//	scene.addObject(dragon);
////	scene.addObject(ball2);
//    scene.addObject(plane);
//    //scene.addObject(ball1);
////    scene.addObject(bunny);
////	scene.addObject(light);
//	scene.endAdd();



