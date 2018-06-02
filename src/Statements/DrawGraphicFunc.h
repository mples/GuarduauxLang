//
// Created by mateusz on 03.06.18.
//

#ifndef GUARDUAUX_LANG_DRAWGRAPHICFUNC_H
#define GUARDUAUX_LANG_DRAWGRAPHICFUNC_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"

namespace Guarduaux {
    class DrawGraphicFunc : public Statement {
    public:
        DrawGraphicFunc(std::string obj,
                        std::vector<std::unique_ptr<Expresion> > pos,
                        std::vector<std::unique_ptr<Expresion> >dim,
                        std::vector<std::unique_ptr<Expresion> > col ) {
            graphicObj_ = obj;
            position_ = std::move(pos);
            dimension_ = std::move(dim);
            color_ = std::move(col);
        }


        Return run() override{
            //TODO
        }

    private:
        std::string graphicObj_;
        std::vector<std::unique_ptr<Expresion> > position_;
        std::vector<std::unique_ptr<Expresion> > dimension_;
        std::vector<std::unique_ptr<Expresion> > color_;
    };
}

#endif //GUARDUAUX_LANG_DRAWGRAPHICFUNC_H
