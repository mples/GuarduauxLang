//
// Created by mateusz on 02.06.18.
//
#include "Context.h"
#include "Exception.h"

using namespace Guarduaux;

Context::Context() {}

Context::Context(const Context &&other)noexcept {
    variables_ = std::move(other.variables_);
}

Context::Context(const Context *other) {
    variables_ = std::move(other->variables_);
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


