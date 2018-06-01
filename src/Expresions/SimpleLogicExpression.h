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

		Variable calculate() override {
			if(negated_){
				return !(assbleExpr_->calculate());
			}
			else {
				return assbleExpr_->calculate();
			}
		}

	private:
		bool negated_;
		ExprPtr assbleExpr_;
	};
}