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

using namespace std;

namespace ps {
namespace scene {
    

class SGSceneReader {
public:
    SGSceneReader();
    SGSceneReader(const string& strFP);
    SGSceneReader(const SGSceneReader& orig);
    virtual ~SGSceneReader();
    
    
    int read_scene(const string& strFP);
private:

};

}   
}

#endif /* SGSCENEREADER_H */

