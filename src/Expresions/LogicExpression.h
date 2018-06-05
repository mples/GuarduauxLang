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
			auto iterator = andExprList_.begin();
            std::shared_ptr<Variable> ret_var = iterator->get()->calculate();
			++iterator;
			while( iterator != andExprList_.end()){
				ret_var = ret_var->or_op(iterator->get()->calculate());
				++iterator;
			}

			return ret_var;
		}


		void addAlternativeAddExpr(ExprPtr and_expr) {
			andExprList_.push_back(std::move(and_expr));
		}

	private:
		std::vector<ExprPtr> andExprList_;
	};
}