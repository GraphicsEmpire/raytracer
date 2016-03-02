/*
 * raytracer_cpuonly.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: pouryas
 */

#include "base/base.h"
#include "glbackend/glselect.h"
#include "sgraytracer_cpuonly.h"
#include "sgnode.h"

using namespace ps::scene;


namespace ps {
namespace raytracer {

RayTracer::RayTracer() {
    setup(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1);
}

RayTracer::RayTracer(int nx, int ny, int super_samples) {
    setup(nx, ny, super_samples);
}

void RayTracer::setup(int nx, int ny, int supersamples) {

    m_nx = nx;
    m_ny = ny;
    m_supersamps = supersamples;

    //other vars
    m_bgcolor = Color::grey();
    m_cam_pos = vec3f(0.0f, 0.0f, 0.0f);
    m_cam_horz_span = RangeF(-2.0f, 2.0f);
    m_cam_vert_span = RangeF(-2.0f, 2.0f);
    m_cam_focal_length = 5.0f;

    U32 id = GLTexture::create_checkerboard(m_nx, m_ny);
    vec3i dim(m_nx, m_ny, 4);
    m_glframebuffer.set(dim, id);
}

RayTracer::~RayTracer() {

    cleanup();
}

void RayTracer::cleanup() {

    m_glframebuffer.cleanup();

    for(U32 i=0; i < m_vnodes.size(); i++) {
        SAFE_DELETE(m_vnodes[i]);
    }
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
    vec3f v = (m_cam_pos - hitrec.p).normalized();

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
    vloginfo("Starting primary rays at resolution [%u x %u] SS= %u", m_nx, m_ny, m_supersamps);


    U32 total_primary_rays = m_nx * m_ny * m_supersamps;

    Pixmap pix(m_nx, m_ny);

    
    //parallel using openmp
    #pragma omp parallel for schedule(dynamic,1) collapse(2)
    for(int x = 0; x < m_nx; x++) {
        for(int y = 0; y < m_ny; y++) {

            float u = m_cam_horz_span.lower() + m_cam_horz_span.length() * (((float)x + 0.5f) / (float) m_nx);
            float v = m_cam_vert_span.lower() + m_cam_vert_span.length() * (((float)y + 0.5f) / (float) m_ny);

            vec3f end(u, v, m_cam_focal_length);

            Ray r(m_cam_pos, end - m_cam_pos);
            
            //final hit record
            HitRecord hitrec_final;
            

            Color lo(0.0f);
            float mint = FLT_MAX;
            int ctIntersected = 0;
            
            //the range along the ray
            RangeF range(0.0f, FLT_MAX);

            //hit all nodes in the scene
            for(int inode=0; inode < (int)m_vnodes.size(); inode++) {
                HitRecord hitrec_current;
                
                int count = m_vnodes[inode]->hit(r, range, hitrec_current);
                if(count > 0) {
                    //apply shading equation
                    if(hitrec_final.t < mint) {
                        mint = hitrec_final.t;
                        range.setUpper(mint);
                        
                        hitrec_final = hitrec_current;
                    }
                    ctIntersected++;
                    break;
                }
            }

            //process color and translucency
            if(ctIntersected == 0)
                lo = m_bgcolor;
            else {
                lo = phong_shading(hitrec_final);
            }

            //put pixel
            pix.putp(x, y, lo);
        }
        
//        U32 finished = x * m_ny;
//        float ratio = (float) finished / (float) total_primary_rays;
//        vloginfo("progress = %.2f", ratio * 100.0f);
    }

    vloginfo("Finished all");
    //update texture
    m_glframebuffer.set(pix);
    glutPostRedisplay();



    //finalize image
    pix.putp(0, 0, Color::green());
    pix.putp(pix.width()-1, pix.height()-1, Color::red());
    m_glframebuffer.set(pix);

    glutPostRedisplay();


    return true;
}

}
}
