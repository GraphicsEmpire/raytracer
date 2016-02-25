/*
 * sgnode.h
 *
 *  Created on: Feb 24, 2016
 *      Author: pouryas
 */

#ifndef SGNODE_H_
#define SGNODE_H_

#include "base/ray.h"
#include "base/interval.h"
#include "base/color.h"
#include "base/aabb.h"

using namespace ps::base;

namespace ps {
namespace scene {

/*!
 *	Final hit record
 */
struct HitRecord {
	float t;
	int bounces;
	Color rgba;
};


class SGNode {
public:
	SGNode() {}
	virtual ~SGNode() {}

	virtual int hit(const Ray& r, RangeF interval, HitRecord& hitrec) = 0;

	AABB aabb() const {return m_aabb;}
protected:
	AABB m_aabb;
};


}
}


#endif /* SGNODE_H_ */
