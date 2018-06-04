//
// Created by mateusz on 04.06.18.
//

#include "GraphicContext.h"

#include "Graphic/Box.h"

Guarduaux::GraphicContext::GraphicContext() {}


Guarduaux::GraphicContext::GraphicContext(const Guarduaux::GraphicContext *other) {
    graphObjects_ = std::move(other->graphObjects_);
}

Guarduaux::GraphicContext::GraphicContext(const Guarduaux::GraphicContext &&other) noexcept {
    graphObjects_ = std::move(other.graphObjects_);
}

void Guarduaux::GraphicContext::updateObj(std::string &obj_name, std::shared_ptr<Guarduaux::GraphicObject> obj) {

    if(graphObjects_.find(obj_name) != graphObjects_.end()){
        std::shared_ptr<GraphicObject> found_obj = graphObjects_.at(obj_name);
        *found_obj = *obj;
    }
}

void Guarduaux::GraphicContext::addObj(std::string &obj_name, Token obj_type) {
    if(obj_type.type_ == TokenType::BOX){
        graphObjects_.insert(std::make_pair(obj_name, std::make_shared<Box>()));
    }
    else {
        //TODO
    }

}

