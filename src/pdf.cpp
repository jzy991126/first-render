//
// Created by jzy99 on 2020/12/9.
//

#include "pdf.h"

Cosine_pdf::Cosine_pdf(const Vec3 &w) { uvw.build_from_w(w); }

double Cosine_pdf::value(const Vec3 &direction) const {
    auto cosine = direction.normalized().dot(uvw.w());
    return (cosine <= 0) ? 0 : cosine/pi;
}

Vec3 Cosine_pdf::generate() const {
    return uvw.local(random_cosine_direction());
}
