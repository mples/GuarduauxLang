#pragma once

#include <memory>
#include <list>
#include "Expresion.h"
#include "Variable.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class AddExpression : public Expresion {
	public:
		AddExpression(ExprPtr relat_expr) {

		}

		Variable calculate() override{

		}

		void addNewRelatExpr(ExprPtr add_expr){

		}

	private:
		std::list<ExprPtr> relatExprList_;
	};
}