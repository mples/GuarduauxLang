#pragma once

#include <memory>
#include <list>
#include "Expresion.h"
#include "Token/TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class AssignableExpression : public Expresion {
	public:
		AssignableExpression(ExprPtr multp_expr) {
			multipExprList_.push_back(std::move(multp_expr));
		}

        std::shared_ptr<Variable> calculate() override {
		    auto it = multipExprList_.begin();
            std::shared_ptr<Variable> ret_var = it->get()->calculate();
			++it;

			for( const TokenType& t : addativOperatorList_){
				if(t == TokenType::ADD_OP){
					ret_var = ret_var->add(it->get()->calculate());
                    ++it;
				}
				else {
					ret_var = ret_var->sub(it->get()->calculate());
                    ++it;
				}
			}
			return ret_var;

		}


		void addMultExpr(ExprPtr multp_expr, TokenType add_op ) {
			multipExprList_.push_back(std::move(multp_expr));
			addativOperatorList_.push_back(add_op);
		}

	private:
		std::vector<ExprPtr> multipExprList_;
		std::vector<TokenType> addativOperatorList_;
	};
}