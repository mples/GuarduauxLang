#pragma once

#include <memory>
#include "Expresion.h"
#include "BlockStatement.h"
#include "AssignStatement.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;
using AssignPtr = std::unique_ptr<Guarduaux::AssignStatement>;

namespace Guarduaux {

	class ForEachStatement : public Statement {
	public:
		ForEachStatement(std::string coll, std::string iter, BlockPtr loop_block){

		}

		

		Return run() override {

		}

	private:
		std::string collection_;
		std::string iterator_;
		BlockPtr loopBlock_;
	};

}