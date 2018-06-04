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
        ChngcolGraphicFunc(std::shared_ptr<GraphicObject>obj,
                        std::vector<std::unique_ptr<Expresion> > col ) {
            graphicObj_ = obj;
            color_ = std::move(col);
        }


        Return run() override{
            std::vector<int> vec = {
                    color_.at(0)->calculate()->get(),
                    color_.at(1)->calculate()->get(),
                    color_.at(2)->calculate()->get()
            };
            if(graphicObj_)
                graphicObj_->chngcol(vec);
            return Return();
        }

    private:
        std::shared_ptr<GraphicObject> graphicObj_;
        std::vector<std::unique_ptr<Expresion> > color_;
    };
}

#endif //GUARDUAUX_LANG_CHNGCOLGRAPHFUNC_H
