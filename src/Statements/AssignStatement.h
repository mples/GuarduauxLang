#pragma once

#include "Expresions/Expresion.h"
#include "Expresions/LogicExpression.h"
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