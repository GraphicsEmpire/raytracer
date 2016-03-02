/*
 * SGSphere.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: pouryas
 */

#include <algorithm>
#include "sgsphere.h"
#include "logger.h"

namespace ps {
namespace scene {

SGSphere::SGSphere(): m_center(0,0,0), m_radius(1.0f) {
	// TODO Auto-generated constructor stub
    compute_aabb();
}

SGSphere::SGSphere(const vec3f& center, float radius): m_center(center), m_radius(radius) {
    compute_aabb();
}

SGSphere::~SGSphere() {
	// TODO Auto-generated destructor stub
}

AABB SGSphere::compute_aabb() {    
    vec3f expand(m_radius * 1.2f);
    m_aabb.set(m_center - expand, m_center + expand);
    
    return m_aabb;
}


int SGSphere::hit(const Ray& r, RangeF interval, HitRecord& hitrec) {
    
    RangeF hitrange_aabb;
    if(!m_aabb.intersect(r, interval, hitrange_aabb))
        return 0;

    //A = d.d
    //B = 2d.(e-c)
    //C = (e-c).(e-c) - R2
    vec3f e_min_c = r.start - m_center;
    
    float a = vec3f::dot(r.direction, r.direction);
    float b = 2.0f * vec3f::dot(r.direction, e_min_c);
    float c = vec3f::dot(e_min_c, e_min_c) - m_radius * m_radius;
    
    //solve quadratic equation
    float discriminant = b * b - 4.0f * a * c;

    //if negative there will be no roots!
    if(discriminant < 0.0f)
        return 0;

    //roots
    float ds = sqrt(discriminant);
    float t1 = (-1.0f * b + ds) / (2.0f * a);
    float t2 = (-1.0f * b - ds) / (2.0f * a);
    
    bool is1 = interval.isInside(t1);
    bool is2 = interval.isInside(t2);
    if(!is1 && !is2)
        return 0;
    
    if(is1 && is2) {
        hitrec.t = MATHMIN(t1, t2);          
    }
    else if(is1)
        hitrec.t = t1;
    else if(is2)
        hitrec.t = t2;
    
    //set hitrec values
    hitrec.bounces ++;       
    hitrec.p = r.point(hitrec.t);
    hitrec.n = (hitrec.p - m_center).normalized();
    hitrec.material = this->material();
    
    if(hitrec.t < 0.0) {
        vlogwarn("hit sphere behind camera!");
    }
    
    return 1;
}

}
}
