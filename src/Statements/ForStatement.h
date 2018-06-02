#pragma once

#include "Expresions/Expresion.h"
#include "Statements/BlockStatement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;

namespace Guarduaux {

	class ForStatement : public Statement {
	public:
		ForStatement(ExprPtr cond, BlockPtr loop_block, StatemPtr init_instr , StatemPtr loop_instr ){
			condition_ = std::move(cond);
			loopBlock_ = std::move(loop_block);
			initStatem_ = std::move(init_instr);
			loopStatem_= std::move(loop_instr);
		}

		Return run() override {
			initStatem_->run();
			while( condition_->calculate()->isTrue()){
				loopBlock_->run();
				loopStatem_->run();
			}

			return Return();
		}

	private:
		ExprPtr condition_;
		StatemPtr initStatem_;
		StatemPtr loopStatem_;
		BlockPtr loopBlock_;
	};

}