//
// Created by mateusz on 03.06.18.
//

#ifndef GUARDUAUX_LANG_CHNGCOLGRAPHFUNC_H
#define GUARDUAUX_LANG_CHNGCOLGRAPHFUNC_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"

namespace Guarduaux {
    class ChngcolGraphicFunc : public Statement {
    public:
        ChngcolGraphicFunc(std::string obj,
                        std::vector<std::unique_ptr<Expresion> > col ) {
            graphicObj_ = obj;
            color_ = std::move(col);
        }


        Return run() override{
            //TODO
        }

    private:
        std::string graphicObj_;
        std::vector<std::unique_ptr<Expresion> > color_;
    };
}

#endif //GUARDUAUX_LANG_CHNGCOLGRAPHFUNC_H
