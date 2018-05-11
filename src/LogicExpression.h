#pragma once

#include <memory>
#include <list>
#include "Variable.h"
#include "Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class LogicExpression : public Expresion {
	public:
		LogicExpression(ExprPtr add_expr) {

		}

		Variable calculate() override{

		}


		void addAlternativeAddExpr(ExprPtr add_expr) {

		}

	private:
		std::list<ExprPtr> addExprList_;
	};
}