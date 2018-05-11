#pragma once

#include "Expresion.h"
#include "LogicExpression.h"
#include "Statement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	class AssignStatement : public Statement {
	public:

		AssignStatement(Variable& var, ExprPtr expr, ExprPtr index){

		}
		AssignStatement(Variable& var, ExprPtr expr) {

		}
		Return run() override {

		}

	private:

		ExprPtr expr_;
		Variable* var_;
		ExprPtr varIndex_;
	};

}