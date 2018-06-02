//
// Created by mateusz on 31.05.18.
//

#ifndef GUARDUAUX_LANG_CONTEXT_H
#define GUARDUAUX_LANG_CONTEXT_H

#include <memory>
#include <unordered_map>
#include "Program/Variable.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

    class Context {
    public:
        Context();
        Context(std::vector<std::string> & params);
        Context(const Context* other );
        Context(const Context&& other )noexcept ;

        void addVar(std::string& var_name, ExprPtr index);
        void addVar(std::string& var_name);
        void addVar(std::string& var_name, std::shared_ptr<Variable> var);
        void updateVars(std::unordered_map < std::string, std::shared_ptr<Variable> > params);

        std::shared_ptr<Variable> findVar(std::string var_name);

        bool isValidVar( std::string& var_name);

    private:
        std::unordered_map < std::string, std::shared_ptr<Variable> > variables_;
    };

}

#endif //GUARDUAUX_LANG_CONTEXT_H
