//
// Created by mateusz on 03.06.18.
//

#ifndef GUARDUAUX_LANG_SCALEGRAPHFUNC_H
#define GUARDUAUX_LANG_SCALEGRAPHFUNC_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"

namespace Guarduaux {
    class ScaleGraphicFunc : public Statement {
    public:
        ScaleGraphicFunc(std::string obj,
                        std::vector<std::unique_ptr<Expresion> > coord ) {
            graphicObj_ = obj;
            coordinates_ = std::move(coord);
        }


        Return run() override{
            //TODO
        }

    private:
        std::string graphicObj_;
        std::vector<std::unique_ptr<Expresion> > coordinates_;
    };
}

#endif //GUARDUAUX_LANG_SCALEGRAPHFUNC_H