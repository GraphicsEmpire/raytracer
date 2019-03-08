/*
 * raytracer_cpuonly.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: pourya
 */

#include <chrono>
#include "base/base.h"
#include "glbackend/glselect.h"
#include "sgraytracer_cpuonly.h"
#include "sgnode.h"

using namespace ps::scene;


namespace ps {
namespace raytracer {

RTCamera::RTCamera() {
    m_pos = vec3f(0.0f, 0.0f, 0.0f);
    m_hspan = RangeF(-2.0f, 2.0f);
    m_vspan = RangeF(-2.0f, 2.0f);
    m_focal_length = 5.0f;
}

RTCamera::RTCamera(const RTCamera& rhs) {
    copyfrom(rhs);
}

RTCamera::~RTCamera() {}

void RTCamera::copyfrom(const RTCamera& rhs) {
    m_pos = rhs.m_pos;
    m_hspan = rhs.m_hspan;
    m_vspan = rhs.m_vspan;
    m_focal_length = rhs.m_focal_length;
}

//////////////////////////////////////////////////////////
RayTracer::RayTracer() {
    setup(kDefaultFrameWidth, kDefaultFrameHeight, 1);
}

RayTracer::RayTracer(int nx, int ny, int super_samples) {
    setup(nx, ny, super_samples);
}

void RayTracer::setup(int nx, int ny, int supersamples) {

    m_prootnode = NULL;
    m_nx = nx;
    m_ny = ny;
    m_supersamps = supersamples;

    //other vars
    m_bgcolor = Color::grey();

    U32 id = GLTexture::create_checkerboard(m_nx, m_ny);
    vec3i dim(m_nx, m_ny, 4);
    m_glframebuffer.set(dim, id);
}

RayTracer::~RayTracer() {

    cleanup();
}

void RayTracer::cleanup() {

    m_glframebuffer.cleanup();

}

bool RayTracer::addlight(const vec3f& pos, const Color& color) {
    if(m_vlights.size() == max_light_sources) {
        vlogwarn("unable to add new light sources, max light source has reached");
        return false;
    }

    LightSource light;
    light.pos = pos;
    light.color = color.toVec4f();
    m_vlights.push_back(light);

    return true;
}

void RayTracer::removelight(int idx) {
    if(idx < 0 || idx >= (int)m_vlights.size()) {
        vlogerror("invalid light index");
        return;
    }

    m_vlights.erase(m_vlights.begin() + idx);
}

bool RayTracer::light(int idx, LightSource& lout) {
    if(idx < 0 || idx >= (int)m_vlights.size()) {
        vlogerror("invalid light index");
        return false;
    }

    lout = m_vlights[idx];
    return true;
}



Color RayTracer::phong_shading(const HitRecord& hitrec) {

    vec4f lo(0.0f);
    
    //adding ambient light
    lo = vec4f::mul(hitrec.material.Ka, vec4f(.2f));

    //evalute phong
    vec3f v = (m_camera.pos() - hitrec.p).normalized();

    //consider all light sources
    for(U32 k=0; k < m_vlights.size(); k++) {

        vec3f l = (m_vlights[k].pos - hitrec.p).normalized();

        //h is half way between v and l
        vec3f h = (v + l).normalized();

        //Diffused: Diff is the angle between n and l
        float cosDiff = max(vec3f::dot(hitrec.n, l), 0.0f);

        //Specular: Spec is the angle between n and h
        float cosSpec = max(vec3f::dot(hitrec.n, h), 0.0f);

        
        vec4f dif = vec4f::mul(hitrec.material.Kd, m_vlights[k].color) * cosDiff;
        vec4f spec = vec4f::mul(hitrec.material.Ks, m_vlights[k].color) * pow(cosSpec, hitrec.material.shininess);

//        vec4f cofactor = (hitrec.material.Kd + hitrec.material.Ks * pow(cosTheta, hitrec.material.shininess));
//        vec4f phong = vec4f::mul(cofactor, m_vlights[k].color) * cosAlpha;

        lo = lo + dif + spec;
    }
    
    lo = vec4f::clamped(lo, 0.0f, 1.0f);

   // return Color::blue();
    return Color(lo);
}




bool RayTracer::run() {    
    if(m_prootnode == NULL) {
        vlogerror("root node is not set.");
        return false;
    }
    
    Pixmap pix(m_nx, m_ny);
    
    //parallel using openmp    
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(dynamic,1) collapse(2)
    for(int x = 0; x < m_nx; x++) {
        for(int y = 0; y < m_ny; y++) {

            float u = m_camera.hspan().lower() + m_camera.hspan().length() * (((float)x + 0.5f) / (float) m_nx);
            float v = m_camera.vspan().lower() + m_camera.vspan().length() * (((float)y + 0.5f) / (float) m_ny);

            vec3f end(u, v, m_camera.focallength());

            Ray r(m_camera.pos(), end - m_camera.pos());
            
            //final hit record
            HitRecord hitrec_final;
            
            Color lo(0.0f);            
            
            //the range along the ray
            RangeF range(0.0f, FLT_MAX);

            //hit all nodes in the scene
            int ctIntersected = m_prootnode->hit(r, range, hitrec_final);

            //process color and translucency
            if(ctIntersected == 0)
                lo = m_bgcolor;
            else {
                lo = phong_shading(hitrec_final);
            }

            //put pixel
            pix.putp(x, y, lo);
        }
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    m_duration_micro_seconds = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    //update the texture
    m_glframebuffer.set(pix);
    glutPostRedisplay();
    return true;
}

}
}
