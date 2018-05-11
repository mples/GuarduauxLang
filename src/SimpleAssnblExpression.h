#pragma once

#include <memory>
#include <list>
#include "Token.h"
#include "Expresion.h"
#include "TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;


namespace Guarduaux {

	class SimpleAssnblExpression : public Expresion {
	public:
		SimpleAssnblExpression(StatemPtr func_call) {

		}

		SimpleAssnblExpression(std::unique_ptr<Variable> var) {

		}

		Variable calculate() override {

		}

	private:
		StatemPtr funcCall_;
		Variable var_;
	};
}

