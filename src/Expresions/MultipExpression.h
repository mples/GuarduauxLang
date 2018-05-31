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

		}

		Variable calculate() override{

		}


		void addSimpleAssignExpr(ExprPtr add_expr, TokenType ret_op = TokenType::UNIDENTIFIED){

		}

	private:
		std::list<ExprPtr> multipExprList_;
		std::list<TokenType> addativOperatorList_;
	};
}