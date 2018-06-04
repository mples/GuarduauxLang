//
// Created by mateusz on 04.06.18.
//

#ifndef GUARDUAUX_LANG_GRAPHICCONTEXT_H
#define GUARDUAUX_LANG_GRAPHICCONTEXT_H

#include <memory>
#include <unordered_map>
#include "Program/Variable.h"
#include "Expresions/Expresion.h"
#include "Graphic/GraphicObject.h"
using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

    class GraphicContext {
    public:
        GraphicContext();
        explicit GraphicContext(const GraphicContext* other );

        GraphicContext(const GraphicContext&& other )noexcept ;


        void updateObj(std::string& obj_name, std::shared_ptr<GraphicObject> obj);

        void addObj(std::string& obj_name, Token obj_type);


    private:
        std::unordered_map < std::string, std::shared_ptr<GraphicObject> > graphObjects_;
    };

}


#endif //GUARDUAUX_LANG_GRAPHICCONTEXT_H
