#include "camera.h"
#include "utils.h"

Ray Camera::getRay(float s, float t)
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return {
            orig + offset,
            lower_left_corner + s*horizontal + t*vertical - orig - offset
    };
}

Camera::Camera(const vec3 &lookfrom, const vec3& lookat, const vec3& vup, double vfov, double aspect_ratio, double aperture,
               double focus_dist) {
    auto theta = degree2radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = (lookfrom - lookat).normalized();
    u = vup.cross(w).normalized();
    v = w.cross(u);

    orig = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = orig - horizontal/2 - vertical/2 - focus_dist*w;

    lens_radius = aperture / 2;
}