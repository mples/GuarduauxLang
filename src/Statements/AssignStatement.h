#pragma once1

#include "Expresions/Expresion.h"
#include "Expresions/LogicExpression.h"
#include "Statement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class AssignStatement : public Statement {
	public:

		AssignStatement(std::shared_ptr<Variable> var, ExprPtr expr, ExprPtr index){
			var_ = var;
			expr_ = std::move(expr);
			varIndex_ = std::move(index);
		}
		Return run() override {
            std::shared_ptr<Variable> var = expr_->calculate();
			if(varIndex_){
				if(var->size()){
					var_->get( varIndex_->calculate()->get()) = var->get();
				}
				else {
					throw Exception ("Cannot assign multidimensional variable to single dimensional variable");
				}
			}
			else {
				*var_ = *var;
			}
			return Return();
		}

	private:

		ExprPtr expr_;
		std::shared_ptr<Variable> var_;
		ExprPtr varIndex_;
	};

}