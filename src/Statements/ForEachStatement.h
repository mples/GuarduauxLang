#pragma once

#include <memory>
#include "Expresions/Expresion.h"
#include "Statements/BlockStatement.h"
#include "Statements/AssignStatement.h"

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