//
// Created by mateusz on 04.06.18.
//

#include "GraphicContext.h"

#include "Graphic/Box.h"
#include "Graphic/Cylinder.h"

Guarduaux::GraphicContext::GraphicContext() {}


Guarduaux::GraphicContext::GraphicContext(const Guarduaux::GraphicContext *other) {
    graphObjects_ = std::move(other->graphObjects_);
}

Guarduaux::GraphicContext::GraphicContext(const Guarduaux::GraphicContext &&other) noexcept {
    graphObjects_ = std::move(other.graphObjects_);
}

void Guarduaux::GraphicContext::updateObj(std::string &obj_name, std::shared_ptr<Guarduaux::GraphicObject> obj) {
    //graphObjects_.insert_or_assign(obj_name,obj);

    if(graphObjects_.find(obj_name) != graphObjects_.end()){
        (graphObjects_.at(obj_name) ) = std::move(obj);
    }

}

void Guarduaux::GraphicContext::addObj(std::string &obj_name, Token obj_type) {
    if(obj_type.type_ == TokenType::BOX){
        graphObjects_.insert(std::make_pair(obj_name, std::make_shared<Box>()));
    }
    else {
        graphObjects_.insert(std::make_pair(obj_name, std::make_shared<Cylinder>() ));
    }

}

const std::unordered_map<std::string, std::shared_ptr<Guarduaux::GraphicObject>> &
Guarduaux::GraphicContext::getGraphObjects_() const {
    return graphObjects_;
}

std::shared_ptr<Guarduaux::GraphicObject> Guarduaux::GraphicContext::findObj(std::string &name) {
    if(graphObjects_.count(name)){
        return graphObjects_.at(name);
    }
}

