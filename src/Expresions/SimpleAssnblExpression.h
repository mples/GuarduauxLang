#pragma once

#include <memory>
#include <utility>
#include <list>
#include <optional>
#include "Token/Token.h"
#include "Expresions/Expresion.h"
#include "Token/TokenType.h"


using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;


namespace Guarduaux {

	class SimpleAssnblExpression : public Expresion {
	public:

		SimpleAssnblExpression(StatemPtr func_call) {
			funcCall_ = std::move(func_call);
		}

		SimpleAssnblExpression(std::shared_ptr<Variable> var) {
			var_ = var;
		}

		SimpleAssnblExpression(std::shared_ptr<Variable> var, ExprPtr index ) {
            index_ = std::move(index);
            var_ = var;
		}
		SimpleAssnblExpression(const SimpleAssnblExpression&) = delete;
		SimpleAssnblExpression(SimpleAssnblExpression && other) :
			funcCall_(std::move(other.funcCall_)), var_(other.var_), index_(std::move(index_))
		{

		}

		std::shared_ptr<Variable> calculate() override {
            if(funcCall_){
                return funcCall_->run().variable_;
            }
            else if(var_ ){
                return var_ ;
            }
            else if( index_){
				return std::make_shared<Variable>(var_->get(index_->calculate()->get()));
            }
            else {
            	throw Exception("Variable does not contain a value");
            }
		}

	private:
		//std::optional<StatemPtr> funcCall_;
		//std::optional<Variable*> var_;
		//std::optional <  ExprPtr > index_ ;
		StatemPtr funcCall_;
		std::shared_ptr<Variable> var_ = nullptr;
		ExprPtr index_ ;
	};
}

