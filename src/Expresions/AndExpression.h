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
			auto iterator = relatExprList_.begin();
            std::shared_ptr<Variable> ret_var = iterator->get()->calculate();
            ++iterator;
            while( iterator != relatExprList_.end() ){
				ret_var = ret_var->and_op(iterator->get()->calculate());
                ++iterator;
            }

            return ret_var;

		}

		void addNewRelatExpr(ExprPtr relat_expr){
			relatExprList_.push_back(std::move(relat_expr));
		}

	private:
		std::vector<ExprPtr> relatExprList_;
	};
}