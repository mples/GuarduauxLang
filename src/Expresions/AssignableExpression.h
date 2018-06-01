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

		Variable calculate() override {
			Variable ret_var = multipExprList_.begin()->get()->calculate();
			multipExprList_.pop_front();

			for( const TokenType& t : addativOperatorList_){
				if(t == TokenType::ADD_OP){
					ret_var = ret_var + multipExprList_.begin()->get()->calculate();
                    multipExprList_.pop_front();
				}
				else {
					ret_var = ret_var - multipExprList_.begin()->get()->calculate();
                    multipExprList_.pop_front();
				}
			}
			return ret_var;

		}


		void addMultExpr(ExprPtr multp_expr, TokenType add_op = TokenType::UNIDENTIFIED) {
			multipExprList_.push_back(std::move(multp_expr));
			addativOperatorList_.push_back(add_op);
		}

	private:
		std::list<ExprPtr> multipExprList_;
		std::list<TokenType> addativOperatorList_;
	};
}