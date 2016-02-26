/*
 * raytracer_cpuonly.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: pouryas
 */

#include <GL/freeglut_std.h>

#include "raytracer_cpuonly.h"
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


	U32 id = GLTexture::create_checkerboard(m_nx, m_ny);
	vec3i dim(m_nx, m_ny, 4);
	m_gltex.set(dim, id);
}

RayTracer::~RayTracer() {


}

bool RayTracer::run() {
	vloginfo("Starting primary rays at resolution [%u x %u] SS= %u", m_nx, m_ny, m_supersamps);

	vec3f eye_pos(0, 0, 0);
	vec3f eye_dir(0, 0, 1);
	float image_plane_dist = 4.0f;
        U32 total_primary_rays = m_nx * m_ny * m_supersamps;

	//left - right = -1, 1
	//bottom - top = -1, 1
	Pixmap pix(m_nx, m_ny);

	for(int x = 0; x < m_nx; x++) {
		for(int y = 0; y < m_ny; y++) {

			float u = -1.0f + 2.0 * (((float)x + 0.5f) / (float) m_nx);
			float v = -1.0f + 2.0 * (((float)y + 0.5f) / (float) m_ny);

			vec3f end(u, v, image_plane_dist);

			Ray r(eye_pos, end - eye_pos);
                        HitRecord hitrec;
                        
                        hitrec.bounces = 0;
                        hitrec.rgba = Color::grey();

                        //hit all nodes in the scene
			for(int inode=0; inode < (int)m_vnodes.size(); inode++) {			
				RangeF range;
				int count = m_vnodes[inode]->hit(r, range, hitrec);

				if(count > 0) {

				}
				else {
					hitrec.rgba = Color::grey();
				}
			}
                        
                        //put pixel
                        pix.putp(x, y, hitrec.rgba);
		}

		//update texture
		m_gltex.set(pix);
                
                U32 finished = x * m_ny;
                float ratio = (float) finished / (float) total_primary_rays;
                vloginfo("progress = %.2f", ratio * 100.0f);
	}
        
        
        //finalize image
        pix.putp(0, 0, Color::green());
        pix.putp(pix.width()-1, pix.height()-1, Color::red());
        m_gltex.set(pix);
        
        glutPostRedisplay();
        

	return true;
}

}
}

