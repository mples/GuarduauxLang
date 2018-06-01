#pragma once

#include <memory>
#include <list>
#include "Expresions/Expresion.h"
#include "Token/TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class MultipExpression : public Expresion {
	public:
		MultipExpression(ExprPtr simpl_assnb_expr){
			multipExprVec_.push_back(std::move(simpl_assnb_expr));
		}

		Variable calculate() override{
			Variable ret_var = multipExprVec_.begin()->get()->calculate();
			multipExprVec_.pop_front();

			for( const TokenType& t : addativOperatorVec_){
				if(t == TokenType::MUL_OP){
					ret_var = ret_var * multipExprVec_.begin()->get()->calculate();
					multipExprVec_.pop_front();
				}
				else {
					ret_var = ret_var / multipExprVec_.begin()->get()->calculate();
					multipExprVec_.pop_front();
				}
			}
            return ret_var;
		}


		void addSimpleAssignExpr(ExprPtr simple_expr, TokenType ret_op ){
			multipExprVec_.push_back(std::move(simple_expr));
			addativOperatorVec_.push_back(ret_op);
		}

	private:
		std::list<ExprPtr> multipExprVec_;
		std::list<TokenType> addativOperatorVec_;
	};
}