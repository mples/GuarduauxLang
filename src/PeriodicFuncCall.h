#pragma once

#include "FuncCall.h"
#include "Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;

namespace Guarduaux {

	class PeriodicFuncCall : public FuncCall {
	public:
		PeriodicFuncCall(StatemPtr func_call, ExprPtr period) : FuncCall(dynamic_cast<FuncCall&>(*func_call).getFuncDef() ){

		}

		Return run() override {

		}

	private:
		ExprPtr callingPeriod_;

	};
}