#pragma once

#include <memory>
#include <list>
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class SimpleLogicExpression : public Expresion {
	public:
		SimpleLogicExpression( ExprPtr assbl_expr, bool neg = false) {
			assbleExpr_ = std::move(assbl_expr);
			negated_ = neg;
		}

		std::shared_ptr<Variable> calculate() override {
			std::shared_ptr<Variable> var = assbleExpr_->calculate();
			if(negated_){
				return var->negate();
			}
			else {
				return var;
			}
		}

	private:
		bool negated_;
		ExprPtr assbleExpr_;
	};
}