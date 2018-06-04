//
// Created by mateusz on 03.06.18.
//

#ifndef GUARDUAUX_LANG_MOVEGRAPHFUNC_H
#define GUARDUAUX_LANG_MOVEGRAPHFUNC_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"
#include "Graphic/GraphicObject.h"

namespace Guarduaux {
    class MoveGraphicFunc : public Statement {
    public:
        MoveGraphicFunc(std::shared_ptr<GraphicObject> obj,
                         std::vector<std::unique_ptr<Expresion> > coord )
        {
            //graphicObj_ = std::move(obj);
            coordinates_ = std::move(coord);
            graphicObj_ = obj;
        }


        Return run() override{
            std::vector<int> move_vec = {
                    coordinates_.at(0)->calculate()->get(),
                    coordinates_.at(1)->calculate()->get(),
                    coordinates_.at(2)->calculate()->get()
            };
            graphicObj_->move(move_vec);
            return Return();
        }

    private:
        std::shared_ptr<GraphicObject> graphicObj_;
        std::vector<std::unique_ptr<Expresion> > coordinates_;
    };
}

#endif //GUARDUAUX_LANG_MOVEGRAPHFUNC_H
