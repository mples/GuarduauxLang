#pragma once

#include <memory>
#include <list>
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class SimpleLogicExpression : public Expresion {
	public:
		SimpleLogicExpression( ExprPtr assbl_expr, bool neg = false) {

		}

		Variable calculate() override {

		}

	private:
		bool neqated_;
		ExprPtr assbleExprList_;
	};
}