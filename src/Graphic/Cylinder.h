//
// Created by mateusz on 04.06.18.
//

#ifndef GUARDUAUX_LANG_CYLINDER_H
#define GUARDUAUX_LANG_CYLINDER_H

#include <vector>

#include "GraphicObject.h"
namespace Guarduaux {
    class Cylinder : public GraphicObject {
    public:
        Cylinder() = default;
        Cylinder(std::vector<int> pos,std::vector<int> col, std::vector<int> dim );
        void draw () override ;

        void move(std::vector<int> vec) override ;
        void scale(std::vector<int> vec) override ;
        void chngcol(std::vector<int> vec) override ;
    private:
        std::vector<int> pos_;
        std::vector<int> col_;
        std::vector<int> dim_;
    };

}


#endif //GUARDUAUX_LANG_CYLINDER_H
