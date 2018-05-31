#pragma once

#include <memory>
#include <list>
#include "Token/Token.h"
#include "Expresions/Expresion.h"
#include "Token/TokenType.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;


namespace Guarduaux {

	class SimpleAssnblExpression : public Expresion {
	public:
		SimpleAssnblExpression(StatemPtr func_call) {

		}

		SimpleAssnblExpression(Variable* var) {

		}

		SimpleAssnblExpression(Variable& var) {

		}

		Variable calculate() override {

		}

	private:
		StatemPtr funcCall_;
		Variable* var_;
	};
}

