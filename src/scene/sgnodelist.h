/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SGNodeList.h
 * Author: pouryas
 *
 * Created on March 1, 2016, 4:45 PM
 */

#ifndef SGNODELIST_H
#define SGNODELIST_H

#include <vector>
#include "sgnode.h"

using namespace std;

namespace ps {
    namespace scene {

    
    class SGNodeList : public SGNode {
    public:
        SGNodeList();    
        virtual ~SGNodeList();
        
        //get aabb
        AABB compute_aabb() override;
        int hit(const Ray& r, RangeF interval, HitRecord& hitrec) override;

        
        int add_node(SGNode* pnode) {
            m_vnodes.push_back(pnode);
            return ((int)m_vnodes.size() - 1);
        }

    protected:
        vector<SGNode*> m_vnodes;

    };

    }
}
#endif /* SGNODELIST_H */

