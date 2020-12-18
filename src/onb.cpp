//
// Created by jzy99 on 2020/12/9.
//

#include "onb.h"

Vec3 Onb::u() const { return axis[0]; }

Vec3 Onb::v() const { return axis[1]; }

Vec3 Onb::w() const { return axis[2]; }

Vec3 Onb::local(double a, double b, double c) const {
    return a*u() + b*v() + c*w();
}

Vec3 Onb::local(const Vec3 &a) const {
    return a.x()*u() + a.y()*v() + a.z()*w();
}
void Onb::build_from_w(const Vec3& n) {
    axis[2] = n.normalized();
    Vec3 a = (fabs(w().x()) > 0.9) ? Vec3(0,1,0) : Vec3(1,0,0);
    axis[1] = w().cross(a).normalized();
    axis[0] = w().cross(v()).normalized();
}

Onb::Onb() {}

