//
// Created by mateusz on 31.05.18.
//

#ifndef GUARDUAUX_LANG_RETURNSTATEMENT_H
#define GUARDUAUX_LANG_RETURNSTATEMENT_H

#include <memory>
#include "Statement.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

    class ReturnStatem : public Statement {
    public:
        ReturnStatem(ExprPtr expr) {}

        Return run() override {

        }
    private:
        ExprPtr returnedExpr_;
    };
}
#endif //GUARDUAUX_LANG_RETURNSTATEMENT_H
