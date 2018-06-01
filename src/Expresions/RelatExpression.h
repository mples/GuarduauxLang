#pragma once

#include <memory>
#include <list>
#include "Expresions/Expresion.h"
#include "Token/TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class RelatExpression : public Expresion {
	public:
		RelatExpression(ExprPtr simple_log_expr) {
			simpleLogicExprList_.push_back(std::move(simple_log_expr) );
		}

		std::shared_ptr<Variable> calculate() override {
			std::shared_ptr<Variable> ret_var = simpleLogicExprList_.begin()->get()->calculate();
			simpleLogicExprList_.pop_front();

			for( const TokenType& t : relationOperatorsList_){
				if(t == TokenType::GOE_OP){
					*ret_var = *ret_var >= *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}
				else if(t == TokenType::GTH_OP){
					*ret_var = *ret_var > *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}
				else if(t == TokenType::LTH_OP){
					*ret_var = *ret_var < *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}
				else if(t == TokenType::LOE_OP){
					*ret_var = *ret_var <= *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}
				else if(t == TokenType::EQU_OP){
					*ret_var = *ret_var == *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}
				else if(t == TokenType::NEQ_OP){
					*ret_var = *ret_var != *(simpleLogicExprList_.begin()->get()->calculate());
					simpleLogicExprList_.pop_front();
				}

			}
			return ret_var;
		}


		void addNextSimpleLogExpr(ExprPtr simple_log_expr, TokenType op = TokenType::UNIDENTIFIED) {
			simpleLogicExprList_.push_back(std::move(simple_log_expr) );
			relationOperatorsList_.push_back(op);
		}

	private:
		std::list<ExprPtr> simpleLogicExprList_;
		std::list<TokenType> relationOperatorsList_;
	};
}