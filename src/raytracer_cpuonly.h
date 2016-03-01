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
#include "sgnode.h"
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

    int add_node(SGNode* pnode) {
        m_vnodes.push_back(pnode);
        return ((int)m_vnodes.size() - 1);
    }


    //lights
    bool addlight(const vec3f& pos, const Color& color);
    void removelight(int idx);
    bool light(int idx, LightSource& lout);
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

    //cam pos
    vec3f m_cam_pos;   
    RangeF m_cam_horz_span;
    RangeF m_cam_vert_span;
    float m_cam_focal_length;


    //background color
    Color m_bgcolor;

    //nodes
    vector<SGNode*> m_vnodes;

    //lights
    vector<LightSource> m_vlights;

    //output
    GLTexture m_glframebuffer;
};


}
}

#endif /* RAYTRACER_CPUONLY_H_ */
