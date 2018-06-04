//
// Created by mateusz on 04.06.18.
//

#ifndef GUARDUAUX_LANG_BOX_H
#define GUARDUAUX_LANG_BOX_H

#include <vector>

#include "GraphicObject.h"
namespace Guarduaux {
    class Box : public GraphicObject {
    public:
        Box() = default;
        Box(std::vector<int> pos,std::vector<int> col, std::vector<int> dim );
        void draw () override ;
    private:
        std::vector<int> pos_;
        std::vector<int> col_;
        std::vector<int> dim_;
    };

}



#endif //GUARDUAUX_LANG_BOX_H
