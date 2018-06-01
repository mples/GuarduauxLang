#pragma once

#include <memory>
#include <list>
#include "Expresions/Expresion.h"
#include "Token/TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class MultipExpression : public Expresion {
	public:
		MultipExpression() = delete;
		explicit MultipExpression(ExprPtr simpl_assnb_expr);
		MultipExpression(const MultipExpression&) = delete;
		MultipExpression(MultipExpression && other)noexcept;

        std::shared_ptr<Variable> calculate() override;


		void addSimpleAssignExpr(ExprPtr simple_expr, TokenType ret_op );

	private:
		std::list<ExprPtr> multipExprVec_;
		std::list<TokenType> addativOperatorVec_;
	};

}