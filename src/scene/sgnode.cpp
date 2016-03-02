
#include "sgnode.h"

namespace ps {
namespace scene {

Material::Material() {
    Ka = vec4f(1.0f);
    Kd = vec4f(1.0f);
    Ks = vec4f(1.0f);
    shininess = 4.0f;
}

Material::Material(const Material &rhs) {
    this->copyfrom(rhs);
}

void Material::copyfrom(const Material &rhs) {
    Ka = rhs.Ka;
    Kd = rhs.Kd;
    Ks = rhs.Ks;
    shininess = rhs.shininess;
}

Material& Material::operator=(const Material& rhs) {
    this->copyfrom(rhs);
    return *this;
}

Material Material::red() {
    Material m;
    m.Ka = vec4f(0.8, 0, 0, 1);
    m.Kd = vec4f(0.8, 0, 0, 1);
    m.Ks = vec4f(1, 1, 1, 1);
    m.shininess = 8.0f;

    return m;
}

Material Material::green() {
    Material m;
    m.Ka = vec4f(0, 0.8, 0, 1);
    m.Kd = vec4f(0, 0.8, 0, 1);
    m.Ks = vec4f(1, 1, 1, 1);
    m.shininess = 8.0f;

    return m;
}

Material Material::blue() {
    Material m;
    m.Ka = vec4f(0, 0, 0.8, 1);
    m.Kd = vec4f(0, 0, 0.8, 1);
    m.Ks = vec4f(1, 1, 1, 1);
    m.shininess = 8.0f;

    return m;
}

/////////////////////////////////////////////////////////////////////////////
HitRecord::HitRecord() {
    bounces = 0;
    t = 0.0f;   
}

HitRecord::HitRecord(const HitRecord& rhs) {
    this->copyfrom(rhs);
}

void HitRecord::copyfrom(const HitRecord& rhs) {
    this->bounces = rhs.bounces;
    this->material = rhs.material;
    this->n = rhs.n;
    this->p = rhs.p;
    this->t = rhs.t;
}

//ops
HitRecord& HitRecord::operator=(const HitRecord& rhs) {
    this->copyfrom(rhs);
    return (*this);
}



}
}
