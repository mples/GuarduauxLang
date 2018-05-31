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
#include "Expresions/Expresion.h"
#include "Program/Exception.h"



using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	using StatemPtr = std::unique_ptr<Statement>;

	class BlockStatement : public Statement {
	public:
		BlockStatement() = default;
		BlockStatement(std::vector<StatemPtr> instr, BlockStatement * prt_block){

		}
		BlockStatement(BlockStatement * prt_block) {
            parentBlock_ = prt_block;
		}
		BlockStatement(const BlockStatement &) = delete;
		BlockStatement &operator=(BlockStatement &) = delete;
		BlockStatement(BlockStatement && other) = default;

		void addInstr(StatemPtr statem){
		    instructions_.push_back(std::move(statem) );
		}

		void addVar(std::string& var_name, ExprPtr expr){
		   // variables_.insert(std::make_pair(var_name, Variable(expr->calculate())  ) );
		}

		Variable& findVar(std::string& var_name){
		    /*if(variables_.find(var_name) != variables_.end()){
                return variables_.at(var_name);
		    }
		    else if(parentBlock_){
                return parentBlock_->findVar(var_name);
		    }
		    else {
		        throw Exception(var_name + "is not a valid variable");
		    }*/

		}

		bool isValidVar( std::string& var_name){
			/*if(variables_.find(var_name) != variables_.end()){
				return true;
			}
			else {
				if(parentBlock_){
					return parentBlock_->isValidVar(var_name);
				}
			}
            return false;*/

		}

		Return run() override{
		    // TODO variables
            /*for(const auto & func : instructions_){
                Return ret = func->run();
                if(ret.type_ == Return::VARIABLE){
                    return ret;
                }
            }*/
            return Return();

		}

	private:
		BlockStatement * parentBlock_;
		std::vector<StatemPtr> instructions_;
		std::unordered_map < std::string, Variable> variables_;
	};

}


