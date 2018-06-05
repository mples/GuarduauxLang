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
		    auto it = simpleLogicExprList_.begin();
			std::shared_ptr<Variable> ret_var = it->get()->calculate();
			++it;

			for( const TokenType& t : relationOperatorsList_){
				if(t == TokenType::GOE_OP){
					ret_var = ret_var->goe(it->get()->calculate());
					++it;
				}
				else if(t == TokenType::GTH_OP){
					ret_var = ret_var->gth(it->get()->calculate());
					++it;
				}
				else if(t == TokenType::LTH_OP){
					ret_var = ret_var->lth(it->get()->calculate());
					++it;
				}
				else if(t == TokenType::LOE_OP){
					ret_var = ret_var->loe(it->get()->calculate());
					++it;
				}
				else if(t == TokenType::EQU_OP){
					ret_var = ret_var->equ(it->get()->calculate());
					++it;
				}
				else if(t == TokenType::NEQ_OP){
					ret_var = ret_var->neq(it->get()->calculate());
					++it;
				}

			}
			return ret_var;
		}


		void addNextSimpleLogExpr(ExprPtr simple_log_expr, TokenType op = TokenType::UNIDENTIFIED) {
			simpleLogicExprList_.push_back(std::move(simple_log_expr) );
			relationOperatorsList_.push_back(op);
		}

	private:
		std::vector<ExprPtr> simpleLogicExprList_;
		std::vector<TokenType> relationOperatorsList_;
	};
}