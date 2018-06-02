#pragma once

#include <memory>
#include <list>
#include "Expresion.h"
#include "Program/Variable.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class AndExpression : public Expresion {
	public:
		AndExpression(ExprPtr relat_expr) {
			relatExprList_.push_back(std::move(relat_expr));
		}

        std::shared_ptr<Variable> calculate() override{

            std::shared_ptr<Variable> ret_var = relatExprList_.begin()->get()->calculate();
            relatExprList_.pop_front();
            while( !relatExprList_.empty()){
				ret_var = ret_var->and_op(relatExprList_.begin()->get()->calculate());
                relatExprList_.pop_front();
            }

            return ret_var;

		}

		void addNewRelatExpr(ExprPtr relat_expr){
			relatExprList_.push_back(std::move(relat_expr));
		}

	private:
		std::list<ExprPtr> relatExprList_;
	};
}