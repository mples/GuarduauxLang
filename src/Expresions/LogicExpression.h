#pragma once

#include <memory>
#include <list>
#include "Program/Variable.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class LogicExpression : public Expresion {
	public:
		LogicExpression(ExprPtr and_expr) {
			andExprList_.push_back(std::move(and_expr));
		}

        std::shared_ptr<Variable> calculate() override{

            std::shared_ptr<Variable> ret_var = andExprList_.begin()->get()->calculate();
			andExprList_.pop_front();
			while( !andExprList_.empty()){
				ret_var = ret_var->or_op(andExprList_.begin()->get()->calculate());
				andExprList_.pop_front();
			}

			return ret_var;
		}


		void addAlternativeAddExpr(ExprPtr and_expr) {
			andExprList_.push_back(std::move(and_expr));
		}

	private:
		std::list<ExprPtr> andExprList_;
	};
}