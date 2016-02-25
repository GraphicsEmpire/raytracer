/*
 * raytracer_cpuonly.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: pouryas
 */

#include "raytracer_cpuonly.h"

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

}

RayTracer::~RayTracer() {


}

bool RayTracer::run() {

	vec3f eye_pos(0, 0, 0);
	vec3f eye_dir(0, 0, 1);
	float image_plane_dist = 4.0f;

	//left - right = -1, 1
	//bottom - top = -1, 1

	for(int x = 0; x < m_nx; x++) {
		for(int y = 0; y < m_ny; y++) {

			float u = -1.0f + 2.0 * (((float)x + 0.5f) / (float) m_nx);
			float v = -1.0f + 2.0 * (((float)y + 0.5f) / (float) m_ny);

			vec3f end(u, v, image_plane_dist);

			Ray r(eye_pos, end - eye_pos);


			for(int i=0; i < (int)m_vnodes.size(); i++) {

				HitRecord hitrec;
				RangeF range;
				int count = m_vnodes[i]->hit(r, range, hitrec);

				if(count > 0) {

				}
			}
		}
	}

	return true;
}

}
}

