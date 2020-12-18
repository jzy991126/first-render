//
// Created by jzy99 on 2020/12/9.
//

#ifndef TESTASSIMP_ONB_H
#define TESTASSIMP_ONB_H

#include "firstrender.h"

class Onb {
public:
    Onb();

    inline Vec3 operator[](int i) const { return axis[i]; }

    Vec3 u() const;
    Vec3 v() const;
    Vec3 w() const;

    Vec3 local(double a, double b, double c) const;

    Vec3 local(const Vec3& a) const;

    void build_from_w(const Vec3&);

public:
    Vec3 axis[3];
};






#endif //TESTASSIMP_ONB_H
