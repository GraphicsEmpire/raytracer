/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sgscenereader.h
 * Author: pouryas
 *
 * Created on March 1, 2016, 5:14 PM
 */

#ifndef SGSCENEREADER_H
#define SGSCENEREADER_H

#include <string>
#include <memory>
#include "base/vec.h"
#include "sgraytracer_cpuonly.h"

using namespace std;
using namespace ps;
using namespace ps::base;
using namespace ps::raytracer;
//using namespace ps::dir;

namespace ps {
namespace scene {

class SGSettings {
public:
    SGSettings() {}

public:
    vec2i screen_dim;
};

class SGSceneReader {
public:
    SGSceneReader();
    SGSceneReader(const string& strFP);
    SGSceneReader(const SGSceneReader& orig);
    virtual ~SGSceneReader();
    
    /*!
     * \brief read_scene
     * \param strFP
     * \return
     */
    int read_scene(const string& strFP);

    //settings
    const SGSettings& const_settings() const { return m_settings;}
    SGSettings& settings() { return m_settings;}

    //raytracer
    RayTracer* raytracer() { return m_prt.get(); }


protected:
    void init_settings();

private:
    SGSettings m_settings;

    std::unique_ptr<RayTracer> m_prt;
};

}   
}

#endif /* SGSCENEREADER_H */

