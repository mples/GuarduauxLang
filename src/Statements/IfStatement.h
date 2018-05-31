#pragma once

#include<memory>
#include "Expresions/Expresion.h"
#include "Statements/BlockStatement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;

namespace Guarduaux {

	class IfStatement : public Statement {
	public:
		IfStatement(ExprPtr expr, BlockPtr if_block) {

		}

		IfStatement(ExprPtr expr, BlockPtr if_block, BlockPtr else_block) {

		}

		Return run() override {

		}

	private:
		ExprPtr condition_;
		BlockPtr ifBlock_;
		BlockPtr elseBlock_;
	};

}