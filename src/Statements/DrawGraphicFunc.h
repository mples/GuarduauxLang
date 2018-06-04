//
// Created by mateusz on 03.06.18.
//

#ifndef GUARDUAUX_LANG_DRAWGRAPHICFUNC_H
#define GUARDUAUX_LANG_DRAWGRAPHICFUNC_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"
#include "../Graphic/Box.h"
#include "../Graphic/Cylinder.h"

namespace Guarduaux {
    class DrawGraphicFunc : public Statement {
    public:
        DrawGraphicFunc(std::string obj,
                        std::string obj_name,
                        std::vector<std::unique_ptr<Expresion> > pos,
                        std::vector<std::unique_ptr<Expresion> >dim,
                        std::vector<std::unique_ptr<Expresion> > col ) {
            graphicObj_ = obj;
            objName_ = obj_name;
            position_ = std::move(pos);
            dimension_ = std::move(dim);
            color_ = std::move(col);
        }


        Return run() override{

            std::vector<int> pos;
            std::vector<int> col;
            std::vector<int> dim;

            for(const auto & ex : position_){
                pos.push_back(ex->calculate()->get());
            }

            for(const auto & ex : dimension_){
                dim.push_back(ex->calculate()->get());
            }

            for(const auto & ex : color_){
                col.push_back(ex->calculate()->get());
            }

            std::shared_ptr<GraphicObject> figure;

            if(graphicObj_ == "box"){
                figure = std::make_shared<Box>(pos,col,dim);
            }
            else {
                figure = std::make_shared<Cylinder>(pos,col,dim);
            }


            return Return(objName_, figure);
        }

    private:
        std::string graphicObj_;
        std::string objName_;
        std::vector<std::unique_ptr<Expresion> > position_;
        std::vector<std::unique_ptr<Expresion> > dimension_;
        std::vector<std::unique_ptr<Expresion> > color_;
    };
}

#endif //GUARDUAUX_LANG_DRAWGRAPHICFUNC_H
