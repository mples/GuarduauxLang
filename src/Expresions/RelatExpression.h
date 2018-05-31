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

		}

		Variable calculate() override {

		}


		void addNextSimpleLogExpr(ExprPtr add_expr, TokenType ret_op = TokenType::UNIDENTIFIED) {

		}

	private:
		std::list<ExprPtr> simpleLogicExprList_;
		std::list<TokenType> raltionOperatorsList_;
	};
}