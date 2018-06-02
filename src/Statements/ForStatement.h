#pragma once

#include "Expresions/Expresion.h"
#include "Statements/BlockStatement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;
using AssignPtr = std::unique_ptr<Guarduaux::AssignStatement>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;

namespace Guarduaux {

	class ForStatement : public Statement {
	public:
		ForStatement(ExprPtr cond, BlockPtr loop_block, StatemPtr init_instr , StatemPtr loop_instr ){

		}

		ForStatement(ExprPtr expr, BlockPtr if_block, BlockPtr else_block) {

		}

		Return run() override {

		}

	private:
		ExprPtr condition_;
		AssignPtr initStatem_;
		AssignPtr loopStatem_;
		BlockPtr loopBlock_;
	};

}