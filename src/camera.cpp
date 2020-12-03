#include "camera.h"


Ray Camera::getRay(float u, float v)
{
	return Ray(orig, lower_left_corner + u * horizontal + v * vertical - orig);
}

Camera::Camera(float _aspect_ratio, float _viewport_height, float _focal_length, Eigen::Vector3f _orig)
{
	viewport_height = _viewport_height;
	aspect_ratio = _aspect_ratio;
	viewport_height = _viewport_height;
	orig = _orig;

	viewport_width = aspect_ratio * viewport_height;
	horizontal = Eigen::Vector3f(viewport_width, 0, 0);
	vertical = Eigen::Vector3f(0, viewport_height, 0);

	lower_left_corner = orig - horizontal / 2 - vertical / 2 - Eigen::Vector3f(0, 0, _focal_length);

}