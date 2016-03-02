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

#include "sgscenereader.h"
#include "yaml-cpp/yaml.h"

namespace ps {
namespace scene {

SGSceneReader::SGSceneReader() {
}

SGSceneReader::SGSceneReader(const string& strFP) {
    read_scene(strFP);
}

SGSceneReader::SGSceneReader(const SGSceneReader& orig) {
}

SGSceneReader::~SGSceneReader() {
}


int SGSceneReader::read_scene(const string& strFP) {
    
    YAML::Node sgmodel = YAML::LoadFile(strFP);
    
    
    return 0;
}

}
}