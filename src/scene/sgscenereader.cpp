/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sgscenereader.cpp
 * Author: pouryas
 * 
 * Created on March 1, 2016, 5:14 PM
 */

//#include <memory>
#include "sgscenereader.h"

#include "logger.h"
#include "base/directory.h"
#include "yaml-cpp/yaml.h"

using namespace ps::base;

namespace ps {
namespace scene {

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

SGSceneReader::SGSceneReader() {
}

SGSceneReader::SGSceneReader(const string& strFP) {
    read_scene(strFP);
}

SGSceneReader::SGSceneReader(const SGSceneReader& orig) {
}

SGSceneReader::~SGSceneReader() {
}

void SGSceneReader::init_settings() {

    //reset all to default values
    m_settings.screen_dim = vec2i(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

int SGSceneReader::read_scene(const string& strFP) {

    int tokens_found = 0;

    if(!ps::dir::FileExists(AnsiStr(strFP.c_str())))
        return tokens_found;
    
    //init settings to default values
    init_settings();

    //load from file
    YAML::Node sgmodel = YAML::LoadFile(strFP);

    //read screen dimension
    if(sgmodel["screen_dim"]) {
        YAML::Node screen_dim = sgmodel["screen_dim"];                
        vloginfo("screen_dim = %d x %d", screen_dim[0].as<int>(), screen_dim[1].as<int>());                
        m_settings.screen_dim = vec2i(screen_dim[0].as<int>(), screen_dim[1].as<int>());

        tokens_found++;
    }

    //render type
    if(sgmodel["render_type"].as<string>() == "raytrace") {

        vloginfo("Request raytracer");
        //m_prt = make_unique<RayTracer>(m_settings.screen_dim.x, m_settings.screen_dim.y);

        tokens_found++;
    }
    
    
    return tokens_found;
}

}
}
