/*
 * SGSphere.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: pouryas
 */

#include <c++/4.1.2/bits/stl_iterator_base_funcs.h>
#include <c++/4.1.2/cmath>
#include <algorithm>

#include "sgsphere.h"

namespace ps {
namespace scene {

SGSphere::SGSphere(): m_center(0,0,0), m_radius(1.0f) {
	// TODO Auto-generated constructor stub
    
}

SGSphere::SGSphere(const vec3f& center, float radius): m_center(center), m_radius(radius) {
    
}

SGSphere::~SGSphere() {
	// TODO Auto-generated destructor stub
}

void SGSphere::compute_aabb() {    
    vec3f expand(m_radius * 1.2f);
    m_aabb.set(m_center - expand, m_center + expand);
}


int SGSphere::hit(const Ray& r, RangeF interval, HitRecord& hitrec) {
    
    //A = d.d
    //B = 2d.(e-c)
    //C = (e-c).(e-c) - R2
    vec3f e_min_c = r.start - m_center;
    
//    float a = vec3f::dot(r.direction, r.direction);
//    float b = 2.0f * vec3f::dot(r.direction, e_min_c);
//    float c = vec3f::dot(e_min_c, e_min_c) - m_radius * m_radius;
//    
//    float discriminant = b * b - 4.0f * a * c;
    
    /*
    if(discriminant < 0.0f)
        return 0;

    float ds = sqrt(discriminant);
    float t1 = (-1.0f * b + ds) / (2.0f * a);
    float t2 = (-1.0f * b - ds) / (2.0f * a);
    
    hitrec.bounces ++;
    
    hitrec.t = MATHMIN(t1, t2);
    hitrec.p = r.point(hitrec.t);
    //hitrec.n = (hitrec.p - m_center).normalized();
    
    */
}

}
}
