
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
    m.Ka = vec4f(0.1, 0.1, 0.1, 0.1);
    m.Kd = vec4f(0.8, 0, 0, 0);
    m.Ks = vec4f(1, 1, 1, 1);
    m.shininess = 80.0f;

    return m;
}


}
}
