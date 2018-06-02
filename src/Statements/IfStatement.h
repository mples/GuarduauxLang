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
			condition_ = std::move(expr);
			ifBlock_ = std::move(if_block);
		}

		IfStatement(ExprPtr expr, BlockPtr if_block, BlockPtr else_block) {
			condition_ = std::move(expr);
			ifBlock_ = std::move(if_block);
			elseBlock_ = std::move(else_block);
		}

		Return run() override {
			if( condition_->calculate()->isTrue()){
				return ifBlock_->run();
			}
			else {
				if(elseBlock_){
					return elseBlock_->run();
				}
				else {
					return Return();
				}
			}
		}

	private:
		ExprPtr condition_;
		BlockPtr ifBlock_;
		BlockPtr elseBlock_;
	};

}