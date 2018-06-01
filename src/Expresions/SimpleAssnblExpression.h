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

		SimpleAssnblExpression(Variable* var) {
			var_ = var;
		}

		SimpleAssnblExpression(Variable& var) {
			var_ = &var;
		}

		SimpleAssnblExpression(std::pair<Variable*, ExprPtr > varAtIndex ) {
            varAtIndex_ = std::move(varAtIndex);
		}

		Variable calculate() override {
            if(funcCall_){
                return funcCall_.value()->run().variable_;
            }
            else if(var_){
                return *(var_.value() );
            }
            else if( varAtIndex_){
                return varAtIndex_.value().first->get(
                		varAtIndex_.value().second->calculate().get().calculate() );
            }
            else {
            	throw Exception("Variable does not contain a value");
            }
		}

	private:
		std::optional<StatemPtr> funcCall_;
		std::optional<Variable*> var_;
		std::optional < std::pair<Variable*, ExprPtr > > varAtIndex_ ;
	};
}

