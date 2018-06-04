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
        ScaleGraphicFunc(std::shared_ptr<GraphicObject> obj,
                        std::vector<std::unique_ptr<Expresion> > coord ) {
            graphicObj_.swap(obj);
            obj.swap(graphicObj_);
            coordinates_ = std::move(coord);
        }


        Return run() override{
            std::vector<int> vec = {
                    coordinates_.at(0)->calculate()->get(),
                    coordinates_.at(1)->calculate()->get(),
                    coordinates_.at(2)->calculate()->get()
            };
            if(graphicObj_)
                graphicObj_->scale(vec);
            return Return();
        }

    private:
        std::shared_ptr<GraphicObject> graphicObj_;
        std::vector<std::unique_ptr<Expresion> > coordinates_;
    };
}

#endif //GUARDUAUX_LANG_SCALEGRAPHFUNC_H
