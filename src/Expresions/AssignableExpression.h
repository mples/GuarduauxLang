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

		}

		Variable calculate() override {

		}


		void addMultExpr(ExprPtr add_expr, TokenType ret_op = TokenType::UNIDENTIFIED) {

		}

	private:
		std::list<ExprPtr> multipExprList_;
		std::list<TokenType> addativOperatorList_;
	};
}