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
#include "pixmap.h"
#include "glbackend/gltexture.h"

#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512

using namespace std;
using namespace ps::scene;
using namespace ps::base;
using namespace ps::opengl;


namespace ps {
namespace raytracer {


class RayTracer {
public:
	RayTracer();
	RayTracer(int nx, int ny, int super_samples = 1);
	virtual ~RayTracer();

	void setup(int nx, int ny, int supersamples = 1);

	bool run();

	//return framebuffer
	GLTexture& framebuffer() { return m_gltex;}

protected:
	int m_nx;
	int m_ny;
	int m_supersamps;

	vector<SGNode*> m_vnodes;
	GLTexture m_gltex;
};


}
}

#endif /* RAYTRACER_CPUONLY_H_ */
