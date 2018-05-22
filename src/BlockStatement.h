#pragma once

//#include <utility>
//#include <memory>
//#include <list>
//#include <unordered_map>
//#include "Statement.h"
//#include "Expresion.h"
//#include "Variable.h"
//#include "Return.h"
#include <memory>
#include <list>
#include <unordered_map>
#include "Statement.h"
#include "Expresion.h"



using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	using StatemPtr = std::unique_ptr<Statement>;

	class BlockStatement : public Statement {
	public:
		BlockStatement() = default;
		BlockStatement(std::vector<StatemPtr> instr, BlockStatement * prt_block){

		}
		BlockStatement(BlockStatement * prt_block) {

		}
		BlockStatement(const BlockStatement &) = delete;
		BlockStatement &operator=(BlockStatement &) = delete;
		BlockStatement(BlockStatement && other) = default;

		void addInstr(StatemPtr statem){

		} //TODO
		void addVar(std::string& var_name, ExprPtr index){

		} //TODO

		Variable& findVar(std::string var_name){

		}

		bool isValidVar( std::string var_name){

		}

		Return run() override{

		}

	private:
		Statement * parentBlock_;
		std::vector<StatemPtr> instructions_;
		std::unordered_map < std::string, Variable> variables_;
	};

}


