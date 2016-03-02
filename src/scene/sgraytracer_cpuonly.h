/*
 * raytracer_cpuonly.h
 *
 *  Created on: Feb 16, 2016
 *      Author: pouryas
 */

#ifndef RAYTRACER_CPUONLY_H_
#define RAYTRACER_CPUONLY_H_

#include <vector>
#include "common/logger.h"
#include "base/ray.h"
#include "sgnode.h"
#include "base/pixmap.h"
#include "sgnodelist.h"
#include "glbackend/gltexture.h"

#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512

using namespace std;
using namespace ps::scene;
using namespace ps::base;
using namespace ps::opengl;


namespace ps {
namespace raytracer {

struct LightSource {
    vec3f pos;
    vec4f color;
    
    LightSource& operator=(const LightSource& rhs) {
        *this = rhs;
        return *this;
    }
};

/*!
 * \brief The RTCamera class represents a camera for RayTracer engine
 */
class RTCamera {
public:
    RTCamera();
    RTCamera(const RTCamera& rhs);
    virtual ~RTCamera();

    void copyfrom(const RTCamera& rhs);

    //setters
    void set_pos(const vec3f& pos) { m_pos = pos;}
    void set_hspan(const RangeF& hspan) { m_hspan = hspan;}
    void set_vspan(const RangeF& vspan) { m_vspan = vspan;}
    void set_focallength(float fl) { m_focal_length = fl; }

    //getters
    vec3f pos() const { return m_pos;}
    RangeF hspan() const { return m_hspan;}
    RangeF vspan() const { return m_vspan;}
    float focallength() const { return m_focal_length;}

protected:
    vec3f m_pos;
    RangeF m_hspan;
    RangeF m_vspan;
    float m_focal_length;
};

/*!
 * \brief The RayTracer class
 */
class RayTracer {
public:
    RayTracer();
    RayTracer(int nx, int ny, int super_samples = 1);
    virtual ~RayTracer();

    void setup(int nx, int ny, int supersamples = 1);

    /*!
     * \brief run execute raytracer
     * \return
     */
    bool run();

    //return framebuffer
    GLTexture& framebuffer() { return m_glframebuffer;}

    //camera
    RTCamera& camera() { return m_camera;}
    const RTCamera& const_camera() const { return m_camera;}

    //lights
    bool addlight(const vec3f& pos, const Color& color);
    void removelight(int idx);
    bool light(int idx, LightSource& lout);

    void set_rootnode(SGNodeList* proot) { m_prootnode = proot;}

public:
    static const int max_light_sources = 8;

protected:
    void cleanup();

    /*!
     * \brief phong_shading performs a phong shading implementation using the specified hitrecord
     * and the supplied light sources. The material properties are transferred from the hitrecord.
     * \param hitrec
     * \return 4 channel color value for the pixel buffer
     */
    Color phong_shading(const HitRecord& hitrec);

protected:
    int m_nx;
    int m_ny;
    int m_supersamps;

    //camera
    RTCamera m_camera;

    //background color
    Color m_bgcolor;

    //models
    SGNodeList* m_prootnode;

    //lights
    vector<LightSource> m_vlights;

    //output
    GLTexture m_glframebuffer;
};


}
}

#endif /* RAYTRACER_CPUONLY_H_ */
