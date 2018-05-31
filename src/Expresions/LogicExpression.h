#pragma once

#include <memory>
#include <list>
#include "Program/Variable.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class LogicExpression : public Expresion {
	public:
		LogicExpression(ExprPtr add_expr) {

		}

		Variable calculate() override{
			return Variable();
		}


		void addAlternativeAddExpr(ExprPtr add_expr) {

		}

	private:
		std::list<ExprPtr> addExprList_;
	};
}