//
// Created by jzy99 on 2020/12/9.
//

#ifndef TESTASSIMP_PDF_H
#define TESTASSIMP_PDF_H
#include "firstrender.h"
#include "utils.h"
#include "onb.h"

class Pdf {
public:
    virtual ~Pdf() {}

    virtual double value(const Vec3& direction) const = 0;
    virtual Vec3 generate() const = 0;

};


class Cosine_pdf : public Pdf {
public:
    Cosine_pdf(const Vec3& w);

    virtual double value(const Vec3& direction) const override;

    virtual Vec3 generate() const override;

public:
    Onb uvw;
};

#endif //TESTASSIMP_PDF_H
