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
#include "sgtransform.h"

using namespace ps::base;

namespace ps {
namespace scene {

class Material {
public:
    Material();
    Material(const Material& rhs);

    /*!
     * \brief copyfrom another material
     * \param rhs
     */
    void copyfrom(const Material& rhs);

    //ops
    Material& operator=(const Material& rhs);

    //predefined materials
    static Material red();
    static Material green();
    static Material blue();
public:
    vec4f Ka;
    vec4f Kd;
    vec4f Ks;
    float shininess;
};

/*!
 *	HitRecord is a storage for material properties and the surface geometry at the point of
 * intersection with a view ray.
 */
class HitRecord {
public:
    HitRecord();
    HitRecord(const HitRecord& rhs);
    
    void copyfrom(const HitRecord& rhs);
    
    //ops
    HitRecord& operator=(const HitRecord& rhs);


public:
    float t;
    vec3f p;
    vec3f n;
    int bounces;
    Material material;
};

/*!
 * \brief The SGNode class
 */
class SGNode {
public:
    SGNode() {}
    virtual ~SGNode() {}

    //get aabb
    virtual AABB compute_aabb() = 0;
    virtual int hit(const Ray& r, RangeF interval, HitRecord& hitrec) = 0;

    /*!
     * \brief aabb is the axis-aligned bounding box for the model
     * \return
     */
    AABB aabb() const {return m_aabb;}

    //mtrl
    Material material() const {return m_mtrl;}
    void set_material(const Material& mtrl) {m_mtrl = mtrl;}

    //transform
    const SGTransform& ctransform() const { return m_transform;}
    SGTransform& transform() { return m_transform;}

protected:
    AABB m_aabb;
    Material m_mtrl;    
    SGTransform m_transform;
};


}
}


#endif /* SGNODE_H_ */
