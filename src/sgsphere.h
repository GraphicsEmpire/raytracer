/*
 * SGSphere.h
 *
 *  Created on: Feb 24, 2016
 *      Author: pouryas
 */

#ifndef SGSPHERE_H_
#define SGSPHERE_H_

#include "sgnode.h"

namespace ps {
namespace scene {

class SGSphere : public SGNode {
public:
	SGSphere();
        SGSphere(const vec3f& center, float radius);
	virtual ~SGSphere();
        
        void compute_aabb();
        int hit(const Ray& r, RangeF interval, HitRecord& hitrec);
        
protected:
    vec3f m_center;
    float m_radius;
};

}
}

#endif /* SGSPHERE_H_ */
