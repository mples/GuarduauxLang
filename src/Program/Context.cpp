//
// Created by mateusz on 02.06.18.
//
#include "Context.h"
#include "Exception.h"

using namespace Guarduaux;

Context::Context() {
    graphicContext_ = std::make_shared<GraphicContext>();
}

Context::Context(std::vector<std::string> &params ){
    for(auto& par : params){
        addVar(par);
    }
    graphicContext_ = std::make_shared<GraphicContext>(); //TODO FIX
}

Context::Context(const Context &&other)noexcept {
    variables_ = other.variables_;
    graphicContext_ = other.graphicContext_;
}

Context::Context(const Context *other) {
    variables_ = other->variables_;
    graphicContext_ = other->graphicContext_;
}

void Context::addVar(std::string &var_name) {
    variables_.insert(std::make_pair(var_name, std::make_shared<Variable>())   );
}

void Context::addVar(std::string &var_name, ExprPtr index) {
    variables_.insert(std::make_pair(var_name, std::make_shared<Variable>())   );
}

std::shared_ptr<Variable> Context::findVar(std::string var_name) {
    if(variables_.find(var_name) != variables_.end()){
        return variables_.at(var_name);
    }
    else {
        throw Exception(var_name + " is not a valid variable");
    }
}

bool Context::isValidVar(std::string &var_name) {
    return variables_.find(var_name) != variables_.end();
}

void Context::addVar(std::string &var_name, std::shared_ptr<Variable> var) {
    variables_.insert(std::make_pair(var_name, var)   );
}

void Context::updateVars(std::unordered_map<std::string, std::shared_ptr<Variable> > params) {
    for( const auto & p : params){
        std::shared_ptr<Variable> var = findVar(p.first);
        *var = *p.second;
        //variables_.insert_or_assign(p.first, p.second);
    }
}

void Context::updateObj(std::string &obj_name, std::shared_ptr<GraphicObject> obj) {
    graphicContext_->updateObj(obj_name, obj);

}

void Context::addObj(std::string &obj_name, Token obj_type) {
    graphicContext_->addObj(obj_name,obj_type);
}



