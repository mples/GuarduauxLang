//
// Created by mateusz on 04.06.18.
//

#include "Program.h"

void Guarduaux::Program::addFunc(std::unique_ptr <FuncDef> function) {
    functions.insert({function->getId(), std::move(function)});
}

bool Guarduaux::Program::isVaildFunc(const std::string &func_name) {
    return functions.find(func_name) != functions.end();
}

std::shared_ptr<Guarduaux::FuncDef> Guarduaux::Program::getFuncDef(const std::string &func_name) {
    return functions.at(func_name);
}

Guarduaux::Return Guarduaux::Program::run() {
    auto scene_func = functions.find("scene");
    if(scene_func != functions.end()){
        Return ret = scene_func->second->run();
        graphicContext_ = scene_func->second->getGraphicContext_();
        return ret;
    }
    else {
        throw Exception("No scene function");
    }

}

void Guarduaux::Program::renderScene() {
    for(const auto & ob : graphicContext_->getGraphObjects_()){
        ob.second->draw();
    }

}
