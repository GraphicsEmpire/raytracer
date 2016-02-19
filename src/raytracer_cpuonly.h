/*
 * raytracer_cpuonly.h
 *
 *  Created on: Feb 16, 2016
 *      Author: pouryas
 */

#ifndef RAYTRACER_CPUONLY_H_
#define RAYTRACER_CPUONLY_H_

#include "common/logger.h"

namespace sda {

class RayTracer {
public:
	RayTracer();
	virtual ~RayTracer();

	bool run();

};


}

#endif /* RAYTRACER_CPUONLY_H_ */
