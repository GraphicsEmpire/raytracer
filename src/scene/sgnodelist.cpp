/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SGNodeList.cpp
 * Author: pouryas
 * 
 * Created on March 1, 2016, 4:45 PM
 */

#include "sgnodelist.h"

namespace ps {
    namespace scene {


SGNodeList::SGNodeList() {
}


SGNodeList::~SGNodeList() {
}

        
AABB SGNodeList::compute_aabb() {
    if(m_vnodes.size() == 0)
        return m_aabb;
    
    m_aabb = m_vnodes[0]->compute_aabb();
    
    for(int i=1; i < (int)m_vnodes.size(); i++) {
        m_aabb = m_aabb.united(m_vnodes[i]->compute_aabb());
    }
    
    return m_aabb;
}

int SGNodeList::hit(const Ray& r, RangeF interval, HitRecord& hitrec) {
            
        float mint = FLT_MAX;
        int res = -1;

            
        //the range along the ray
        RangeF range(0.0f, FLT_MAX);

        //hit all nodes in the scene
        for (int inode = 0; inode < (int) m_vnodes.size(); inode++) {
            HitRecord hitrec_current;

            res = m_vnodes[inode]->hit(r, range, hitrec_current);
            if (res > 0) {
                //apply shading equation
                if (hitrec.t < mint) {
                    mint = hitrec.t;
                    range.setUpper(mint);

                    hitrec = hitrec_current;
                }

                break;
            }
        }

        return res;

    }
}
}