#pragma once

//#include <utility>
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
#include "Program/Context.h"



using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;

namespace Guarduaux {

	using StatemPtr = std::unique_ptr<Statement>;

	class BlockStatement : public Statement {
	public:
		BlockStatement() = default;
		BlockStatement(std::vector<StatemPtr> instr, BlockStatement * prt_block){

		}
		BlockStatement(Context* c ) {
			if(c){
				context_ = std::make_unique<Context>( c );
			}
			else {
				context_ = std::make_unique<Context>();
			}
		}
		BlockStatement(const BlockStatement &) = delete;
		BlockStatement &operator=(BlockStatement &) = delete;
		BlockStatement(BlockStatement && other) = default;

		void addInstr(StatemPtr statem){
		    instructions_.push_back(std::move(statem) );
		}

		void addVar(std::string& var_name, ExprPtr expr){
			context_->addVar(var_name,std::move(expr) );
		}

		void addVar(std::string& var_name, std::shared_ptr<Variable> var){
			context_->addVar(var_name,var);
		}

		void updateVars(std::unordered_map < std::string, std::shared_ptr<Variable> > params){
			context_->updateVars(params);
		}

		std::shared_ptr<Variable> findVar(std::string& var_name){
			return context_->findVar(var_name);
		}

		bool isValidVar( std::string& var_name){
			context_->isValidVar(var_name);
		}

		Return run() override{
            for(const auto & func : instructions_){
                Return ret = func->run();
				if(ret.type_ == Return::OBJECT){
					context_->updateObj(ret.objName,ret.object_);
				}
                else if(ret.type_ == Return::VARIABLE){
                    return ret;
                }
            }

            return Return();

		}

		const std::unique_ptr<Context> &getContext_() const {
			return context_;
		}

    private:
        std::vector<StatemPtr> instructions_;
		std::unique_ptr<Context> context_;

	};

}


